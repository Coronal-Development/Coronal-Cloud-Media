#include "pch.h"
#include "signalingserver.h"
#include <algorithm>

namespace ccm
{
    SignalingServer::SignalingServer()
        :io_(new sio::client())
        ,connection_listener_(new Connection_listener(*io_))
    {}

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
        std::map<std::string, std::string> query;
        query.insert(std::pair<std::string, std::string>("clientVersion", "4.2"));
        query.insert(std::pair<std::string, std::string>("clientType", "cpp"));
        query.insert(std::pair<std::string, std::string>("token", token)); // TODO: parse token to get actual token.

        io_->set_open_listener(std::bind(&Connection_listener::On_connected, connection_listener_.get()));

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
        io_->connect(host, query);
    }

    void SignalingServer::Disconnect(std::function<void()> on_success, std::function<void(std::unique_ptr<owt::base::Exception>)> on_failure)
    {
    }

    void SignalingServer::SendMessage(const std::string & message, const std::string & target_id, std::function<void()> on_success, std::function<void(std::unique_ptr<owt::base::Exception>)> on_failurr)
    {
    }

} // ! namespace ccm