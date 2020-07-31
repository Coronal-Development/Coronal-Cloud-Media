#ifndef HOOK_H_
#define HOOK_H_
#include "common/common.h"

namespace meri
{
	class SocketObject
	{
	public:
		int type_;
		std::string name_;
		SOCKET* socket_handl_;
		std::string target_ip_;
		std::string target_port_;
		bool receive_thread_flag_;
		std::thread receive_stream_thread_;
		void clientsocket()
		{
			char buffer[1024]{};
			receive_thread_flag_ = true;
			while (receive_thread_flag_)
			{
				// TODO(yourtata@gmail.com): Addition daemon thread logic. if can't receive TargetInformation for a long time,
				// should it free this client socket and remove it from the socket map of Media Server.
				memset(buffer, 0, sizeof(buffer));
				int res = recv(*socket_handl_, buffer, sizeof(buffer), NULL);
				if (res <= 0) continue;
				if (SetTargetInformation() == MeriStatus::kNomal) break;
			}
			while (receive_thread_flag_)
			{
				int res = recv(*socket_handl_, buffer, sizeof(buffer), NULL);
				if (res <= 0) continue;
				ForwardMediaStreaming();
			}
			std::cout << "Exit thread of ReceiveFromSockets!" << std::endl;
			return ;

		}
		MeriStatus SetTargetInformation()
		{
			return MeriStatus();
		}
		MeriStatus ForwardMediaStreaming()
		{
			return MeriStatus();
		}
	};

	class ClientObject
	{

		
	};

	class MediaServices
	{
	public:
		SINGLETON_DEFINE(MediaServices)
		~MediaServices() = default;
		MeriStatus Init();
		MeriStatus Deinit(void* args);
		MeriStatus ReceiveStream(MediaBuffer * media_buffer);
		MeriStatus SendStream();



	private:
		MeriStatus MediaServices::InitWindowsSocket();
		MeriStatus MediaServices::InitFFmpeg();
		void ListenSocket(std::string ip = "127.0.0.1", int port = 9566);
		MediaServices() = default;

		std::map<int, SocketObject*> sockets_;
		bool listen_socket_thread_flag_;
		std::thread listen_socket_thread_;

	}; // ! class Hook
	
} // ! namespace meri

#endif // !HOOK_H_
