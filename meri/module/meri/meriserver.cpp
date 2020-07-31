#include "meriserver.h"
#include "sdlcontroller.h"
#include "../core/config/config.h"

#pragma comment (lib, "ws2_32.lib")

namespace meri
{
    MeriServer::MeriServer()
        :sdl_controller_(nullptr)
    {

    }

    MeriServer::~MeriServer()
    {
    }

    MeriStatus MeriServer::Init()
    {
        // TODO(yourtayu@gmail.com): Init socket.
        WSADATA wsadata;
        WSAStartup(MAKEWORD(2, 2), &wsadata);
        // TODO(yourtayu@gmail.com): read config file.
        Config * config = Config::GetInstance();
        config->ReadConfig();
        // Start streaming media server or connect streaming media server.

        // Create controller server.
        sdl_controller_ = new SDLController(config->GetValue("ip"), config->GetValue("port"));
        sdl_controller_->ListenSocket();
        return MeriStatus();
    }

    MeriStatus MeriServer::Deinit()
    {
        return MeriStatus();
    }

    MeriStatus MeriServer::EncodeFrame()
    {
        return MeriStatus();
    }

} // !namespace meri

