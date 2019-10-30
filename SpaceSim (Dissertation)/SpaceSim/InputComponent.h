#pragma once
#include "Component.h"

class InputComponent :
	public Component
{
public:
	InputComponent(GameObject* x);
	virtual ~InputComponent();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();
};

