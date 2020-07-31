#ifndef WEBRTC_AUDIO_FRAME_GENERATOR_H_
#define WEBRTC_AUDIO_FRAME_GENERATOR_H_

#include "owt/base/framegeneratorinterface.h"

namespace meri
{
	class WebRtcAudioFrameGenerator : public owt::base::AudioFrameGeneratorInterface
	{
	public:
		static WebRtcAudioFrameGenerator* Create(int channel_number, int sample_rate);
		~WebRtcAudioFrameGenerator();

		virtual uint32_t GenerateFramesForNext10Ms(uint8_t* frame_buffer,
			const uint32_t capacity) override;
		virtual int GetSampleRate() override;
		virtual int GetChannelNumber() override;

	private:

	};
}

#endif // !WEBRTC_AUDIO_FRAME_GENERATOR_H_
