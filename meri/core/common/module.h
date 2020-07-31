#ifndef MODULE_H_
#define MODULE_H_
#include <functional>
#include <string>

namespace meri
{
    struct AVPacket;
    enum class ModuleType
    {
        controller = 0
    };

    class Module
    {
    public:
        explicit Module() = default;
        explicit Module(std::string name, ModuleType type, std::string mimetype = "")
            :name_(name), type_(type), mimetype_(mimetype) {}

        HMODULE                                         handle_;
        ModuleType                                      type_;
        std::string                                     name_;
        std::string                                     mimetype_;
        std::function<int(void* arg)>                   init_;
        std::function<int(void* arg)>                   start_;
        std::function<int(void* arg)>                   stop_;
        std::function<int(void* arg)>                   deinit_;
        std::function<int(int command
                            , int argsize
                            , void* arg)>               ioctl_;
        std::function<int(void* arg)>                   notify_;
        std::function<void*(void* arg)>                 raw_;
        std::function<int(const char* prefix
                            , int channelId
                            , AVPacket* pkt
                            , int64_t encoderPts
                            , struct timeval* ptv)>     send_packet_;

    };
}


#endif // !MODULE_H_
