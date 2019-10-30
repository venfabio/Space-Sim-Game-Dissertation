#pragma once
#include "GameObject.h"
class LaserBeam :
	public GameObject
{
private:

	float _maxSpeed;
	float _lifetime;
	float _invulnerable;

	static const float MAX_LIFETIME;

	bool _isFired;

public:
	LaserBeam();
	~LaserBeam();

	virtual void Update(float deltaTime);
	virtual void OnMessage(Message* m);

	void Fire(glm::vec3 pos, glm::vec3 angle);

	bool IsFired() { return _isFired; }
};

