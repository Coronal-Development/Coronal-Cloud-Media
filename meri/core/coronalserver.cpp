#include "CoronalServer.h"
#include <algorithm>

namespace ccm
{
    CoronalServer::CoronalServer()
        : initailization_flag_(0)
        , configuration_{}
        , p2pclient_{nullptr}
        , signaling_server_(new SignalingServer())
        , local_peer_id_{}
        , url_{}
        , video_codec_{}
        , audio_codec_{}
    {}

    CoronalServer::~CoronalServer()
    {
    }

    void CoronalServer::Init()
    {
        owt::base::GlobalConfiguration::SetVideoHardwareAccelerationEnabled(true);
        video_codec_ = "H264";
        audio_codec_ = "OPUS";
        AddVideoCodecToConfig(video_codec_);
        AddAudioCodecToConfig(audio_codec_);
        url_ = "http://10.67.113.97:8095";
        local_peer_id_ = "client";
    }

    void CoronalServer::Connect()
    {
        if (p2pclient_ != nullptr) return;
        p2pclient_ = std::make_shared<owt::p2p::P2PClient>(configuration_, signaling_server_);
        p2pclient_->AddObserver(*this);
        p2pclient_->Connect(url_,local_peer_id_,nullptr,nullptr);
        
    }

    void CoronalServer::SetRemoteId(std::string id)
    {
        remote_peer_id_ = id;
        p2pclient_->AddAllowedRemoteId(id);
    }

    void CoronalServer::Start()
    {
        p2pclient_->Send(remote_peer_id_, "start", nullptr, nullptr);
    }

    void CoronalServer::Disconnect()
    {
        p2pclient_->Disconnect(nullptr, nullptr);
    }

    void CoronalServer::AddVideoCodecToConfig(std::string codec_name)
    {
        owt::base::VideoCodecParameters video_codec_params;
        video_codec_params.name = GetVidoeCodec(codec_name);
        if (video_codec_params.name == owt::base::VideoCodec::kUnknown) return;
        owt::base::VideoEncodingParameters video_params(video_codec_params, 0, true);
        configuration_.video_encodings.emplace_back(video_params);
    }

    void CoronalServer::RemoveVideoCodecFromConfig(std::string codec_name)
    {
        auto code_name = GetVidoeCodec(codec_name);
        auto& codec_vector = configuration_.video_encodings;
        for (auto i = codec_vector.begin(); i != codec_vector.end(); i++)
        {
            if (i->codec.name == code_name)
            {
                codec_vector.erase(i);
                break;
            }
        }
    }

    void CoronalServer::AddAudioCodecToConfig(std::string codec_name)
    {
        owt::base::AudioCodecParameters audio_codec_params;
        audio_codec_params.name = GetAudioCodec(codec_name);
        if (audio_codec_params.name == owt::base::AudioCodec::kUnknown) return;
        owt::base::AudioEncodingParameters audio_params(audio_codec_params, 0);
        configuration_.audio_encodings.emplace_back(audio_params);
    }

    void CoronalServer::RemoveAudioCodecFromConfig(std::string codec_name)
    {
        auto code_name = GetAudioCodec(codec_name);
        auto& codec_vector = configuration_.audio_encodings;
        for (auto i = codec_vector.begin(); i != codec_vector.end(); i++)
        {
            if (i->codec.name == code_name)
            {
                codec_vector.erase(i);
                break;
            }
        }
    }

    owt::base::VideoCodec CoronalServer::GetVidoeCodec(std::string video_codec_name)
    {
        if (!video_codec_name.compare("VP8"))
        {
            return owt::base::VideoCodec::kVp8;
        }
        else if (!video_codec_name.compare("VP9"))
        {
            return owt::base::VideoCodec::kVp9;
        }
        else if (!video_codec_name.compare("H264"))
        {
            return owt::base::VideoCodec::kH264;
        }
        else if (!video_codec_name.compare("H265"))
        {
            return owt::base::VideoCodec::kH265;
        }
        return owt::base::VideoCodec::kUnknown;
    }

    owt::base::AudioCodec CoronalServer::GetAudioCodec(std::string audio_codec_name)
    {
        if (!audio_codec_name.compare("OPUS"))
        {
            return owt::base::AudioCodec::kOpus;
        }
        else if (!audio_codec_name.compare("PCMU"))
        {
            return owt::base::AudioCodec::kPcmu;
        }
        else if (!audio_codec_name.compare("PCMA"))
        {
            return owt::base::AudioCodec::kPcma;
        }
        else if (!audio_codec_name.compare("AC3"))
        {
            return owt::base::AudioCodec::kAc3;
        }
        return owt::base::AudioCodec::kUnknown;
    }

} // !namespace ccm