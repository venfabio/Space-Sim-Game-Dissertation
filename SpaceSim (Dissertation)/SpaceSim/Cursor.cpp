#include "Cursor.h"
#include "CursorController.h"

Cursor::Cursor()
{
	cc = new CursorController(this);
}


Cursor::~Cursor()
{
}

void Cursor::Update(float dt)
{
	GameObject::Update(dt);
}

void Cursor::OnMessage(Message* m)
{
	GameObject::OnMessage(m);
}

int Cursor::GetCurrPos()
{
	int x = cc->GetCurrPos();
	return x;
}

void Cursor::SetMaximumPos(int x)
{
	cc->SetMaximumPos(x);
}