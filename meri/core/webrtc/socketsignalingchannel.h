#ifndef SOCKETSIGNALINGCHANNEL_H_
#define SOCKETSIGNALINGCHANNEL_H_
#include "../../core/common/common.h"
#include "sio_client.h"
#include "owt/p2p/p2psignalingchannelinterface.h"

using namespace owt::p2p;

namespace meri
{
	class connection_listener
	{
		sio::client& handler;
	public:
		connection_listener(sio::client& hdl) : handler(hdl) {}
		void on_connected() {}
	};

	class SocketSignalingChannel : public P2PSignalingChannelInterface
	{
	public:
		explicit SocketSignalingChannel();
		virtual void AddObserver(
			P2PSignalingChannelObserver& observer) override;
		virtual void RemoveObserver(
			P2PSignalingChannelObserver& observer) override;
		virtual void Connect(const std::string& host,
			const std::string& token,
			std::function<void(const std::string&)> on_success,
			std::function<void(std::unique_ptr<Exception>)> on_failure) override;
		virtual void Disconnect(std::function<void()> on_success,
			std::function<void(std::unique_ptr<Exception>)> on_failure) override;
		virtual void SendMessage(const std::string& message, const std::string& target_id,
			std::function<void()> on_success,
			std::function<void(std::unique_ptr<owt::base::Exception>)>on_failurr)override;
	private:
		std::vector<P2PSignalingChannelObserver*> observers_;
		std::unique_ptr<sio::client> io_;
		std::function<void(const std::string&)> connect_success_callback_;
		std::unique_ptr<connection_listener> connection_listener_;
	};
}

#endif // SOCKETSIGNALINGCHANNEL_H_
