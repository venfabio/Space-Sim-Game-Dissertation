#pragma once
#include "Message.h"

class KeyPressMessage :
	public Message
{
protected:
	int _key;
	bool _down;

public:
	KeyPressMessage(int key, bool down);
	virtual ~KeyPressMessage();

	int GetKey()				const	{ return _key; }
	bool GetDown()				const	{ return _down; }
};

