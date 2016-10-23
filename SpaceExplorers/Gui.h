#pragma once

#ifndef INC_GUI_H
#define INC_GUI_H


#include "ErrCodes.h"
#include "Scene.h"
#include "Prototype.h"


class Gui
{
public:

	ErrCode Init();
	ErrCode Dispose();

	ErrCode Load();
	ErrCode Unload();

	ErrCode Draw(Doh3d::Sprite& pSprite);

	void SetScene(Scene& pScene) { m_scene = &pScene; }

	Doh3d::GPanel* InfoPanel;
	Doh3d::GText* InfoText;
	Doh3d::GGrid* InventoryGrid;

	ErrCode CreateGameGui();

	/// nullptr to cancel buiding mode
	ErrCode SwitchBuildMode(const Prototype* pWhatToBuild);


	// Gui creation

	ErrCode CreatePanel(Doh3d::GPanel*& pPanel, float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName);
	ErrCode CreateButton(Doh3d::GButton*& pButton, float pPosX, float pPosY, float pSizeX, float pSizeY,
						 const std::string& pTexNameNormal, const std::string& pTexNamePressed, const std::string& pTexNameSelected, const std::string& pTexNameDisabled);
	ErrCode CreateText(Doh3d::GText*& pGText, float pPosX, float pPosY, const std::string& pText, const std::string& pFontName = "Gadugi");
	ErrCode CreateGGrid(Doh3d::GGrid*& pGGrid, float pPosX, float pPosY, float pSizeX, float pSizeY, int pNumberOfCells,
						const std::string& pTextureName, const std::string& pFrameTextureName);

private:

	bool m_isLoaded;

	Scene* m_scene;
	std::vector<Doh3d::GBase*> m_guis;
	D3DXMATRIX m_transformMatrix;

	const Prototype* m_whatToBuild;

};


#endif // INC_GUI_H
