#ifndef WEBRTC_CLIENT_H_
#define WEBRTC_CLIENT_H_
#include "../common/common.h"

#include "owt/base/globalconfiguration.h"
#include "owt/p2p/p2pclient.h"

#include "socketsignalingchannel.h"
#include "webrtccontroller.h"
#include "webrtcvideoinput.h"

namespace meri
{
	struct AVPacket;
	class WebrctP2PClient : public owt::p2p::P2PClientObserver,
		public std::enable_shared_from_this<WebrctP2PClient>
	{
	public:
		int Init(void* arg);
		int Start();
		int Stop();
		void InsertFrame(AVPacket* packet);
		void SendCursor(const std::string& cursor_info);

		int64_t GetCreditBytes();
		int64_t GetMaxBitrate();

	protected:
		virtual void OnMessageReceived(const std::string& remote_user_id,
			const std::string message) override;
		virtual void
			OnStreamAdded(std::shared_ptr<owt::base::RemoteStream> stream) override;
	private:
		void ConnectCallback(bool is_fail, const std::string& error);
		void CreateStream();

		std::shared_ptr<owt::p2p::P2PClient> p2pclient_;
		std::promise<int> connect_status_;
		std::shared_ptr<owt::base::LocalStream> local_stream_;
		std::shared_ptr<owt::base::LocalStream> local_audio_stream;
		WebRtcVideoEncoder* ga_encoder_;
		std::unique_ptr<WebRtcController> controller_;
		int64_t bytes_sent_on_last_stat_call_;
		int64_t bytes_sent_on_last_credit_call_;
		int64_t credit_bytes_;
		int64_t current_available_bandwidth_;
		std::string remote_user_id_;
		std::string last_cursor_msg_;
	};
}

#endif // !WEBRTC_CLIENT_H_
