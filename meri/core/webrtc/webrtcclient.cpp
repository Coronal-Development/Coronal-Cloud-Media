#include "webrtcclient.h"
#include "webrtcaudioinput.h"
#include "socketsignalingchannel.h"
#include "../../core/signalingserver.h"

namespace meri
{
    int EnncoderRegisterClient(void* ctx)
    {
        return 1;
    }

    int WebrctP2PClient::Init(void* arg)
    {
        // read config
        meri::MeriRect rect{ 0,0,1920,1080 };
        std::string signaing_server_host = "localhost";
        std::string signaing_server_port = "8095";
        std::stringstream path;
        std::string server_peer_id = "ga";
        std::string client_peer_id = "client";
        std::string stun_urls = "stun:example.com:3478";
        std::string turn_urls = "turn:example.com:3478?transport=udp";
        std::string turn_credential = "password";
        std::string turn_username = "username";
        unsigned short game_width = rect.width_;
        unsigned short game_height = rect.height_;
        controller_ = std::make_unique<WebRtcController>(game_width, game_height);
        path << "http://" << signaing_server_host << ":" << signaing_server_port;
        bytes_sent_on_last_stat_call_ = 0;
        bytes_sent_on_last_credit_call_ = 0;
        current_available_bandwidth_ = 8 * 1000 * 1000;  //Initial setting for 1080p. Will be adjusted.
        owt::p2p::GlobalConfiguration::SetEncodedVideoFrameEnabled(true);
        owt::p2p::GlobalConfiguration::SetAEC3Enabled(false);
        owt::p2p::GlobalConfiguration::SetAECEnabled(false);
        owt::p2p::GlobalConfiguration::SetAGCEnabled(false);

        owt::p2p::GlobalConfiguration::SetVideoHardwareAccelerationEnabled(true);
        owt::p2p::GlobalConfiguration::SetLowLatencyStreamingEnabled(true);
        owt::p2p::GlobalConfiguration::SetDelayBasedBWEWeight(100);

        auto generator =
            std::unique_ptr<WebRtcAudioFrameGenerator>(WebRtcAudioFrameGenerator::Create(
                111, 111));
        // Always enable customized audio input here. `CreateStream` will
        // enable/disable audio track according to conf.
        owt::p2p::GlobalConfiguration::SetCustomizedAudioInputEnabled(true,
            std::move(generator));
        std::shared_ptr<SocketSignalingChannel> signaling =
            std::make_shared<SocketSignalingChannel>(SocketSignalingChannel());
        owt::p2p::P2PClientConfiguration config;
        owt::p2p::IceServer ice_server;
        //init STUN server
        ice_server.urls.push_back(stun_urls);
        config.ice_servers.push_back(ice_server);
        ice_server.urls.clear();

        //init TURN server
        ice_server.urls.push_back(stun_urls);
        ice_server.password = turn_credential;
        ice_server.username = turn_username;
        config.ice_servers.push_back(ice_server);

        p2pclient_.reset(new owt::p2p::P2PClient(config, signaling));
        p2pclient_->AddObserver(*this);
        std::future<int> connect_done = connect_status_.get_future();
        std::weak_ptr<WebrctP2PClient> weak_this = shared_from_this();
        p2pclient_->AddAllowedRemoteId(client_peer_id);
        // TODO: Temporary hard code allowed remote IDs here. It should be set by user or configuration file.
        p2pclient_->AddAllowedRemoteId("client");
        p2pclient_->AddAllowedRemoteId("client1");
        p2pclient_->AddAllowedRemoteId("client2");
        p2pclient_->AddAllowedRemoteId("client3");
        p2pclient_->AddAllowedRemoteId("client4");
        p2pclient_->Connect(path.str(), server_peer_id,
            [weak_this](const std::string& id) {
            auto that = weak_this.lock();
            if (!that)
                return;
            that->ConnectCallback(false, "");
        },
            [weak_this](std::unique_ptr<owt::p2p::Exception> err) {
            auto that = weak_this.lock();
            if (!that)
                return;
            that->ConnectCallback(true, err->Message());
        });
        CreateStream();
        return 0;
    }

    int WebrctP2PClient::Start()
    {
        if (EnncoderRegisterClient(this) < 0) return -1;
        return 0;
    }

    int WebrctP2PClient::Stop()
    {
        return 0;
    }

    void WebrctP2PClient::InsertFrame(AVPacket* packet)
    {
    }

    void WebrctP2PClient::SendCursor(const std::string& cursor_info)
    {
    }

    int64_t WebrctP2PClient::GetCreditBytes()
    {
        return int64_t();
    }

    int64_t WebrctP2PClient::GetMaxBitrate()
    {
        return int64_t();
    }

    void WebrctP2PClient::OnMessageReceived(const std::string& remote_user_id, const std::string message)
    {
    }

    void WebrctP2PClient::OnStreamAdded(std::shared_ptr<owt::base::RemoteStream> stream)
    {
    }

    void WebrctP2PClient::ConnectCallback(bool is_fail, const std::string& error)
    {
    }

    void WebrctP2PClient::CreateStream()
    {
        ga_encoder_ = WebRtcVideoEncoder::Create(owt::base::VideoCodec::kH264);
        std::shared_ptr<owt::base::LocalCustomizedStreamParameters> lcsp;
        lcsp.reset((new owt::p2p::LocalCustomizedStreamParameters(true, true)));
        lcsp->Fps(240);
        lcsp->Resolution(480, 320);
        int error_code = 0;
        local_stream_ = owt::p2p::LocalStream::Create(lcsp, ga_encoder_);
    }
}


