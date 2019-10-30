#include "Planet.h"
#include "SphereCollisionComponent.h"
#include "InventoryComponent.h"
#include "CollisionMessage.h"
#include "LandedMessage.h"

#include "Game.h"	// Send message to the scene
#include "SceneManager.h"
#include "Scene.h"

#include "Player.h"

Planet::Planet(glm::vec3 pos, int param)
{
	_position = pos;

	_landable = true;

	new SphereCollisionComponent(this, 2.0f);	// 2.5 ???
	ic = new InventoryComponent(this, param);
}


Planet::~Planet()
{
}

void Planet::OnMessage(Message *m)
{
	if (m->GetMessageType() == "collision")
	{
		// Sistemare
		CollisionMessage* cm = static_cast<CollisionMessage*>(m);
		if (dynamic_cast<Player*> (cm->GetColliderOne()))
		{
			LandedMessage* lm = new LandedMessage(this);
			Game::TTS->GetSceneManager()->GetCurrentScene()->OnMessage(lm);
		}
	}
	if (m->GetMessageType() == "transaction")
	{
		ic->OnMessage(m);
	}
}