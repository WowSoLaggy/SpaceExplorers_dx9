#include "stdafx.h"
#include "Game.h"

#include "RealThing.h"
#include "MapGenerator.h"


const std::string Game::c_pathToObjectsFile = "Data\\main.objs";


ErrCode Game::Start(Scene& pScene)
{
	LOG("Game::Start()");
	ErrCode err;

	m_isRun = true;
	m_scene = &pScene;
	m_gui.SetScene(pScene);

	err = Prototype::Init(c_pathToObjectsFile);
	if (err != err_noErr)
	{
		echo("ERROR: Can't parse object file.");
		return err;
	}

	m_map.reset(MapGenerator::CreateStartLocation());

	err = m_gui.CreateGameGui();
	if (err != err_noErr)
	{
		echo("ERROR: Can't create game gui.");
		return err;
	}

	return err_noErr;
}

ErrCode Game::End()
{
	m_isRun = false;
	return err_noErr;
}


ErrCode Game::OnRenderDeviceReset()
{
	LOG("Game::OnRenderDeviceReset()");
	ErrCode err;

	// Load prototypes

	err = Prototype::Load();
	if (err != err_noErr)
	{
		echo("ERROR: Can't load resources for prototypes.");
		return err;
	}

	// Load map

	if (!!m_map)
	{
		err = m_map->Load();
		if (err != err_noErr)
		{
			echo("ERROR: Can't load map.");
			return err_cantLoadMap;
		}
	}

	// Rescale Gui

	err = m_gui.Load();
	if (err != err_noErr)
	{
		echo("ERROR: Can't rescale Gui.");
		return err;
	}

	return err_noErr;
}
