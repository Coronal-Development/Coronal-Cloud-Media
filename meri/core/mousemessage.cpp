#include "mousemessage.h"

namespace meri
{
	MouseMessage::DataMessageType MouseMessage::CoverButtonType(int which, bool is_pressed)
	{
		switch (which)
		{
		case 0:
			return MouseMessage::DataMessageType::kNull;
		case 1:
			return is_pressed ? DataMessageType::kLeftButtonDown : DataMessageType::kLeftButtonUp;
		case 2:
			return is_pressed ? DataMessageType::kRightButtonDown : DataMessageType::kRightButtonUp;
		case 3:
			return is_pressed ? DataMessageType::kMiddleButtonDown : DataMessageType::kMiddleButtonUp;
		default:
			return MouseMessage::DataMessageType::kNull;
		}
	}
} // !namespace meri
