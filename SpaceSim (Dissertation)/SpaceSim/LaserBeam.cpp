#include "LaserBeam.h"
#include "SphereCollisionComponent.h"

#include "Message.h"
#include "DamageMessage.h"
#include "CollisionMessage.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>

const float LaserBeam::MAX_LIFETIME = 2.0f;

LaserBeam::LaserBeam()
{
	new SphereCollisionComponent(this, 0.1f);

	_isFired = false;
	_lifetime = 0;
	_invulnerable = 0;
}


LaserBeam::~LaserBeam()
{
}

void LaserBeam::Update(float deltaTime)
{
	// Update only if it is fired
	if (_isFired)
	{
		GameObject::Update(deltaTime);

		// Shoot forward
		glm::vec3 temp(0, 0, 15);
		temp = glm::rotateX(temp, _angle.x);
		temp = glm::rotateY(temp, _angle.y);
		_position = _position + temp * deltaTime;

		_lifetime = _lifetime + deltaTime;
		_invulnerable = _invulnerable + deltaTime;
		
		if (_lifetime > MAX_LIFETIME)
		{
			_isFired = false;
			_alive = false;
			_lifetime = 0;
		}
	}
}

void LaserBeam::OnMessage(Message* m)
{
	GameObject::OnMessage(m);

	if (m->GetMessageType() == "collision" && _invulnerable > 1.00f)
	{
		DamageMessage *dm = new DamageMessage(60);
		CollisionMessage* cm = (CollisionMessage*)m;
		// If the laser beam is involved in a collision, send a damage message to the collided object
		if (cm->GetColliderOne() == this)
		{
			_alive = false;
			cm->GetColliderTwo()->OnMessage(dm);
		}
		if (cm->GetColliderTwo() == this)
		{
			_alive = false;
			cm->GetColliderOne()->OnMessage(dm);
		}
	}
}

void LaserBeam::Fire(glm::vec3 pos, glm::vec3 angle)
{
	// When fired, the laser beam needs to know where it is and orientation
	if (!_isFired)
	{
		_isFired = true;
		_alive = true;
 		SetPos(pos);
		SetAngle(angle);
	}
}