#include "KeyPressMessage.h"


KeyPressMessage::KeyPressMessage(int key, bool down)
	: Message("keypress")
{
	_key = key;
	_down = down;
}


KeyPressMessage::~KeyPressMessage()
{
}
