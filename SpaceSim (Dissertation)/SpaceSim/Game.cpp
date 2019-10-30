#include <iostream>
#include <fstream>

#include "Game.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "GameplayScene.h"
#include "KeyPressMessage.h"

Game* Game::TTS = NULL;

Game::Game()
{
	TTS = this;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
}

Game::~Game()
{
}

void Game::Initialize(Window* w)
{
	_window = w;
	_renderer = w->GetRenderer();

	_sceneManager = new SceneManager();

	// Read stuff from config file
	//ReadConfig();

	if (_sceneManager->LoadScene(new StartScene(_renderer)))
		_currentState = Executing;
}

// this is the function used to render a single frame
void Game::Run(void)
{
	// Get delta time
	QueryPerformanceCounter(&end);
	_deltaTime = (end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
	start = end;

	if (_currentState == Executing)
	{
		_sceneManager->Update(_deltaTime);
	}

	// Draw everything
	Draw();
}


void Game::Draw()
{
	_sceneManager->Draw();
}

void Game::OnKeyboard(int key, bool down)
{
	_keyStates[key] = down;
	/*
	// Misc
	if (_keyStates[27])
	{
		exit(0);
	}

	if (_keyStates[80])	// P
	{
		if (_currentState == Running)
			_currentState = Paused;
		else if (_currentState == Paused)
			_currentState = Running;
	}

	if (_keyStates[82])  // R
	{
		_currentState = Resetting;
		Reset();
		_currentState = Running;
	}*/

	_sceneManager->OnKeyboard(key, down);
	//KeyPressMessage m(key, down);
	//Broadcast(&m);
}

void Game::Reset()
{
}

void Game::ListenToMessage(Message* m)
{
	if (m->GetMessageType() == "changescene")
	{
		_sceneManager->ChangeScene(new GameplayScene(_renderer));
	}
}

void Game::Broadcast(Message* m)
{
	ListenToMessage(m);
}
