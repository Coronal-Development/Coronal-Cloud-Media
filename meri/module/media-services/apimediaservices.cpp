#include "../../core/common/common.h"
#include "../../core/mediaservices.h"

int main()
{
    meri::MediaServices* instance = meri::MediaServices::GetInstance();
    instance->Init();
    return 0;
}