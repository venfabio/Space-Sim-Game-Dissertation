#include "StartScene.h"
#include "Renderer.h"
#include "Camera.h"
#include "Message.h"
#include "Game.h"

StartScene::StartScene(Renderer* renderer)
	: Scene(renderer)
{
}


StartScene::~StartScene()
{
}

void StartScene::Load()
{
	_cameraOne = _r->GetCamera();
	_cameraOne->Reset();

	_titleMesh.LoadFromFile("PanelMesh.txt");
	_titleMesh.CreateVBO(_r);
	_titleTexture.Initialize(_r->GetDevice(), L"MainScreen.jpg");
	_title = new GameObject();
	_title->SetMesh(&_titleMesh);
	_title->SetTexture(&_titleTexture);
	_title->SetAlive(true);

	_gameObjects.push_back(_title);
}

void StartScene::Unload()
{
	Scene::Unload();
}

void StartScene::Update(float deltaTime)
{

}

void StartScene::Draw()
{
	_r->ClearScreen();
	_r->RenderFrame();

	_r->DrawGUI(_title);

	_r->SwapBuffer();
}

void StartScene::OnMessage(Message* m)
{
	Scene::OnMessage(m);
}

void StartScene::OnKeyboard(int key, bool down)
{
	Scene::OnKeyboard(key, down);

	if (key == 13 && down == true)
	{
		Message* m = new Message("changescene");
		Game::TTS->ListenToMessage(m);
	}
}