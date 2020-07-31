#include "webrtcvideoinput.h"

namespace meri
{
    WebRtcVideoEncoder* WebRtcVideoEncoder::Create(owt::base::VideoCodec codec)
    {
        return nullptr;
    }
    void WebRtcVideoEncoder::InsertFrame(AVPacket* packet)
    {
    }
    void WebRtcVideoEncoder::FlushQueue()
    {
    }
    void WebRtcVideoEncoder::RequestKeyFrame()
    {
    }
    void WebRtcVideoEncoder::SetMaxBitrate(int64_t bps)
    {
    }
    bool WebRtcVideoEncoder::InitEncoderContext(owt::base::Resolution& resolution, uint32_t fps, uint32_t bitrate, owt::base::VideoCodec video_codec)
    {
        return false;
    }
    bool WebRtcVideoEncoder::EncodeOneFrame(std::vector<uint8_t>& buffer, bool keyFrame, uint64_t& capture_timestamp, uint16_t& picture_id)
    {
        return false;
    }
    bool WebRtcVideoEncoder::Release()
    {
        return false;
    }
}

