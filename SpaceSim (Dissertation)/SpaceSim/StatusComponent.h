#pragma once
#include <GLM\glm.hpp>
#include "Component.h"
class StatusComponent :
	public Component
{
public:
	StatusComponent(GameObject* x, int hp);
	virtual ~StatusComponent();

	int _maxHp;
	int _hp;
	int _maxSpeed;		

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

	int GetMaxHp()		const	{ return _maxHp; }
	int GetHp()			const	{ return _hp; }
	
	void SetMaxHp(int x)		{ _maxHp = x; }
	void SetHp(int x)			{ _hp = x; }
};

