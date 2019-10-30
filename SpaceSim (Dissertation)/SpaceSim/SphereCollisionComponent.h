#pragma once
#include "Component.h"
class SphereCollisionComponent :
	public Component
{
public:
	SphereCollisionComponent(GameObject* x, float radius);
	virtual ~SphereCollisionComponent();

	float	_radius;			// The radius of the bounding sphere
	float	_greaterRadius;		// ???

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

	// Collision specific
	void CollideWithSphere(GameObject* other); //Gameobject->GetComponent->GetRadius

	float GetRadius()			{ return _radius; }			// Useful.
	float GetGreaterRadius()	{ return _greaterRadius; }	// Even more useful.
};

