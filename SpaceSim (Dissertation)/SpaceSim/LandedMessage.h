#pragma once
#include "Message.h"

class Planet;

class LandedMessage :
	public Message
{
private:
	Planet* planet;

public:
	LandedMessage(Planet* p);
	virtual ~LandedMessage();

	Planet* GetPlanet()				{ return planet; }
};

