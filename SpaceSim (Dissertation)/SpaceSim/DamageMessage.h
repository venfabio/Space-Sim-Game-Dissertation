#pragma once
#include "Message.h"

class GameObject;

// TODO: Target type?

class DamageMessage :
	public Message
{
protected:
	GameObject* _targetType;
	int _damage;

public:
	DamageMessage(int dmg);
	virtual ~DamageMessage();

	GameObject* GetTarget()		const	{ return _targetType; }
	int GetDamage()				const	{ return _damage; }
};

