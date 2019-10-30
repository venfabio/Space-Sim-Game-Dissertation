#pragma once
#include "GameObject.h"
#include "InventoryComponent.h"

class Message;

class Planet :
	public GameObject
{
private:
	bool _landable;
	InventoryComponent* ic;

public:
	Planet(glm::vec3 pos, int param);
	~Planet();

	void OnMessage(Message *m);
};

