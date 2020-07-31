#ifndef WEBRTC_CONTROLLER_H_
#define WEBRTC_CONTROLLER_H_
#include "../common/common.h"

namespace meri
{
    class WebRtcController
    {
    public:
        WebRtcController(unsigned long this_width = 1920, unsigned long this_height = 1080
                        , unsigned long that_width = 1920, unsigned long that_height = 1080)
            : work_width_(this_width), work_height_(this_height) 
            , remote_width_(that_width), remote_height_(that_height){}
        void PushClientEvent(const std::string& jsonMessage);
        unsigned long work_width_;
        unsigned long work_height_;
        unsigned long remote_width_;
        unsigned long remote_height_;
    };
}

#endif // !WEBRTC_CONTROLLER_H_
