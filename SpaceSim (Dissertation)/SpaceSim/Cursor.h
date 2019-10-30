#pragma once
#include "GameObject.h"
#include "CursorController.h"

class Cursor :
	public GameObject
{
private:
	CursorController* cc;
public:
	Cursor();
	~Cursor();

	virtual void Update(float dt);
	virtual void OnMessage(Message* m);
	
	int GetCurrPos();
	void SetMaximumPos(int x);
};

