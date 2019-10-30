#include "LandedMessage.h"


LandedMessage::LandedMessage(Planet* p)
	: Message("landed")
{
	planet = p;
}


LandedMessage::~LandedMessage()
{
}
