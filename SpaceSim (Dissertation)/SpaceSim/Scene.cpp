#include "Scene.h"
#include "GameObject.h"
#include "KeyPressMessage.h"

// No cameras involved, they should be handled individually in the proper scene

Scene::Scene(Renderer* renderer)
{
	_r = renderer;
}


Scene::~Scene()
{
}

void Scene::Load()
{
	// Abstract.
}

void Scene::Unload()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		delete _gameObjects[i];
	}
	_gameObjects.clear();
}

void Scene::Update(float dt)
{
	// Abstract.
}

void Scene::Draw()
{
	// Abstract.
}

void Scene::OnMessage(Message* m)
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		if (_gameObjects[i]->IsAlive())
		{
			_gameObjects[i]->OnMessage(m);
		}
	}
}

void Scene::OnKeyboard(int key, bool down)
{
	_keyStates[key] = down;

	KeyPressMessage m(key, down);
	OnMessage(&m);

}