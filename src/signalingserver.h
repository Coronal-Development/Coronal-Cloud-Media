#ifndef CCM_SIGNALING_SERVER_H_
#define CCM_SIGNALING_SERVER_H_

#include "sio_client.h"
#include "owt/p2p/p2psignalingchannelinterface.h"

namespace ccm
{
    class Connection_listener
    {
        sio::client &handler_;
    public:
        Connection_listener(sio::client &handler) :handler_(handler) {}
        void On_connected() {}
    }; // !class Connection_listener

    class SignalingServer :public owt::p2p::P2PSignalingChannelInterface
    {
    public:
        explicit SignalingServer();
        virtual void AddObserver(owt::p2p::P2PSignalingChannelObserver &observer)override;
        virtual void RemoveObserver(owt::p2p::P2PSignalingChannelObserver &observer)override;
        virtual void Connect(const std::string &host, const std::string &token,
            std::function<void(const std::string&)> on_success,
            std::function<void(std::unique_ptr<owt::base::Exception>)> on_failure)override;
        virtual void Disconnect(std::function<void()> on_success,
            std::function<void(std::unique_ptr<owt::base::Exception>)>on_failure)override;
        virtual void SendMessage(const std::string &message, const std::string &target_id,
            std::function<void()> on_success,
            std::function<void(std::unique_ptr<owt::base::Exception>)>on_failurr)override;
    private:
        std::vector<owt::p2p::P2PSignalingChannelObserver*> observers_;
        std::unique_ptr<sio::client> io_;
        std::unique_ptr<Connection_listener> connection_listener_;
        std::function<void(const std::string &)> connect_success_callback_;
    }; // ! class SignalingServer
} // !namespace ccm

#endif // !CCM_SIGNALING_SERVER_H_