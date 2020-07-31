#ifndef MERI_SDLCONTROLLER_H_
#define MERI_SDLCONTROLLER_H_
#include "../../core/common/common.h"

namespace meri
{
    class Coordinate;
    class SDLController
    {
    public:
        SDLController(int work_area_w = 1920, int work_area_h = 1080);
        ~SDLController();
        MeriStatus ListenSocket(std::string ip = "127.0.0.1", int port = 8554);
    private:
        MeriStatus ReceiveFromSockets(bool& run_flag, SOCKET& client);
        MeriStatus ForwardMessage(const std::string message);
        Coordinate&& CoverNativeCoordinate(Coordinate &&coordinate) const;
        MeriStatus SendMessageToOS(class DataMessage* message) const;
        friend std::tuple<unsigned short, unsigned short> CoverToSDLkey(uint32_t which_key_button);

        int native_work_area_w_, native_work_area_h_;
        int scale_x_, scale_y_;
        std::list<void*> sockets_;
        std::mutex sockets_lock_;
        bool accpet_socket_flag_;
        std::thread* accpet_socket_thread_;
        bool receive_socket_flag_;
        std::list<std::tuple<bool,std::thread*>> receive_socket_threads_;
    }; // !SDLCONTROLLER
} // !namespace meri

#endif // !MERI_SDLCONTROLLER_H_

