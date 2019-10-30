#include "FlightComponent.h"
#include "GameObject.h"
#include "Message.h"

FlightComponent::FlightComponent(GameObject* x)
	: Component("flight", x)
{
}


FlightComponent::~FlightComponent()
{
}

void FlightComponent::Start()
{
	_parent->RegisterListener("move", this);
}

void FlightComponent::Update(float dt)
{

}

void FlightComponent::OnMessage(Message* m)
{
	if (m->GetMessageType() == "thrust")
	{
		//ThrustMessage* tm = (ThrustMessage*)msg;
		//_velocity += tm->GetThrust();
	}
}

void FlightComponent::End()
{
	_parent->UnregisterListener("move", this);
}