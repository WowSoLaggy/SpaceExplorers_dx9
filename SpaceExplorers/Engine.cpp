#include "stdafx.h"
#include "Engine.h"

#include "Cursor.h"


Engine* Engine::s_instance;


Engine::Engine()
{
	s_instance = this;
}


ErrCode Engine::Run(const Doh3d::StartupPars& pStartupPars)
{
	CreateDirectory(c_logDirName.c_str(), nullptr);
	LOGINIT(c_logFileFullPath, c_gameName, c_fileName);

	LOG("Engine::Run()");
	ErrCode err;

	err = Init(pStartupPars);
	if (err != err_noErr)
	{
		echo("ERROR: Can't init Engine.");
		return err;
	}

	err = Mainloop();
	if (err != err_noErr)
	{
		echo("ERROR: Error while mainlooping.");
		Dispose();
		return err;
	}

	err = Dispose();
	if (err != err_noErr)
	{
		echo("ERROR: Can't dispose Engine.");
		return err;
	}

	return err_noErr;
}

ErrCode Engine::Stop()
{
	m_isRun = false;
	return err_noErr;
}


ErrCode Engine::Init(const Doh3d::StartupPars& pStartupPars)
{
	LOG("Engine::Init()");
	ErrCode err;
	ErrCode3d err3d;

	Doh3d::WinClass::Register(pStartupPars, c_gameName);

	Doh3d::ResourceMan::SetTextureDir(c_textureDir);
	Doh3d::ResourceMan::SetFontDir(c_fontDir);

	err3d = Doh3d::ResourceMan::Init();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't init resources.");
		return err_cantInitResources;
	}

	err = m_scene.Init();
	if (err != err_noErr)
	{
		echo("ERROR: Can't init scene.");
		return err;
	}

	err = m_game.Init();
	if (err != err_noErr)
	{
		echo("ERROR: Can't init game.");
		return err;
	}

	err = Cursor::SetNormal();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set normal cursor.");
		return err;
	}

	return err_noErr;
}

ErrCode Engine::Dispose()
{
	LOG("Engine::Dispose()");
	ErrCode err;
	ErrCode3d err3d;

	err = m_game.Dispose();
	if (err != err_noErr)
	{
		echo("ERROR: Can't dispose game.");
		return err;
	}

	err = m_scene.Dispose();
	if (err != err_noErr)
	{
		echo("ERROR: Can't dispose scene.");
		return err;
	}

	err3d = Doh3d::ResourceMan::Dispose();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't dispose resources.");
		return err_cantDisposeResources;
	}

	err3d = Doh3d::RenderMan::Dispose();
	if (err3d != err3d_noErr)
		echo("ERROR: Can't dispose RenderMan.");

	Doh3d::WinClass::Unregister();
	return err_noErr;
}


ErrCode Engine::OnRenderDeviceReset()
{
	LOG("Engine::OnRenderDeviceReset()");
	ErrCode err;
	ErrCode3d err3d;

	// Unload map

	if (m_game.HasMap())
	{
		err = m_game.GetMap()->Unload();
		if (err != err_noErr)
		{
			echo("ERROR: Can't unload map.");
			return err_cantUnloadMap;
		}
	}

	// Unload scene

	err = m_scene.Unload();
	if (err != err_noErr)
	{
		echo("ERROR: Can't unload scene.");
		return err;
	}

	// Unload resources

	err3d = Doh3d::ResourceMan::UnloadResources();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't unload resources.");
		return err_cantUnloadResources;
	}

	// RenderMan

	Doh3d::RenderPars renderPars;
	err = GetRenderPars(renderPars);
	if (err != err_noErr)
	{
		echo("ERROR: Can't get render pars.");
		return err;
	}

	err3d = Doh3d::RenderMan::Recreate(renderPars);
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't recreate render device.");
		return err_cantRecreateRenderDevice;
	}

	// InputMan

	Doh3d::InputPars inputPars;
	err = GetInputPars(inputPars);
	if (err != err_noErr)
	{
		echo("ERROR: Can't get input pars.");
		return err;
	}

	err3d = Doh3d::InputMan::Recreate(inputPars);
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't recreate InputMan.");
		return err_cantRecreateInputMan;
	}

	// Load resources

	err3d = Doh3d::ResourceMan::LoadResources();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't load resources.");
		return err_cantLoadResources;
	}

	// Sprite

	err3d = m_sprite.Reload();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't reload sprite.");
		return err_cantReloadSprite;
	}

	// Load scene

	err = m_scene.Load();
	if (err != err_noErr)
	{
		echo("ERROR: Can't load scene.");
		return err;
	}

	// Reset game

	err = m_game.OnRenderDeviceReset();
	if (err != err_noErr)
	{
		echo("ERROR: Can't update game.");
		return err;
	}


	return err_noErr;
}

ErrCode Engine::GetRenderPars(Doh3d::RenderPars& pRenderPars)
{
	pRenderPars.ResolutionWidth = 1280;
	pRenderPars.ResolutionHeight = 1024;
	pRenderPars.Windowed = true;
	pRenderPars.FullScreenRefreshRate = 60;
	pRenderPars.WndCaption = false;

	return err_noErr;
}

ErrCode Engine::GetInputPars(Doh3d::InputPars& pInputPars)
{
	pInputPars.MouseSensX = 2;
	pInputPars.MouseSensY = 2;

	pInputPars.OnMouseMove = std::bind(&Engine::OnMouseMove, this);
	pInputPars.OnMouseDown = std::bind(&Engine::OnMouseDown, this, std::placeholders::_1);
	pInputPars.OnMouseUp = std::bind(&Engine::OnMouseUp, this, std::placeholders::_1);

	pInputPars.OnKeyPressed = std::bind(&Engine::OnKeyPressed, this, std::placeholders::_1);
	pInputPars.OnKeyDown = std::bind(&Engine::OnKeyDown, this, std::placeholders::_1);
	pInputPars.OnKeyUp = std::bind(&Engine::OnKeyUp, this, std::placeholders::_1);

	return err_noErr;
}
