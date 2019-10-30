#include "InputPlayer.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "Message.h"
#include "KeyPressMessage.h"
#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>

// Ship's movements, animations and stuff.

InputPlayer::InputPlayer(GameObject* x)
	: InputComponent(x)
{
	// WASD
	_left = false;
	_right = false;
	_forward = false;
	_backward = false;

	// Arrows
	_pitchUp = false;
	_pitchDown = false;
	_yawLeft = false;
	_yawRight = false;

	_shots = 4;
	_recharge = 0;

	// TODO: trovargli una sistemazione decente, o lasciare che il gameobject inizializzi i propri elementi
	Start();
}


InputPlayer::~InputPlayer()
{
}

void InputPlayer::Start()
{
	_parent->RegisterListener("keypress", this);
}

void InputPlayer::Update(float deltaTime)
{
	if (_left)
		MoveLeft(deltaTime);

	if (_right)
		MoveRight(deltaTime);

	if (_forward)	
		MoveForward(deltaTime);

	if (_backward)	
		MoveBackward(deltaTime);

	if (_yawLeft)
		RotateLeft(deltaTime);

	if (_yawRight)
		RotateRight(deltaTime);

	if (_pitchUp)
		RotateUp(deltaTime);

	if (_pitchDown)
		RotateDown(deltaTime);

	if (_fire)
		FireOneShot();

	//ResetAngle(deltaTime);

	_recharge = _recharge + deltaTime;
	if (_recharge > 2.5f && _shots <= 4)
	{
		_recharge = 0;
		_shots++;
	}
}

void InputPlayer::OnMessage(Message* m)
{
	if (m->GetMessageType() == "keypress")
	{
		KeyPressMessage* kpm = (KeyPressMessage*)m;
		switch (kpm->GetKey())
		{
			case 32: // SPAAAAAAAAACE
				_fire = kpm->GetDown();
				break;
			case 37: //Arrow left
				_yawLeft = kpm->GetDown();
				break;
			case 38: // Arrow Up
				_pitchUp = kpm->GetDown();
				break;
			case 39: // Arrow Right
				_yawRight = kpm->GetDown();
				break;
			case 40: // Arrow Down
				_pitchDown = kpm->GetDown();
				break;
			case 65: // A
				_left = kpm->GetDown();
				break;
			case 68: // D
				_right = kpm->GetDown();
				break;
			case 87: // W
				_forward = kpm->GetDown();
				break;
			case 83: // S
				_backward = kpm->GetDown();
				break;
		}
	}
}

void InputPlayer::End()
{
	_parent->UnregisterListener("keypress", this);
}

//TODO: sistemare animazioni

void InputPlayer::MoveLeft(float dt)
{
	glm::vec3 temp(5, 0, 0);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() - temp * dt);

	//if (_parent->GetAngleZ() < 0.5f)
		//_parent->SetAngleZ(_parent->GetAngleZ() + 0.9f * dt);
}

void InputPlayer::MoveRight(float dt)
{
	glm::vec3 temp(5, 0, 0);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() + temp * dt);

	//if (_parent->GetAngleZ() > -0.5f)
		//_parent->SetAngleZ(_parent->GetAngleZ() - 0.9f * dt);
}

void InputPlayer::MoveForward(float dt)
{
	glm::vec3 temp(0, 0, 5);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() + temp * dt);
}

void InputPlayer::MoveBackward(float dt)
{
	glm::vec3 temp(0, 0, 5);
	temp = glm::rotateX(temp, _parent->GetAngleX());
	temp = glm::rotateY(temp, _parent->GetAngleY());
	_parent->SetPos(_parent->GetPos() - temp * dt);
}

void InputPlayer::RotateLeft(float dt)
{
	_parent->SetAngleY(_parent->GetAngleY() - 1.0f * dt);
}

void InputPlayer::RotateRight(float dt)
{
	_parent->SetAngleY(_parent->GetAngleY() + 1.0f * dt);
}

// Inverted on purpose
void InputPlayer::RotateUp(float dt)
{
	_parent->SetAngleX(_parent->GetAngleX() + 0.9f * dt);
}
// Inverted on purpose
void InputPlayer::RotateDown(float dt)
{
	_parent->SetAngleX(_parent->GetAngleX() - 0.9f * dt);
}

void InputPlayer::ResetAngle(float dt)
{
	// Bring back the ship into a normal position
	if (_parent->GetAngleZ() > 0 && _left == false)
		_parent->SetAngleZ(_parent->GetAngleZ() - 0.9f * dt);

	if (_parent->GetAngleZ() < 0 && _right == false)
		_parent->SetAngleZ(_parent->GetAngleZ() + 0.9f * dt);
}

void InputPlayer::FireOneShot()
{
	if (_shots > 0)
	{
		_fire = false;	// hardfix
		_shots--;
		Message* m = new Message("fire");
		Game::TTS->GetSceneManager()->GetCurrentScene()->OnMessage(m);
	}
}