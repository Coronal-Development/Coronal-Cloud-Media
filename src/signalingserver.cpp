#include "../pch.h"
#include "signalingserver.h"
#include <algorithm>

namespace ccm
{
    SignalingServer::SignalingServer()
        :io_(new sio::client())
        ,connection_listener_(new ConnectionListener(*io_))
    {}

    SignalingServer::~SignalingServer()
    {
        observers_.clear();
    }

    void SignalingServer::AddObserver(owt::p2p::P2PSignalingChannelObserver & observer)
    {
        observers_.emplace_back(&observer);
    }

    void SignalingServer::RemoveObserver(owt::p2p::P2PSignalingChannelObserver & observer)
    {
        observers_.erase(remove(observers_.begin(), observers_.end(), &observer), observers_.end());
    }

    void SignalingServer::Connect(const std::string & host, const std::string & token, 
                                  std::function<void(const std::string&)> on_success, 
                                  std::function<void(std::unique_ptr<owt::base::Exception>)> on_failure)
    {
        connect_success_callback_ = on_success;
        connect_failed_callback_ = on_failure;
        std::map<std::string, std::string> query;
        query.insert(std::pair<std::string, std::string>("clientVersion", "4.2"));
        query.insert(std::pair<std::string, std::string>("clientType", "cpp"));
        query.insert(std::pair<std::string, std::string>("token", token)); // TODO: parse token to get actual token.
        ListenerSocket();
        io_->connect(host, query);
    }

    void SignalingServer::Disconnect(std::function<void()> on_success, std::function<void(std::unique_ptr<owt::base::Exception>)> on_failure)
    {
        if (!io_->opened())
        {
            if (on_failure)
            {
                std::unique_ptr<owt::base::Exception> exception(
                    new owt::base::Exception(owt::base::ExceptionType::kP2PClientInvalidState,
                        "Socket IO service has not been opened yet."));
                on_failure(std::move(exception));
            }
            return;
        }
        io_->close();
    }

    void SignalingServer::SendMessage(const std::string & message, const std::string & target_id, std::function<void()> on_success, std::function<void(std::unique_ptr<owt::base::Exception>)> on_failure)
    {
        sio::message::ptr json_object = sio::object_message::create();
        json_object->get_map()["to"] = sio::string_message::create(target_id);
        json_object->get_map()["data"] = sio::string_message::create(message);
        io_->socket()->emit("owt-message", json_object, [=](const sio::message::list& msg)
        {
            if (msg.size() > 0 && msg[0]->get_flag() == sio::message::flag_integer)
            {
                int64_t error_code = msg[0]->get_int();
                if (on_failure) {
                    std::unique_ptr<owt::base::Exception> exception(
                        new owt::base::Exception(owt::base::ExceptionType::kP2PMessageTargetUnreachable,
                            "Remote user cannot be reached."));
                    on_failure(std::move(exception));
                }
                return;
            }
        });
    }

    void SignalingServer::ListenerSocket()
    {
        io_->set_open_listener(std::bind(&ConnectionListener::OnConnected, connection_listener_.get()));
        sio::socket::ptr socket = io_->socket();
        std::string ics_chat = "owt-message";
        std::string auth_done = "server-authenticated";
        socket->on(
            ics_chat,
            sio::socket::event_listener_aux(
                [&](std::string const& name, sio::message::ptr const& data,
                    bool has_ack, sio::message::list& ack_resp) {
            if (data->get_flag() == sio::message::flag_object) {
                std::string msg = data->get_map()["data"]->get_string().data();
                std::string from = data->get_map()["from"]->get_string().data();
                for (auto it = observers_.begin(); it != observers_.end(); ++it)
                    (*it)->OnSignalingMessage(msg, from);
            }
        }));
        socket->on(
            auth_done,
            sio::socket::event_listener_aux(
                [&](std::string const& name, sio::message::ptr const& data,
                    bool has_ack, sio::message::list& ack_resp) {
            if (data->get_flag() == sio::message::flag_object && connect_success_callback_) {
                std::string msg = data->get_map()["uid"]->get_string().data();
                connect_success_callback_(msg);
            }
        }));
    }

} // ! namespace ccm