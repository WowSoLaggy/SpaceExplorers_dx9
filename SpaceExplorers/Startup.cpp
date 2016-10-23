#include "stdafx.h"
#include "Engine.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine engine;
	return engine.Run({ hInstance, hPrevInstance, lpCmdLine, nCmdShow });
}
