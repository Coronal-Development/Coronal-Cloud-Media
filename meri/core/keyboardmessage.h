#ifndef MERI_KEY_BOARD_MESSAGE_H_
#define MERI_KEY_BOARD_MESSAGE_H_
#include "datamessage.h"
namespace meri
{
	class KeyboardMessage :public DataMessage
	{
	public:
		KeyboardMessage(DataMessageType type, int which_button,int status);
		~KeyboardMessage() = default;

		int which_button_;
	private:
		

	};
}

#endif // !MERI_KEY_BOARD_MESSAGE_H_
