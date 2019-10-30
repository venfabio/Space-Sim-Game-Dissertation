#include "SphereCollisionComponent.h"
#include "GameObject.h"
#include "Message.h"
#include "CollisionMessage.h"

#include "Game.h"	// Need to get the game objects from somewhere...
#include "SceneManager.h"
#include "Scene.h"

SphereCollisionComponent::SphereCollisionComponent(GameObject* x, float radius)
	: Component("collision", x)
{
	_radius = radius;
	_greaterRadius = radius * 1.5f;
}


SphereCollisionComponent::~SphereCollisionComponent()
{
}

void SphereCollisionComponent::Start()
{
	_parent->RegisterListener("collision", this);
}

void SphereCollisionComponent::Update(float deltaTime)
{
	// Grab the gameobjects from the scene
	std::vector<GameObject*>& gs = Game::TTS->GetSceneManager()->GetCurrentScene()->GetGameObjects();

	for (int i = 0; i < gs.size(); i++)
	{
		GameObject *g = gs[i];
		if (g != _parent && g->IsAlive())
			CollideWithSphere(g);
	}
}

void SphereCollisionComponent::OnMessage(Message* m)
{
	// ??? Se ricevi un messaggio di collision calcola la risposta?
}

void SphereCollisionComponent::End()
{
	_parent->UnregisterListener("collision", this);
}

void SphereCollisionComponent::CollideWithSphere(GameObject* other)
{
	glm::vec3 x = this->_parent->GetPos();
	glm::vec3 y = other->GetPos();

	SphereCollisionComponent* another = dynamic_cast<SphereCollisionComponent*>(other->GetComponent("collision"));
	
	if (another != NULL)	// Not every object has collision component, thus is not collidable.

	{
		float radii = this->GetRadius() + another->GetRadius();

		float dist = glm::distance(x, y);

		float res = dist - radii;

		if (res < 0)
		{
			// Send message to both objects
			CollisionMessage m(_parent, other);
			_parent->OnMessage(&m);
			other->OnMessage(&m);
		}
	}
}