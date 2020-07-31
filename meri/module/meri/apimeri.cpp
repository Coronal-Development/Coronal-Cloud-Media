#include "../../core/common/common.h"
#include "meriserver.h"
static meri::MeriServer* kMeriServerInstance = meri::MeriServer::GetInstance();
#ifdef MERI_EXPORTS
#define MERI_API __declspec(dllexport)
#else
#define MERI_API __declspec(dllimport)
#endif

extern "C" MERI_API bool RegisterMeri()
{
    kMeriServerInstance->Init();
    return 0;
}

extern "C" MERI_API bool EncodeFrame()
{
    return true;
}

extern "C" MERI_API bool UnRegisterMeri()
{
    kMeriServerInstance->Deinit();
    return 0;
}



