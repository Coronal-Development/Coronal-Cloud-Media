#ifndef ETW_LOG_INTERFACE_H_
#define ETW_LOG_INTERFACE_H_
#include <string>
namespace log
{
    struct GUID
    {
        std::string id_;
    };
    struct Session
    {
        std::string session_name_;
        GUID guid_;
    };
}
#endif // !ETW_LOG_INTERFACE_H_
