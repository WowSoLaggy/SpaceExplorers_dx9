#include "stdafx.h"
#include "Game.h"

#include "RealThing.h"
#include "MapGenerator.h"


const std::string Game::c_pathToObjectsFile = "Data\\main.objs";


ErrCode Game::Init()
{
	LOG("Game::Init()");
	ErrCode err;

	m_mode = GameMode::MainMenu;

	err = m_gui.Init(this);
	if (err != err_noErr)
	{
		echo("ERROR: Can't init Gui.");
		return err;
	}

	return err_noErr;
}

ErrCode Game::Dispose()
{
	LOG("Game::Dispose()");
	ErrCode err;

	err = m_gui.Dispose();
	if (err != err_noErr)
	{
		echo("ERROR: Can't dispose Gui.");
		return err;
	}

	return err_noErr;
}


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

	err = ShowMainMenu();
	if (err != err_noErr)
	{
		echo("ERROR: Can't show main menu.");
		return err;
	}

	err = m_gui.SetNewGuiIfNeeded();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set new Guis.");
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

	// Reload Gui

	err = m_gui.Load();
	if (err != err_noErr)
	{
		echo("ERROR: Can't reload Gui.");
		return err;
	}

	err = m_gui.SetNewGuiIfNeeded();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set new Guis.");
		return err;
	}

	return err_noErr;
}


ErrCode Game::ShowMainMenu()
{
	LOG("Game::ShowMainMenu()");
	ErrCode err;

	m_mode = GameMode::MainMenu;

	err = m_gui.CreateOrUpdateGui(GuiMode::MainMenu);
	if (err != err_noErr)
	{
		echo("ERROR: Can't create main menu.");
		return err;
	}

	return err_noErr;
}

ErrCode Game::ReturnToMainMenu()
{
	LOG("Game::ReturnToMainMenu()");
	ErrCode err;

	err = ShowMainMenu();
	if (err != err_noErr)
	{
		echo("ERROR: Can't create main menu.");
		return err;
	}

	m_scene->SetBackground("");
	m_map.reset();

	return err_noErr;
}

ErrCode Game::StartNewMap()
{
	LOG("Game::StartNewMap()");
	ErrCode err;

	m_map.reset(MapGenerator::CreateStartLocation());

	err = OnNewGame();
	if (err != err_noErr)
	{
		echo("ERROR: Error while OnNewGame() call.");
		return err;
	}

	return err_noErr;
}

ErrCode Game::LoadMap()
{
	LOG("Game::LoadMap()");
	ErrCode err;

	Map* pMap = nullptr;
	err = Map::LoadFromFile(pMap, "main.map");
	if (err != err_noErr)
	{
		echo("ERROR: Can't load map \"main.map\".");
		return err;
	}
	if (!pMap)
	{
		echo("ERROR: LoadMapFromFile() returned nullptr.");
		return err_cantLoadMapFromFile;
	}

	m_map.reset(pMap);

	err = OnNewGame();
	if (err != err_noErr)
	{
		echo("ERROR: Error while OnNewGame() call.");
		return err;
	}

	return err_noErr;
}

ErrCode Game::OnNewGame()
{
	LOG("Game::OnNewGame()");
	ErrCode err;

	m_mode = GameMode::InGame;
	m_scene->SetBackground("Space_1920_1024_1.png");
	err = m_gui.CreateOrUpdateGui(GuiMode::InGame);
	if (err != err_noErr)
	{
		echo("ERROR: Can't create game gui.");
		return err;
	}

	if (!m_scene)
	{
		echo("ERROR: No scene to load.");
		return err_cantLoadScene;
	}

	err = m_scene->Load();
	if (err != err_noErr)
	{
		echo("ERROR: Can't load scene.");
		return err;
	}

	return err_noErr;
}

ErrCode Game::ReturnToGame()
{
	LOG("Game::ReturnToGame()");
	ErrCode err;

	m_mode = GameMode::InGame;
	err = m_gui.CreateOrUpdateGui(GuiMode::InGame);
	if (err != err_noErr)
	{
		echo("ERROR: Can't update Gui for mode: \"InGame\".");
		return err;
	}

	return err_noErr;
}

ErrCode Game::CallEscapeMenu()
{
	LOG("Game::CallEscapeMenu()");
	ErrCode err;

	m_mode = GameMode::EscapeMenu;
	err = m_gui.CreateOrUpdateGui(GuiMode::EscapeMenu);
	if (err != err_noErr)
	{
		echo("ERROR: Can't update Gui for mode: \"EscapeMenu\".");
		return err;
	}

	return err_noErr;
}
