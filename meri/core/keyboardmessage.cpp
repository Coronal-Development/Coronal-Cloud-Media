#include "keyboardmessage.h"

meri::KeyboardMessage::KeyboardMessage(DataMessageType type, int which_button, int status)
    :DataMessage(type,sizeof(*this))
    ,which_button_(which_button)
{
}
