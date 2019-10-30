#include "CameraController.h"
#include "GameObject.h"
#include "Camera.h"
#include "InputComponent.h"
#include "Message.h"
#include "KeyPressMessage.h"

#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>


CameraController::CameraController(Camera* x)
	: InputComponent(x)
{
	theta = 0;
	t = 4.6;
	h = -1.0f;

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

	Camera* c = static_cast<Camera*>(_parent);
	target = c->GetCameraTarget();

	Start();
}


CameraController::~CameraController()
{
}

void CameraController::Start()
{
	_parent->RegisterListener("keypress", this);
}

void CameraController::Update(float deltaTime)
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
		YawLeft(deltaTime);

	if (_yawRight)
		YawRight(deltaTime);

	if (_pitchUp)
		PitchUp(deltaTime);

	if (_pitchDown)
		PitchDown(deltaTime);

	if (_rotateLeft)
		RotateLeft(deltaTime);

	if (_rotateRight)
		RotateRight(deltaTime);

	if (_rotateUp)
		RotateUp(deltaTime);

	if (_rotateDown)
		RotateDown(deltaTime);
}

void CameraController::OnMessage(Message* m)
{
	if (m->GetMessageType() == "keypress")
	{
		KeyPressMessage* kpm = (KeyPressMessage*)m;
		switch (kpm->GetKey())
		{
			case 37: //Arrow left
				_yawLeft = kpm->GetDown();
				break;
			case 38: // Arrow Up
				_pitchDown = kpm->GetDown();
				break;
			case 39: // Arrow Right
				_yawRight = kpm->GetDown();
				break;
			case 40: // Arrow Down
				_pitchUp = kpm->GetDown();
				break;
			case 65: // A
				_left = kpm->GetDown();
				break;
			case 68: // D
				_right = kpm->GetDown();
				break;
			case 69: //E
				_rotateRight = kpm->GetDown();
				break;
			case 70: //F
				_rotateDown = kpm->GetDown();
				break;
			case 81: //Q
				_rotateLeft = kpm->GetDown();
				break;
			case 82: //R
				_rotateUp = kpm->GetDown();
				break;
			case 87: // W
				_forward = kpm->GetDown();
				break;
			case 83: // S
				_backward = kpm->GetDown();
		}
	}
}

void CameraController::End()
{
	_parent->UnregisterListener("keypress", this);
}

void CameraController::MoveLeft(float dt)
{
	glm::vec3 temp(5, 0, 0);
	temp = glm::rotateX(temp, target->GetAngleX());
	temp = glm::rotateY(temp, target->GetAngleY());
	_parent->SetPos(_parent->GetPos() - temp * dt);
}

void CameraController::MoveRight(float dt)
{
	glm::vec3 temp(5, 0, 0);
	temp = glm::rotateX(temp, target->GetAngleX());
	temp = glm::rotateY(temp, target->GetAngleY());
	_parent->SetPos(_parent->GetPos() + temp * dt);
}

void CameraController::MoveForward(float dt)
{
	glm::vec3 temp(0, 0, 5);
	temp = glm::rotateX(temp, target->GetAngleX());
	temp = glm::rotateY(temp, target->GetAngleY());
	_parent->SetPos(_parent->GetPos() + temp * dt);
}

void CameraController::MoveBackward(float dt)
{
	glm::vec3 temp(0, 0, 5);
	temp = glm::rotateX(temp, target->GetAngleX());
	temp = glm::rotateY(temp, target->GetAngleY());
	_parent->SetPos(_parent->GetPos() - temp * dt);
}

void CameraController::YawLeft(float dt)
{
	
	//http://www.gamedev.net/page/resources/_/technical/math-and-physics/a-simple-quaternion-based-camera-r1997
	glm::vec3 a = { 0, 2, 0 };
	glm::quat rotation;
	theta = 0.5f * dt;
	rotation.x = a.x * sin(theta / 2);
	rotation.y = a.y * sin(theta / 2);
	rotation.z = a.z * sin(theta / 2);
	rotation.w = cos(theta / 2);
	Camera* c = static_cast<Camera*>(_parent);		// we are 100% sure that _parent is a Camera object (the construtor says so!) 
	c->SetCameraRotation(rotation);

	//If it rotates on the left, it should also slightly move on the right
	t = t + 1.0f * dt;
	_parent->SetPosX(3 * cos(t) + target->GetPosX());
	_parent->SetPosZ(3 * sin(t) + target->GetPosZ());
	
}

void CameraController::YawRight(float dt)
{
	
	// Magic. Don't touch it.
	glm::vec3 a = { 0, -2, 0 };
	glm::quat rotation;
	theta = 0.5f * dt;
	rotation.x = a.x * sin(theta / 2);
	rotation.y = a.y * sin(theta / 2);
	rotation.z = a.z * sin(theta / 2);
	rotation.w = cos(theta / 2);
	Camera* c = static_cast<Camera*>(_parent);
	c->SetCameraRotation(rotation);

	t = t - 1.0f * dt;
	_parent->SetPosX(3 * cos(t) + target->GetPosX());
	_parent->SetPosZ(3 * sin(t) + target->GetPosZ());
	
}
// Actually goes down...
void CameraController::PitchUp(float dt)
{
	glm::vec3 a = { 1, 0, 0 };
	glm::quat rotation;
	theta = 0.5f * dt;
	rotation.x = a.x * sin(theta / 2);
	rotation.y = a.y * sin(theta / 2);
	rotation.z = a.z * sin(theta / 2);
	rotation.w = cos(theta / 2);
	Camera* c = static_cast<Camera*>(_parent);
	c->SetCameraRotation(rotation);
	
	// Move Up
	h = h - 0.5f * dt;
	_parent->SetPosY(3 * cos(h) + target->GetPosY());
	_parent->SetPosZ(3 * sin(h) + target->GetPosZ());
}

void CameraController::PitchDown(float dt)
{
	glm::vec3 a = { -1, 0, 0 };
	glm::quat rotation;
	theta = 0.5f * dt;
	rotation.x = a.x * sin(theta / 2);
	rotation.y = a.y * sin(theta / 2);
	rotation.z = a.z * sin(theta / 2);
	rotation.w = cos(theta / 2);
	Camera* c = static_cast<Camera*>(_parent);
	c->SetCameraRotation(rotation);
	
	// Move Down
	h = h + 0.5f * dt;
	_parent->SetPosY(3 * cos(h) + target->GetPosY());
	_parent->SetPosZ(3 * sin(h) + target->GetPosZ());
}

void CameraController::RotateLeft(float dt)
{
	t = t - 0.5f * dt;
	_parent->SetPosX(3 * cos(t) + target->GetPosX());
	_parent->SetPosZ(3 * sin(t) + target->GetPosZ());
}

void CameraController::RotateRight(float dt)
{
	t = t + 0.5f * dt;
	_parent->SetPosX(3 * cos(t) + target->GetPosX());
	_parent->SetPosZ(3 * sin(t) + target->GetPosZ());
}

void CameraController::RotateUp(float dt)
{
	h = h + 0.5f * dt;
	_parent->SetPosY(3 * cos(h) + target->GetPosY());
	_parent->SetPosZ(3 * sin(h) + target->GetPosZ());
}

void CameraController::RotateDown(float dt)
{
	h = h - 0.5f * dt;
	_parent->SetPosY(3 * cos(h) + target->GetPosY());
	_parent->SetPosZ(3 * sin(h) + target->GetPosZ());
}