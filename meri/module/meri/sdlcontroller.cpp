#include "sdlcontroller.h"

#include "json/json.h"
#include "../../core/mousemessage.h"
#include "../../core/keyboardmessage.h"
#include "../../core/covertosdlkeymap.h"
#include "../../core/coordinate.h"

namespace meri
{
    static SOCKET kSdlControllerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_UDP);
    SOCKADDR *client_address = nullptr;

    SDLController::SDLController(int work_area_w, int work_area_h)
        : native_work_area_h_(work_area_h)
        , native_work_area_w_(work_area_w)
        , scale_x_(0), scale_y_(0)
        , accpet_socket_flag_(false)
        , accpet_socket_thread_(nullptr)
        , receive_socket_flag_(false)
    {
    }

    SDLController::~SDLController()
    {
        if (accpet_socket_thread_ != nullptr)
        {
            accpet_socket_flag_ = false;
            accpet_socket_thread_->join();
            delete accpet_socket_thread_;
            accpet_socket_thread_ = nullptr;
        }
        for (auto i : receive_socket_threads_)
        {
            auto& flag = std::get<0>(i);
            auto& th = std::get<1>(i);
            if (flag)
            {
                flag = false;
                th->join();
                delete th;
                th = nullptr;
                receive_socket_threads_.remove(i);
            }
        }
    }

    MeriStatus SDLController::ListenSocket(std::string ip, int port)
    {
        // TODO(tayu.mymail@gmail.com): Create Socket and listening.
        sockaddr_in address;
        memset(&address, 0, sizeof(address));
        address.sin_family = PF_INET;
        address.sin_addr.s_addr = inet_addr(ip.c_str());
        address.sin_port = htons(port);
        bind(kSdlControllerSocket, (SOCKADDR*)&address, sizeof(sockaddr_in));
        listen(kSdlControllerSocket, 20);
        auto accpet_lb = [&]() 
        {
            accpet_socket_flag_ = true;
            while (accpet_socket_flag_)
            {
                client_address = new SOCKADDR();
                int nSize = sizeof(SOCKADDR);
                SOCKET clntSock = accept(kSdlControllerSocket, (SOCKADDR*)&*client_address, &nSize);
                bool receive_flag = true;
                std::thread* temp = new std::thread(&SDLController::ReceiveFromSockets, this, std::ref(receive_flag), std::ref(clntSock));
                receive_socket_threads_.emplace_back(std::make_tuple(std::move(receive_flag), temp));
                sockets_.emplace_back(client_address);
                client_address = nullptr;
                // Exit critical zone.
            } 
            std::cout << "Exit thread of ListenSocket!" << std::endl;
        };
        accpet_socket_thread_ = new std::thread(accpet_lb);
        
        return MeriStatus::kNomal;
    }


    MeriStatus SDLController::ReceiveFromSockets(bool& run_flag, SOCKET& client)
    {
        char buffer[1024]{};
        run_flag = true;
        while (run_flag)
        {
            int res = recv(client, buffer, sizeof(buffer), NULL);
            if (res <= 0) continue;
            ForwardMessage(buffer);
        }
        std::cout << "Exit thread of ReceiveFromSockets!" << std::endl;
        return MeriStatus::kNomal;
    }

    MeriStatus SDLController::ForwardMessage(const std::string json_message)
    {
        DataMessage::DataMessageType type = DataMessage::DataMessageType::kNull;
        Json::CharReaderBuilder builder;
        Json::Value root;
        JSONCPP_STRING err;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(json_message.c_str(), json_message.c_str() + json_message.length(), &root, &err))
        {
            return MeriStatus();
        }
        //get message type, and check is it control.
        std::string message_type = root["type"].asString();
        if (message_type.compare("control") != 0) return MeriStatus();
        //get message data.
        Json::Value message_data = root["data"];
        if (message_data.empty()) return MeriStatus();
        //get event_type from message data
        std::string message_data_event_type = message_data["event"].asString();
        if (message_data_event_type.empty()) return MeriStatus();
        //get message parameters from message data
        Json::Value message_data_parameters = message_data["parameters"];
        if (message_data_parameters.empty()) return MeriStatus();
        //event branch
        DataMessage* message = nullptr;
        if (message_data_event_type.compare("mousemove") == 0)
        {
            // Mouse motion.
            type = DataMessage::DataMessageType::kMouseMove;
            int x = message_data_parameters["x"].asInt();
            int y = message_data_parameters["y"].asInt();
            auto&& corrdinate = CoverNativeCoordinate({ x,y });
            message = new MouseMessage(type, corrdinate.x_, corrdinate.y_, 0, 0);
            return SendMessageToOS(message);
        }
        else if (message_data_event_type.compare("mouseup") == 0 || message_data_event_type.compare("mousedown") == 0)
        {
            // Mouse click.
            if (message_data_parameters.size() < 3) return MeriStatus();
            int x = message_data_parameters["x"].asInt();
            int y = message_data_parameters["y"].asInt();
            // Pressed key returns from JavaScript side is the same as SDL defines. 1 for left, 2 for middle and 3 for right.
            bool mouse_is_pressed = (message_data_event_type.compare("mousedown") == 0) ? true : false;
            type = MouseMessage::CoverButtonType(message_data_parameters["which"].asUInt(), mouse_is_pressed);
            auto&& corrdinate = CoverNativeCoordinate({ x,y });
            message = new MouseMessage(type, corrdinate.x_, corrdinate.y_, 0, mouse_is_pressed);
            return SendMessageToOS(message);
        }
        else if (message_data_event_type.compare("keydown") == 0 || message_data_event_type.compare("keyup") == 0)
        {
            if (message_data_event_type.compare("keydown") == 0)
            {
                type = KeyboardMessage::DataMessageType::kKeyboardDown;
            }
            else
            {
                type = KeyboardMessage::DataMessageType::kKeyboardUp;
            }
            unsigned int which = message_data_parameters["which"].asUInt();
            auto sdl_key = CoverToSDLkey(which);
            if (std::get<0>(sdl_key) == 0 || std::get<1>(sdl_key) == 0)
            {
                return MeriStatus();
            }
            message = new KeyboardMessage(type, std::get<0>(sdl_key), message_data_event_type == "keydown" ? 1 : 0);
            return SendMessageToOS(message);
        }
        else if (message_data_event_type.compare("sizechange") == 0) {
            // Render target size changed. Update screen size for mouse position calculations.
            Json::Value video_size = message_data_parameters["rendererSize"];
            this->native_work_area_h_ = video_size["height"].asInt();
            this->native_work_area_w_ = video_size["width"].asInt();
            return MeriStatus::kNomal;
        }
        else if (message_data_event_type.compare("wheel") == 0)
        {
            short delta = message_data_parameters["deltaY"].asInt();
            if (delta > 0)
            {
                type = DataMessage::DataMessageType::kMiddleButtonUpWheel;
            }
            else if(delta < 0)
            {
                type = DataMessage::DataMessageType::kMiddleButtonDownWheel;
            }
            else
            {
                return MeriStatus();
            }
            int x = message_data_parameters["x"].asInt();
            int y = message_data_parameters["y"].asInt();
            
            auto&& corrdinate = CoverNativeCoordinate({ x,y });
            message = new MouseMessage(type, corrdinate.x_, corrdinate.y_, delta, 0);
            return SendMessageToOS(message);
        }
        else return MeriStatus::kError;
    }

    Coordinate&& SDLController::CoverNativeCoordinate(Coordinate&& coordinate) const
    {
        coordinate.x_ = 0;
        coordinate.y_ = 0;
        return std::move(coordinate);
    }

    MeriStatus SDLController::SendMessageToOS(DataMessage* message) const
    {
        //TODO(tayu.mymail@gmail.com): Create Windows Message struct class.
        INPUT in{};
        switch (message->type_)
        {
            in.type = 0xffff;
            case DataMessage::DataMessageType::kKeyboardDown:
            {
                in.type = INPUT_KEYBOARD;
                KeyboardMessage* keyboard_message = dynamic_cast<KeyboardMessage*>(message);
                if ((in.ki.wVk = CoverToSystemkey(keyboard_message->which_button_)) != 0)
                {
                    in.ki.wScan = MapVirtualKey(in.ki.wVk, MAPVK_VK_TO_VSC);
                }
                break;
            }
            case DataMessage::DataMessageType::kKeyboardUp:
            {
                in.type = INPUT_KEYBOARD;
                KeyboardMessage* keyboard_message = dynamic_cast<KeyboardMessage*>(message);
                if ((in.ki.wVk = CoverToSystemkey(keyboard_message->which_button_)) != 0)
                {
                    in.ki.dwFlags |= KEYEVENTF_KEYUP;
                    in.ki.wScan = MapVirtualKey(in.ki.wVk, MAPVK_VK_TO_VSC);
                }
                break;
            }
            case DataMessage::DataMessageType::kMouseMove:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
                MouseMessage* mouse_message = dynamic_cast<MouseMessage*>(message);
                in.mi.dx = (DWORD)
                    (65536.0 * scale_x_ * mouse_message->x_) / native_work_area_w_;
                in.mi.dy = (DWORD)
                    (65536.0 * scale_y_ * mouse_message->y_) / native_work_area_h_;
                break;
            }
            case DataMessage::DataMessageType::kLeftButtonDown:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                break;
            }
            case DataMessage::DataMessageType::kLeftButtonUp:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                break;
            }
            case DataMessage::DataMessageType::kMiddleButtonDown:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
                break;
            }
            case DataMessage::DataMessageType::kMiddleButtonUp:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
                break;
            }
            case DataMessage::DataMessageType::kMiddleButtonDownWheel:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_WHEEL;
                in.mi.mouseData = -WHEEL_DELTA;
                break;
            }
            case DataMessage::DataMessageType::kMiddleButtonUpWheel:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_WHEEL;
                in.mi.mouseData = +WHEEL_DELTA;
                break;
            }
            case DataMessage::DataMessageType::kRightButtonDown:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
                break;
            }
            case DataMessage::DataMessageType::kRightButtonUp:
            {
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
                break;
            }
            default:
            {
                //case DataMessage::DataMessageType::kNull:
                break;
            }
        } // !end switch
        if (in.type == 0xffff) return MeriStatus::kError;
        SetForegroundWindow(NULL);
        SendInput(1, &in, sizeof(in));
        return MeriStatus::kNomal;
    }
} // !namespace meri
