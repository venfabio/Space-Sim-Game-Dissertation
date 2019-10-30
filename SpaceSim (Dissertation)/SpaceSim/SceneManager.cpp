#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::instance = 0;

SceneManager::SceneManager()
{
	instance = this;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	return instance;
}

bool SceneManager::LoadScene(Scene* s)
{
	currScene = s;
	currScene->Load();
	return true;
}

void SceneManager::Update(float dt)
{
	currScene->Update(dt);
}

void SceneManager::Draw()
{
	currScene->Draw();
}

void SceneManager::ChangeScene(Scene* newScene)
{
	currScene->Unload();
	currScene = newScene;
	currScene->Load();
}

void SceneManager::OnMessage(Message* m)
{
	currScene->OnMessage(m);
}

void SceneManager::OnKeyboard(int key, bool down)
{
	currScene->OnKeyboard(key, down);
}