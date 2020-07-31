#include "common/common.h"

namespace meri
{
	using SystemKey = unsigned short;
	using SDLKey = unsigned int;
	class Controller :public ModuleVirtualInterface
	{
	public:
		SINGLETON_DEFINE(Controller)
		~Controller();
		int Init(void* merirect) override;
		int Start(void* args) override;
		int Stop(void* args) override;
		int Deinit(void* args) override;
		int IOCtrl(int command, int argsize, void* arg) override;
		int Notify(void* args) override;
		int Raw(void* arg, int* size) override;
	private:
		Controller();
		friend void MapSdlKeyToSystem();
		class meri::MeriRect* work_rect_;
		std::unordered_map<SDLKey, SystemKey> keymap_;
	}; // ! class meri

} // ! namespace meri