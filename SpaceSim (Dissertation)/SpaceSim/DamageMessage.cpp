#include "DamageMessage.h"


DamageMessage::DamageMessage(int dmg)
	: Message("damage")
{
	_damage = dmg;
}


DamageMessage::~DamageMessage()
{
}
