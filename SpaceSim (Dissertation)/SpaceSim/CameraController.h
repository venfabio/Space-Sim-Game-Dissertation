#pragma once
#include <math.h>
#include "InputComponent.h"

class Camera;

class CameraController :
	public InputComponent
{
public:
	CameraController(Camera* x);
	~CameraController();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

private:

	float theta;
	float t;
	float h;

	GameObject* target;

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

	bool _rotateRight;
	bool _rotateLeft;
	bool _rotateUp;
	bool _rotateDown;

	// Movements
	void MoveLeft(float dt);
	void MoveRight(float dt);
	void MoveForward(float dt);
	void MoveBackward(float dt);

	// Rotations
	void YawLeft(float dt);
	void YawRight(float dt);
	void PitchUp(float dt);
	void PitchDown(float dt);

	void RotateLeft(float dt);
	void RotateRight(float dt);
	void RotateUp(float dt);
	void RotateDown(float dt);
};

