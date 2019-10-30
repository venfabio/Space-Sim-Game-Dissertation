#pragma once
#include "Scene.h"

class Camera;

class StartScene :
	public Scene
{
private:

	GameObject*				_title;

	Mesh					_titleMesh;

	Texture					_titleTexture;

	// Camera
	Camera*					_cameraOne;		// Default camera

public:
	StartScene(Renderer* renderer);
	~StartScene();

	void Load();
	void Unload();
	void Update(float dt);
	void Draw();
	void OnMessage(Message* m);
	void OnKeyboard(int key, bool down);
};

