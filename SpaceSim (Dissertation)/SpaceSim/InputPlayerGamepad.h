#pragma once
#include "GamepadInputComponent.h"
class InputPlayerGamepad :
	public GamepadInputComponent
{
public:
	InputPlayerGamepad(GameObject* x);
	virtual ~InputPlayerGamepad();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

private:
	XINPUT_STATE state;

	// Movements
	void MoveLeft(float dt);
	void MoveRight(float dt);
	void MoveForward(float dt);
	void MoveBackward(float dt);

	// Rotations
	void RotateLeft(float dt);
	void RotateRight(float dt);
	void RotateUp(float dt);
	void RotateDown(float dt);

	void ResetAngle(float dt);
};

