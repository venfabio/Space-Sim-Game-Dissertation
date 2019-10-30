#include "CursorController.h"
#include "GameObject.h"
#include "Message.h"
#include "KeyPressMessage.h"

CursorController::CursorController(GameObject* x)
	: InputComponent(x)
{
	_active = false;
	_up = false;
	_down = false;
	_screen = 0;
	_currPos = 2;

	_pos[0] = glm::vec3(-0.5f, 0.7f, 0.0f);
	_pos[1] = glm::vec3(-0.5f, 0.5f, 0.0f);
	_pos[2] = glm::vec3(-0.5f, 0.3f, 0.0f);
	_pos[3] = glm::vec3(-0.5f, 0.1f, 0.0f);
	_pos[4] = glm::vec3(-0.5f, -0.1f, 0.0f);
	_pos[5] = glm::vec3(-0.5f, -0.3f, 0.0f);
	_pos[6] = glm::vec3(-0.5f, -0.5f, 0.0f);
	_pos[7] = glm::vec3(-0.5f, -0.7f, 0.0f);
	_pos[8] = glm::vec3(-0.5f, -0.9f, 0.0f);
	_pos[9] = glm::vec3(-0.5f, -1.1f, 0.0f);

	_parent->SetPos(_pos[_currPos]);

	Start();
}


CursorController::~CursorController()
{
}

void CursorController::Start()
{
	_parent->RegisterListener("keypress", this);
}

void CursorController::Update(float deltaTime)
{
	/*
	if (_up)
		ShiftUp();

	if (_down)
		ShiftDown();
		*/
}

void CursorController::OnMessage(Message* m)
{
	if (m->GetMessageType() == "keypress")
	{
		KeyPressMessage* kpm = (KeyPressMessage*)m;
		switch (kpm->GetKey())
		{
		case 8:
			if (kpm->GetDown() == false)
			{
				_screen = 0;
				_currPos = 2;
				_parent->SetPos(_pos[_currPos]);
			}
			break;
			case 13:
				if (kpm->GetDown() == false)
				{
					if (_screen == 0)
					{
						_screen = 1;
						_currPos = 0;
						_parent->SetPos(_pos[_currPos]);
					}
				}
			break;
			case 38: // Arrow Up
				if (kpm->GetDown() == false)
					ShiftUp();
				break;
			case 40: // Arrow Down
				if (kpm->GetDown() == false)
					ShiftDown();
				break;
		}
	}
}

void CursorController::End()
{
	_parent->UnregisterListener("keypress", this);
}

void CursorController::ShiftUp()
{
	if (_screen == 0 && _currPos == 3)
	{
		_currPos--;
		_parent->SetPos(_pos[_currPos]);
	}
	if (_screen == 1 && _currPos > 0)
	{
		_currPos--;
		_parent->SetPos(_pos[_currPos]);
	}
}

void CursorController::ShiftDown()
{
	if (_screen == 0 && _currPos == 2)
	{
		_currPos++;
		_parent->SetPos(_pos[_currPos]);
	}

	if (_screen == 1 && _currPos < _maxPos)
	{
		_currPos++;
		_parent->SetPos(_pos[_currPos]);
	}
}

void CursorController::SetMaximumPos(int x)
{
	_maxPos = x;
}