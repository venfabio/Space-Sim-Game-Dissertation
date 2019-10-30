#pragma once
#include "GameObject.h"
#include "StatusComponent.h"

class TestEnemy :
	public GameObject
{
private:
	StatusComponent* _status;	

public:
	TestEnemy();
	~TestEnemy();

	virtual void Update(float deltaTime);
	virtual void OnMessage(Message* m);
};

