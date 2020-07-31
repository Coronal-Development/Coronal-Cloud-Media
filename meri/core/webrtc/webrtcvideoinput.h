#ifndef WEBRTC_VIDEO_INPUT_H_
#define WEBRTC_VIDEO_INPUT_H_
#include "../common/common.h"

#include "owt/base/clock.h"
#include "owt/base/videoencoderinterface.h"

struct AVPacket;
namespace meri
{
	class WebRtcVideoEncoder : public owt::base::VideoEncoderInterface
	{
	public:
		static WebRtcVideoEncoder* Create(owt::base::VideoCodec codec);
		static void InsertFrame(AVPacket* packet);
		void FlushQueue();
		void RequestKeyFrame();
		void SetMaxBitrate(int64_t bps);
	protected:
		virtual bool InitEncoderContext(owt::base::Resolution& resolution,
			uint32_t fps,
			uint32_t bitrate,
			owt::base::VideoCodec video_codec) override;
		virtual bool EncodeOneFrame(std::vector<uint8_t>& buffer,
			bool keyFrame,
			uint64_t& capture_timestamp,
			uint16_t& picture_id) override;
		virtual bool Release() override;

		virtual owt::base::VideoEncoderInterface* Copy() override;
	private:
		static owt::base::VideoCodec codec_;
		static std::list<WebRtcVideoEncoder*> encoders_;
		static std::mutex encoders_mutex_;
		std::mutex packet_mutex_;
		std::queue<std::pair<std::chrono::system_clock::time_point, AVPacket*>>
			packets_;
		std::unique_ptr<owt::base::Clock> clock_;
	};

}

#endif // !WEBRTC_VIDEO_INPUT_H_
