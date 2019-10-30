#include "StatusComponent.h"
#include "GameObject.h"
#include "Message.h"

StatusComponent::StatusComponent(GameObject* x, int hp)
	: Component("status", x)
{
	_maxHp = hp;
	_hp = hp;
}


StatusComponent::~StatusComponent()
{
}

void StatusComponent::Start()
{
	_parent->RegisterListener("damage", this);		// "damage" message can also be used for healing
}

void StatusComponent::Update(float deltaTime)
{
	// ???
}

void StatusComponent::OnMessage(Message* m)
{
	if (m->GetMessageType() == "damage")
	{
		// TODO: damage message
	}
}

void StatusComponent::End()
{
	_parent->UnregisterListener("damage", this);
}