#pragma once
#include <fstream>
#include <Windows.h>

#include "Window.h"
#include "Vertex.h"
#include "Renderer.h"

#include "Mesh.h"
#include "Texture.h"

enum State{

	Executing,
	Alted,
	Resetting,
	Quit
};

//class Renderer;
//class Window;
class SceneManager;
class GameObject;
class Message;
class Player;
class Planet;
class Camera;

class Game
{
private:

	Window*					_window;
	Renderer*				_renderer;
	SceneManager*			_sceneManager;

	State					_currentState;

	bool					_keyStates[256];

	float					_deltaTime;			// Time since last frame

	LARGE_INTEGER start, end, frequency;

public:
	Game();
	~Game();

	static Game* TTS;

	void Initialize(Window* w);
	void Run(void);
	void Draw();
	void OnKeyboard(int key, bool down);
	void Reset();

	// Message system
	void Broadcast(Message* m);
	void ListenToMessage(Message* m);

	SceneManager* GetSceneManager() { return _sceneManager; }

	State GetPState()			const	{ return _currentState; }
};

