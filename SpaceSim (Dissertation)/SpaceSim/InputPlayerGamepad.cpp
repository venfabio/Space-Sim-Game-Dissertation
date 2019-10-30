#include "InputPlayerGamepad.h"
#include "GameObject.h"
#include "Message.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>

InputPlayerGamepad::InputPlayerGamepad(GameObject* x)
	: GamepadInputComponent(x)
{
	/*
	A = 0;
	B = 1;
	X = 2;
	Y = 3;

	DPad_Up = 4;
	DPad_Down = 5;
	DPad_Left = 6;
	DPad_Right = 7;

	L_Shoulder = 8;
	R_Shoulder = 9;

	Start = 12;
	Back = 13;
	*/
	Start();
}


InputPlayerGamepad::~InputPlayerGamepad()
{
}

void InputPlayerGamepad::Start()
{
	_parent->RegisterListener("padinput", this);
}

void InputPlayerGamepad::Update(float deltaTime)
{
	GamepadInputComponent::Update(deltaTime);	// ???

	if (GamepadInputComponent::GetButtonDown(XButtons.X))
		MoveLeft(deltaTime);

	GamepadInputComponent::RefreshState();
}

void InputPlayerGamepad::OnMessage(Message* m)
{

}

void InputPlayerGamepad::End()
{
	_parent->UnregisterListener("keypress", this);
}

void InputPlayerGamepad::MoveLeft(float dt)
{
	glm::vec3 temp(5, 0, 0);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() - temp * dt);

	if (_parent->GetAngleZ() < 0.5f)
		_parent->SetAngleZ(_parent->GetAngleZ() + 0.9f * dt);
}

void InputPlayerGamepad::MoveRight(float dt)
{
	glm::vec3 temp(5, 0, 0);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() + temp * dt);

	if (_parent->GetAngleZ() > -0.5f)
		_parent->SetAngleZ(_parent->GetAngleZ() - 0.9f * dt);
}

void InputPlayerGamepad::MoveForward(float dt)
{
	glm::vec3 temp(0, 0, 5);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() + temp * dt);
}

void InputPlayerGamepad::MoveBackward(float dt)
{
	glm::vec3 temp(0, 0, 5);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() - temp * dt);
}

void InputPlayerGamepad::RotateLeft(float dt)
{
	_parent->SetAngleY(_parent->GetAngleY() - 0.9f * dt);
}

void InputPlayerGamepad::RotateRight(float dt)
{
	_parent->SetAngleY(_parent->GetAngleY() + 0.9f * dt);
}

// Inverted on purpose
void InputPlayerGamepad::RotateUp(float dt)
{
	_parent->SetAngleX(_parent->GetAngleX() + 0.9f * dt);
}
// Inverted on purpose
void InputPlayerGamepad::RotateDown(float dt)
{
	_parent->SetAngleX(_parent->GetAngleX() - 0.9f * dt);
}

void InputPlayerGamepad::ResetAngle(float dt)
{
	// Bring back the ship into a normal position
	if (_parent->GetAngleZ() > 0 && GamepadInputComponent::GetButtonDown(6) == false)
		_parent->SetAngleZ(_parent->GetAngleZ() - 0.9f * dt);

	if (_parent->GetAngleZ() < 0 && GamepadInputComponent::GetButtonDown(7) == false)
		_parent->SetAngleZ(_parent->GetAngleZ() + 0.9f * dt);
}