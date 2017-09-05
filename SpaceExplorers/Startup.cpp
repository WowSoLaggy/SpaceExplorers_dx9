#include "stdafx.h"
#include "Engine.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Doh3d::StartupPars startupPars(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
  Engine().run(startupPars);
	return 0;
}
