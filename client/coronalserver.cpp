#include "pch.h"
#include "CoronalServer.h"

namespace ccm
{
    void CoronalServer::Connect()
    {
        if (signaling_server_.get() == nullptr)
        {
            signaling_server_.reset(new SignalingServer());
        }
        owt::base::GlobalConfiguration::SetVideoHardwareAccelerationEnabled(true);
        video_codec_ = "H264";
        audio_codec_ = "OPUS";
        owt::base::VideoCodecParameters video_codec_params;
        owt::base::AudioCodecParameters audio_codec_params;
        video_codec_params.name = GetVidoeCodec(video_codec_);
        audio_codec_params.name = GetAudioCodec(audio_codec_);
        owt::base::VideoEncodingParameters video_params(video_codec_params, 0, true);
        owt::base::AudioEncodingParameters audio_params(audio_codec_params, 0);
        configuration_.video_encodings.emplace_back(video_params);
        configuration_.audio_encodings.emplace_back(audio_params);
        url_ = "http://10.67.113.69:8095";
        local_peer_id_ = "client";
        if (p2pclient_.get() == nullptr)
        {
            p2pclient_.reset(new owt::p2p::P2PClient(configuration_,signaling_server_));
        }
        p2pclient_->AddObserver(*this);
        p2pclient_->Connect(url_,local_peer_id_,nullptr,nullptr);
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