#pragma once
#include <vector>
#include "Mesh.h"
#include "Texture.h"

class Renderer;
class GameObject;
class Message;

enum SceneState{

	Loading,
	Running,
	Paused,
	Transitioning
};

class Scene
{
protected:
	Renderer*						_r;

	std::vector<GameObject*>		_gameObjects;

	SceneState						_sceneState;

	bool							_keyStates[256];

public:
	Scene(Renderer* renderer);
	~Scene();

	virtual void Load();
	virtual void Unload();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void OnMessage(Message* m);
	virtual void OnKeyboard(int key, bool down);

	SceneState GetSceneState() { return _sceneState; }

	std::vector<GameObject*> GetGameObjects()	{ return _gameObjects; }
};

