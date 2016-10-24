#pragma once

#ifndef INC_GUI_H
#define INC_GUI_H


#include "ErrCodes.h"
#include "Scene.h"
#include "Prototype.h"


class Game;


enum class GuiMode
{
	MainMenu,
	InGame,
	EscapeMenu,

	End
};


class Gui
{
public:

	ErrCode Init(Game* pGame);
	ErrCode Dispose();

	ErrCode Load();
	ErrCode Unload();

	ErrCode Draw(Doh3d::Sprite& pSprite);

	GuiMode Mode() const { return m_mode; }
	ErrCode SetNewGuiIfNeeded();

	void SetScene(Scene& pScene) { m_scene = &pScene; }


	Doh3d::GPanel* MainMenu_Background;
	Doh3d::GButton* MainMenu_CreateNewMapBtn;
	Doh3d::GButton* MainMenu_LoadMapBtn;
	Doh3d::GButton* MainMenu_ExitBtn;
	Doh3d::GText* MainMenu_VersionText;

	Doh3d::GPanel* InfoPanel;
	Doh3d::GText* InfoText;
	Doh3d::GGrid* InventoryGrid;

	Doh3d::GPanel* EscapeMenu_Fade;
	Doh3d::GButton* EscapeMenu_ReturnToGame;
	Doh3d::GButton* EscapeMenu_ExitToMain;


	ErrCode DeleteGuis();
	ErrCode CreateOrUpdateGui(GuiMode pGuiMode);


	/// nullptr to cancel buiding mode
	ErrCode SwitchBuildMode(const Prototype* pWhatToBuild);
	bool IsBuildMode() const { return m_whatToBuild != nullptr; }

	// Input handlers

	ErrCode OnMouseMove(bool& pHandled);
	ErrCode OnMouseDown(bool& pHandled, int pButton);
	ErrCode OnMouseUp(bool& pHandled, int pButton);
	ErrCode OnKeyPressed(bool& pHandled, int pKey);
	ErrCode OnKeyDown(bool& pHandled, int pKey);
	ErrCode OnKeyUp(bool& pHandled, int pKey);

	// Gui creation

	ErrCode CreatePanel(Doh3d::GPanel*& pPanel, float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName);
	ErrCode CreateButton(Doh3d::GButton*& pButton, float pPosX, float pPosY, float pSizeX, float pSizeY,
						 const std::string& pTexNameNormal, const std::string& pTexNamePressed, const std::string& pTexNameSelected, const std::string& pTexNameDisabled);
	ErrCode CreateText(Doh3d::GText*& pGText, float pPosX, float pPosY, const std::string& pText, const std::string& pFontName = "Gadugi");
	ErrCode CreateGGrid(Doh3d::GGrid*& pGGrid, float pPosX, float pPosY, float pSizeX, float pSizeY, int pNumberOfCells,
						const std::string& pTextureName, const std::string& pFrameTextureName);

private:

	bool m_isLoaded;
	GuiMode m_mode;

	bool m_newGuiReady;

	Scene* m_scene;
	Game* m_game;

	std::vector<Doh3d::GBase*> m_guis;
	std::vector<Doh3d::GBase*> m_newGuis;
	D3DXMATRIX m_transformMatrix;

	const Prototype* m_whatToBuild;


	ErrCode CreateMainMenu();
	ErrCode CreateGameGui();
	ErrCode CreateEscapeMenu();

};


#endif // INC_GUI_H
