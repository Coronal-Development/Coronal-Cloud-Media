#ifndef ETW_LOG_CONTROLLERS_H_
#define ETW_LOG_CONTROLLERS_H_
namespace log
{
    class EtwController
    {
    public:
        EtwController();
        ~EtwController();

        bool CreateSession();
        bool EnableProvider();
        bool DisableProvider();
        bool StopSession();

    private:
        int controller_state_;
    };
}
#endif // !ETW_LOG_CONTROLLERS_H_
