// http://rivermanmedia.com/object-oriented-game-programming-the-scene-system/

#pragma once
#include <stddef.h>
#include "Scene.h"

class Message;

class SceneManager
{
private:
	static SceneManager* instance;
	Scene* currScene;

public:
	SceneManager();
	~SceneManager();

	static SceneManager* GetInstance();

	bool LoadScene(Scene* s);
	void Update(float dt);
	void Draw();

	void ChangeScene(Scene* newScene);

	void OnMessage(Message* m);
	void OnKeyboard(int key, bool down);

	Scene* GetCurrentScene() { return currScene; }
};

