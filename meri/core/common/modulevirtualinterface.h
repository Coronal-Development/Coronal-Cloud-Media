#ifndef MODULE_VIRTUAL_INTERFACE_H_
#define MODULE_VIRTUAL_INTERFACE_H_

#ifdef MERI_EXPORTS
#define MERI_API __declspec(dllexport)
#else
#define MERI_API __declspec(dllimport)
#endif

#include "module.h"
namespace meri
{
    class ModuleVirtualInterface
    {
    public:
        virtual int Init(void *arg) = 0;
        virtual int Start(void *) = 0;
        virtual int Stop(void *) = 0;
        virtual int Deinit(void *) = 0;
        virtual int IOCtrl(int command, int argsize, void* arg) = 0;
        virtual int Notify(void *) = 0;
        virtual int Raw(void* arg, int* size) = 0;
        virtual int send_packet(const char* prefix
                                , int channelId
                                , AVPacket* pkt
                                , int64_t encoderPts
                                , struct timeval* ptv) {return 0;};
        HMODULE                                         handle_;
        ModuleType                                      type_;
        std::string                                     name_;
        std::string                                     mimetype_;
    };

    extern "C" MERI_API ModuleVirtualInterface * GetModule();
}

#endif // !MODULE_VIRTUAL_INTERFACE_H_
