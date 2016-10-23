#pragma once

#ifndef INC_GAME_H
#define INC_GAME_H


#include "ErrCodes.h"
#include "Map.h"
#include "Scene.h"
#include "Gui.h"
#include "Prototype.h"


class Game
{
public:

	ErrCode Start(Scene& pScene);
	ErrCode End();

	bool IsRun() { return m_isRun; }

	bool HasMap() const { return m_map.get() != nullptr; }
	std::shared_ptr<Map> GetMap() const { return m_map; }
	Gui GetGui() { return m_gui; }


	ErrCode OnRenderDeviceReset();


	// Input handlers

	ErrCode OnMouseMove(bool& pHandled);
	ErrCode OnMouseDown(bool& pHandled, int pButton);
	ErrCode OnMouseUp(bool& pHandled, int pButton);
	ErrCode OnKeyPressed(bool& pHandled, int pKey);
	ErrCode OnKeyDown(bool& pHandled, int pKey);
	ErrCode OnKeyUp(bool& pHandled, int pKey);

	// Actions

	ErrCode InfoUnderCursor();

	ErrCode MoveCameraLeft();
	ErrCode MoveCameraRight();
	ErrCode MoveCameraUp();
	ErrCode MoveCameraDown();

	ErrCode SelectBeltItem(int pItemIndex);

private:

	volatile bool m_isRun;

	Scene* m_scene;
	std::shared_ptr<Map> m_map;
	Gui m_gui;

	static const std::string c_pathToObjectsFile;

};


#endif // INC_GAME_H
