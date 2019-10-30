#include "InputComponent.h"
#include "GameObject.h"

InputComponent::InputComponent(GameObject* x) 
	: Component("input", x)
{
}


InputComponent::~InputComponent()
{
}

void InputComponent::Start()
{
	_parent->RegisterListener("keypress", this);
}

void InputComponent::Update(float deltaTime)
{
}

void InputComponent::OnMessage(Message* m)
{	/* Non in uso
	if (m->GetMessageType() == "keypress")
	{
	
	}
	*/
}

void InputComponent::End()
{
	_parent->UnregisterListener("keypress", this);
}