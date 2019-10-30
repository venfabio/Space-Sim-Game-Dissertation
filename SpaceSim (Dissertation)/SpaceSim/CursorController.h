#pragma once
#include <GLM\glm.hpp>
#include "InputComponent.h"

class CursorController :
	public InputComponent
{
public:
	CursorController(GameObject* x);
	virtual ~CursorController();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

	int GetCurrPos()				{ return _currPos; }
	void SetMaximumPos(int x);

private:
	bool _active;
	bool _up;
	bool _down;
	bool _confirm;

	int _currPos;
	int _screen;
	int _maxPos;

	glm::vec3 _pos[9];

	void ShiftUp();
	void ShiftDown();
};

