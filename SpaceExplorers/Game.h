#pragma once

#ifndef INC_GAME_H
#define INC_GAME_H


#include "ErrCodes.h"
#include "Map.h"
#include "Scene.h"
#include "Gui.h"
#include "Prototype.h"


enum class GameMode
{
	MainMenu,
	InGame,
	EscapeMenu,
};


class Game
{
public:

	ErrCode Init();
	ErrCode Dispose();

	ErrCode Start(Scene& pScene);
	ErrCode End();

	bool IsRun() { return m_isRun; }
	GameMode Mode() { return m_mode; }

	bool HasMap() const { return m_map.get() != nullptr; }
	std::shared_ptr<Map> GetMap() const { return m_map; }
	Gui& GetGui() { return m_gui; }


	ErrCode OnRenderDeviceReset();

	ErrCode ShowMainMenu();
	ErrCode ReturnToMainMenu();
	ErrCode StartNewMap();
	ErrCode ReturnToGame();
	ErrCode CallEscapeMenu();


	// Input handlers

	ErrCode OnMouseMove(bool& pHandled);
	ErrCode OnMouseDown(bool& pHandled, int pButton);
	ErrCode OnMouseUp(bool& pHandled, int pButton);
	ErrCode OnKeyPressed(bool& pHandled, int pKey);
	ErrCode OnKeyDown(bool& pHandled, int pKey);
	ErrCode OnKeyUp(bool& pHandled, int pKey);

	// Actions

	ErrCode EscapeHit();
	ErrCode InfoUnderCursor();

	ErrCode MoveCameraLeft();
	ErrCode MoveCameraRight();
	ErrCode MoveCameraUp();
	ErrCode MoveCameraDown();

	ErrCode SelectBeltItem(int pItemIndex);
	ErrCode OnBeltItemChanged();

	ErrCode TryBuild();

	ErrCode SaveMap();
	ErrCode LoadMap();

	ErrCode BeginRemoveMode();
	ErrCode EndRemoveMode();
	ErrCode TryRemove();

private:

	volatile bool m_isRun;
	GameMode m_mode;

	Scene* m_scene;
	std::shared_ptr<Map> m_map;
	Gui m_gui;

	static const std::string c_pathToObjectsFile;

	ErrCode OnNewGame();

};


#endif // INC_GAME_H
