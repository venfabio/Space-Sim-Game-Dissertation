#pragma once
#include <string>

class Message
{
protected:
	std::string type;

public:
	Message(std::string t);
	virtual ~Message();

	std::string GetMessageType()		const	{ return type; }
};

