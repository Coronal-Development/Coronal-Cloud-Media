#include "MediaServices.h"

#include <windows.h>

extern "C" {
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/base64.h>
}
#include "common/modulevirtualinterface.h"
#include "config/config.h"

#pragma comment (lib, "ws2_32.lib")

namespace meri
{
    static MediaServices* kHook = MediaServices::GetInstance();
    static SOCKET kMediaServerListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_UDP);
    MeriStatus MediaServices::Init()
    {
        InitWindowsSocket();
        InitFFmpeg();
        listen_socket_thread_.swap(std::thread(&MediaServices::ListenSocket, this, "12",9566));
        return MeriStatus();
    }

    MeriStatus MediaServices::Deinit(void* args)
    {
        for (auto i : sockets_)
        {
            i.second->receive_thread_flag_ = false;
            i.second->receive_stream_thread_.detach();
        }
        return MeriStatus();
    }

    MeriStatus MediaServices::ReceiveStream(MediaBuffer* media_buffer)
    {
        return MeriStatus();
    }

    MeriStatus MediaServices::SendStream()
    {
        return MeriStatus();
    }

    MeriStatus MediaServices::InitWindowsSocket()
    {
        srand(time(0));
        WSADATA wd;
        if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
            return MeriStatus();
        return MeriStatus();
    }

    MeriStatus MediaServices::InitFFmpeg()
    {
        av_register_all();
        avcodec_register_all();
        avformat_network_init();
        return MeriStatus();
    }

    void MediaServices::ListenSocket(std::string ip, int port)
    {
        sockaddr_in address;
        memset(&address, 0, sizeof(address));
        address.sin_family = PF_INET;
        address.sin_addr.s_addr = inet_addr(ip.c_str());
        address.sin_port = htons(port);
  
        bind(kMediaServerListenSocket, (SOCKADDR*)&address, sizeof(sockaddr_in));
        listen(kMediaServerListenSocket, 20);
        SOCKADDR* client_address = nullptr;
        listen_socket_thread_flag_ = true;
        while (listen_socket_thread_flag_)
        {
            static int i = 0;
            client_address = new SOCKADDR();
            int nSize = sizeof(SOCKADDR);
            SocketObject* clientsocket = new SocketObject();
            *(SOCKET*)(clientsocket->socket_handl_) = accept(kMediaServerListenSocket, (SOCKADDR*)&*client_address, &nSize);
            clientsocket->receive_stream_thread_.swap(std::thread(&SocketObject::clientsocket, clientsocket));
            sockets_.insert(std::make_pair(i++, clientsocket));
            client_address = nullptr;
            // Exit critical zone.
        }
        std::cout << "Exit thread of ListenSocket!" << std::endl;
    }
} // ! namespace meri