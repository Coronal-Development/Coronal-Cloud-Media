#include "../../core/common/common.h"
#include "../../core/controller.h"

static meri::Controller* controller = meri::Controller::GetInstance();

namespace meri
{
	ModuleVirtualInterface* GetModule()
	{
		controller->name_ = "controller-sdl";
		controller->type_ = meri::ModuleType::controller;
		return controller;
	}
}