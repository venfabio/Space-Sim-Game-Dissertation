#include "Component.h"
#include "GameObject.h"
#include "Game.h"

Component::Component(std::string type, GameObject* parent)
{
	_componentType = type;
	_parent = parent;

	_parent->AddComponent(this);
}


Component::~Component()
{
}

void Component::Broadcast(Message* m)
{
	Game::TTS->Broadcast(m);
}