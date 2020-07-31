#include "../../core/common/common.h"
#include "../../core/webrtc/webrtcclient.h"
#include "serverwebrtc.h"

namespace meri
{
	enum ga_ioctl_commands {
		GA_IOCTL_NULL = 0,		/**< Not used */
		GA_IOCTL_RECONFIGURE,		/**< Reconfiguration */
		GA_IOCTL_RECONFIGURE_DELTAQP,
		GA_IOCTL_REQUEST_KEYFRAME,   /**< Request a key frame. */
		GA_IOCTL_GET_CREDIT_BYTES,
		GA_IOCTL_SET_MAX_BPS,
		GA_IOCTL_GETSPS = 0x100,	/**< Get SPS: for H.264 and H.265 */
		GA_IOCTL_GETPPS,		/**< Get PPS: for H.264 and H.265 */
		GA_IOCTL_GETVPS,		/**< Get VPS: for H.265 */
		GA_IOCTL_UPDATE_CLIENT_EVENT,  /** < Upate keyboard and mouse event for the E2E latency*/
		GA_IOCTL_REQUEST_NEW_CURSOR,
		GA_IOCTL_CUSTOM = 0x40000000	/**< For user customization */
	};

#define	GA_IOCTL_ERR_NONE		0	/**< No error */
#define	GA_IOCTL_ERR_GENERAL		-1	/**< General error */
#define	GA_IOCTL_ERR_NULLMODULE		-2	/**< Module is NULL */
#define	GA_IOCTL_ERR_NOIOCTL		-3	/**< ioctl() is not implemented */
#define	GA_IOCTL_ERR_NOINTERFACE	-3	/**< ioctl() or interface is not implemented */
#define	GA_IOCTL_ERR_NOTINITIALIZED	-4	/**< Module has not been initialized */
#define	GA_IOCTL_ERR_NOTSUPPORTED	-5	/**< Command is not supported */
#define	GA_IOCTL_ERR_INVALID_ARGUMENT	-6	/**< Invalid argument */
#define	GA_IOCTL_ERR_NOTFOUND		-7	/**< Not found */
#define	GA_IOCTL_ERR_BUFFERSIZE		-8	/**< Buffer error */
#define	GA_IOCTL_ERR_BADID		-9	/**< Invalid Id */
#define	GA_IOCTL_ERR_NOMEM		-10	/**< No memory */

	class ga_ioctl_credit_t;
	static ServerWebrtc* instance = ServerWebrtc::GetInstance();

	ModuleVirtualInterface* GetModule()
	{
		return instance;
	}

	int ServerWebrtc::Init(void* arg)
	{
		p2pclient_ =
			std::make_unique<WebrctP2PClient>(WebrctP2PClient());
		return p2pclient_->Init(arg);
	}

	int ServerWebrtc::Start(void*)
	{
		return p2pclient_->Start();
	}

	int ServerWebrtc::Stop(void*)
	{
		return p2pclient_->Stop();
	}

	int ServerWebrtc::Deinit(void*)
	{
		return 0;
	}

	int ServerWebrtc::IOCtrl(int command, int argsize, void* arg)
	{
		int ret = 0;
		ga_ioctl_credit_t* credit = (ga_ioctl_credit_t*)arg;
		int64_t credit_bytes = 0;
		switch (command) {
		case GA_IOCTL_GET_CREDIT_BYTES:
			//const int ga_ioctl_credit_t_SIZE = 0;
			//if (argsize != sizeof(ga_ioctl_credit_t_SIZE))
			//	return GA_IOCTL_ERR_INVALID_ARGUMENT;
			if (p2pclient_.get())
				credit_bytes = p2pclient_->GetCreditBytes();
			//memcpy(&credit_bytes, &(credit->credit_bytes), sizeof(credit->credit_bytes));
			break;
		default:
			break;
		}
		return 0;
	}

	int ServerWebrtc::Notify(void*)
	{
		return 0;
	}

	int ServerWebrtc::Raw(void* arg, int* size)
	{
		return 0;
	}

	int ServerWebrtc::send_packet(const char* prefix, int channelId, AVPacket* pkt, int64_t encoderPts, timeval* ptv)
	{
		p2pclient_->InsertFrame(pkt);
		return 0;
	}
}