#ifndef MERI_MOUSE_MESSAGE_H_
#define MERI_MOUSE_MESSAGE_H_
#include "datamessage.h"

namespace meri
{
	class MouseMessage : public DataMessage
	{
	public:
		MouseMessage(DataMessageType type, int x = 0, int y = 0,int delta = 0, int status = 0)
			:DataMessage(type,sizeof(*this))
			,x_(x)
			, y_(y)
			, delta_(delta)
			, status_(status) 
		{}
		~MouseMessage() = default;
		static MouseMessage::DataMessageType CoverButtonType(int which, bool pressed);
		int x_, y_, delta_;
		int status_;
	private:

	};
} // !namespace meri
#endif // !MERI_MOUSE_MESSAGE_H_
