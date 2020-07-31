#pragma once
#ifndef MERISERVER_H_
#define MERISERVER_H_

#include "../../core/common/common.h"

namespace meri
{
    class SDLController;
    class MeriServer
    {
    public:
        SINGLETON_DEFINE(MeriServer)
        MeriStatus Init();
        MeriStatus Deinit();
        MeriStatus EncodeFrame();
    private:
        MeriServer();
        ~MeriServer();

        SDLController* sdl_controller_;
    };
} // !namespace meri

#endif // !MERISERVER_H_


