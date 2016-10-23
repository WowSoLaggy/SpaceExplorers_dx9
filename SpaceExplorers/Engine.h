#pragma once

#ifndef INC_ENGINE_H
#define INC_ENGINE_H


#include "ErrCodes.h"
#include "Game.h"
#include "Scene.h"


class Engine
{
public:

	Engine();

	Scene& GetScene() { return m_scene; }
	const Scene& GetScene() const { return m_scene; }

	Game& GetGame() { return m_game; }
	const Game& GetGame() const { return m_game; }

	static Engine* GetInstance() { return s_instance; }

	ErrCode Run(const Doh3d::StartupPars& pStartupPars);
	ErrCode Stop();

private:

	const std::string c_gameName = "SpaceExplorers";
	const std::string c_logDirName = "Logs";
	const std::string c_logFileFullPath = c_logDirName + "/" + c_gameName + ".log";
	const std::string c_fileName = c_gameName + ".exe";

	const std::string c_textureDir = "Data/Textures/";
	const std::string c_fontDir = "Data/Fonts/";


	volatile bool m_isRun;

	static Engine* s_instance;
	Game m_game;
	Scene m_scene;

	Doh3d::Sprite m_sprite;


	ErrCode Init(const Doh3d::StartupPars& pStartupPars);
	ErrCode Mainloop();
	ErrCode Dispose();

	ErrCode OnRenderDeviceReset();
	ErrCode GetRenderPars(Doh3d::RenderPars& pRenderPars);
	ErrCode GetInputPars(Doh3d::InputPars& pInputPars);

	// Input handlers

	void OnMouseMove();
	void OnMouseDown(int pButton);
	void OnMouseUp(int pButton);

	void OnKeyPressed(int pKey);
	void OnKeyDown(int pKey);
	void OnKeyUp(int pKey);

};


#endif // INC_ENGINE_H
