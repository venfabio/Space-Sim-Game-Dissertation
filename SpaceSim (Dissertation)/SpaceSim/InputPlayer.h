#pragma once
#include "InputComponent.h"

// Spaceship movements
class InputPlayer :
	public InputComponent
{
public:
	InputPlayer(GameObject* x);
	virtual ~InputPlayer();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

private:

	// WASD
	bool _left;
	bool _right;
	bool _forward;
	bool _backward;

	// Arrows
	bool _pitchUp;
	bool _pitchDown;
	bool _yawLeft;
	bool _yawRight;

	bool _fire;

	int _shots;

	float _recharge;
	
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

	void FireOneShot();

};

