#ifndef SERVER_WEBRTC_H_
#define SERVER_WEBRTC_H_

#include "../../core/common/common.h"
#include "../../core/webrtc/webrtcclient.h"
#include "../../core/common/modulevirtualinterface.h"

namespace meri
{
	class ServerWebrtc : public ModuleVirtualInterface
	{
	public:
		SINGLETON_DEFINE(ServerWebrtc)
		~ServerWebrtc() = default;
		virtual int Init(void* arg) override;
		virtual int Start(void*) override;
		virtual int Stop(void*) override;
		virtual int Deinit(void*) override;
		virtual int IOCtrl(int command, int argsize, void* arg) override;
		virtual int Notify(void*) override;
		virtual int Raw(void* arg, int* size) override;
		virtual int send_packet(const char* prefix
								, int channelId
								, AVPacket* pkt
								, int64_t encoderPts
								, struct timeval* ptv);

	private:
		ServerWebrtc() = default;

		std::shared_ptr<WebrctP2PClient> p2pclient_;
	};
}

#endif // !SERVER_WEBRTC_H_
