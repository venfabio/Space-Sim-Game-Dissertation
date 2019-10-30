// Code based on https://lcmccauley.wordpress.com/2014/01/10/gamepadtutorial-part3/

#pragma once
#ifndef GAMEPAD_H
#define GAMEPAD_H
#include <Windows.h>
#include <XInput.h>
#include "Component.h"

// XInput Button values		// https://msdn.microsoft.com/en-us/library/microsoft.directx_sdk.reference.xinput_gamepad(v=vs.85).aspx
static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,	// Not in use anyway
	XINPUT_GAMEPAD_RIGHT_THUMB,	// Ditto.
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

// XInput Button IDs
struct XButtonIDs
{
	XButtonIDs();

	int A, B, X, Y;

	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;

	int L_Shoulder, R_Shoulder;

	int Start;
	int Back;
};

class GamepadInputComponent :
	public Component
{
private:
	XINPUT_STATE m_State; // Current gamepad state
	int m_iGamepadIndex;  // Gamepad index (eg. 1,2,3,4)

	static const int ButtonCount = 14;    // Total gamepad buttons
	bool bPrev_ButtonStates[ButtonCount]; // Previous frame button states
	bool bButtonStates[ButtonCount];      // Current frame button states

	// Buttons pressed on current frame
	bool bGamepad_ButtonsDown[ButtonCount];

public:
	GamepadInputComponent(GameObject* x);
	virtual ~GamepadInputComponent();

	virtual void Start();

	virtual void Update(float deltaTime);

	virtual void OnMessage(Message* m);

	virtual void End();

	XINPUT_STATE GetState(); // Return gamepad state
	int GetIndex();          // Return gamepad index
	bool Connected();        // Return true if gamepad is connected

	void Update();			 // Update gamepad state
	void RefreshState();	 // Update button states for next frame

	bool GetButtonPressed(int a_iButton);	// Return True if passed otherwise False
	bool GetButtonDown(int a_iButton);		// Ditto as above, but only on current frame. Can be useful!
};
#endif // GAMEPAD_H
extern XButtonIDs XButtons;