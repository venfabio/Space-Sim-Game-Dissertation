#pragma once

#include "GameObject.h"
#include "StatusComponent.h"
#include "InventoryComponent.h"

class Message;

class Player :
	public GameObject
{
private:
	StatusComponent* _status;	// need it here badly.
	InventoryComponent* ic;

public:
	Player();
	~Player();

	virtual void Update(float deltaTime);
	virtual void OnMessage(Message* m);
};

