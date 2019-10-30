#pragma once
#include "Message.h"

class GameObject;

class CollisionMessage :
	public Message
{
protected:
	GameObject* _x;
	GameObject* _y;

public:
	CollisionMessage(GameObject* x, GameObject* y);
	virtual ~CollisionMessage();

	GameObject* GetColliderOne()	const	{ return _x; }
	GameObject*	GetColliderTwo()	const	{ return _y; }
};

