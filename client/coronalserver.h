#ifndef CCM_CORONAL_SERVER_H_
#define CCM_CORONAL_SERVER_H_

#include "owt/p2p/p2pclient.h"
#include "signalingserver.h"

namespace ccm
{
    class CoronalServer : public owt::p2p::P2PClientObserver
    {
    public:
        void Connect();
        owt::base::VideoCodec GetVidoeCodec(std::string video_codec_name);
        owt::base::AudioCodec GetAudioCodec(std::string audio_codec_name);
    private:
        owt::p2p::P2PClientConfiguration configuration_;
        std::shared_ptr<owt::p2p::P2PClient> p2pclient_;
        std::shared_ptr<SignalingServer> signaling_server_;
        std::string local_peer_id_;
        std::string url_;
        std::string video_codec_;
        std::string audio_codec_;
    }; // ! class CoronalServer
} // ! namespace ccm

#endif // !CCM_CORONAL_SERVER_H_