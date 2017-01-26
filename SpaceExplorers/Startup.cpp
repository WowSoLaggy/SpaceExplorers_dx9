#include "stdafx.h"
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Doh3d::StartupPars startupPars(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
  Game().run(startupPars);
	return 0;
}
