#pragma once
#include <GLM\glm.hpp>
#include "Component.h"
class FlightComponent :
	public Component
{
protected: 
	glm::vec3	_velocity;
	glm::vec3	_orientation;

public:
	FlightComponent(GameObject* x);
	virtual ~FlightComponent();

	virtual void Start();

	virtual void Update(float dt);

	virtual void OnMessage(Message* m);

	virtual void End();
};

