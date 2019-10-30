#define _USE_MATH_DEFINES // Allows access to PI from math.h
#include <math.h>
#include "Window.h"
#include "Renderer.h"
#include "Game.h"

Window*	Window::TheWindow = 0;

Window::Window(Game *game, HINSTANCE hInstance, int nCmdShow)
	: _renderer(0),
	_game(game)
{
	TheWindow = this;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Window::WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	// x86
	wc.lpszClassName = L"WindowClass";
	// x64
	//wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, 800, 600 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	// x86
	
	_hWnd = CreateWindowEx(NULL,
		L"WindowClass",
		L"Through the Stars",
		WS_OVERLAPPEDWINDOW,
		0,	//100
		0,	//100
		SCREEN_WIDTH, SCREEN_HEIGHT,    // set window to new resolution
		NULL,
		NULL,
		hInstance,
		NULL);
	
	// x64
	/*
	_hWnd = CreateWindowEx(NULL,
		"WindowClass",
		"Through the Stars",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		SCREEN_WIDTH, SCREEN_HEIGHT,    // set window to new resolution
		NULL,
		NULL,
		hInstance,
		NULL);
	*/
	ShowWindow(_hWnd, nCmdShow);
}

// this is the main message handler for the program
LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		//PostQuitMessage(0); 
		exit(0);
		return 0;
	}
		break;
	
	case WM_KEYDOWN:
	{
		TheWindow->_game->OnKeyboard(wParam, true);
	}
		break;
	case WM_KEYUP:
	{
		TheWindow->_game->OnKeyboard(wParam, false);
	}
		break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::Start()

{
	_renderer = new Renderer(_hWnd);

	// set up and initialize Direct3D
	_renderer->InitD3D();
	_renderer->InitStates();

	_game->Initialize(this);

	// enter the main loop:

	MSG msg;

	while (_game->GetPState() != Quit)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}

		_game->Run();
	}

	// clean up DirectX and COM
	_renderer->CleanD3D();
}

