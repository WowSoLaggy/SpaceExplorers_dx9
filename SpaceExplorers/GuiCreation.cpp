#include "stdafx.h"
#include "Gui.h"


ErrCode Gui::CreatePanel(Doh3d::GPanel*& pPanel, float pPosX, float pPosY, float pSizeX, float pSizeY, const std::string& pTextureName)
{
	LOG("Gui::CreatePanel()");
	ErrCode3d err3d;

	Doh3d::GPanel* panel = new Doh3d::GPanel(pPosX, pPosY, pSizeX, pSizeY, pTextureName);
	
	if (m_isLoaded)
	{
		err3d = panel->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load panel.");
			return err_cantLoadGui;
		}
	}

	m_guis.push_back(panel);
	pPanel = panel;
	return err_noErr;
}


ErrCode Gui::CreateButton(Doh3d::GButton*& pButton, float pPosX, float pPosY, float pSizeX, float pSizeY,
							const std::string& pTexNameNormal, const std::string& pTexNamePressed, const std::string& pTexNameSelected, const std::string& pTexNameDisabled)
{
	LOG("Gui::CreateButton()");
	ErrCode3d err3d;

	Doh3d::GButton* button = new Doh3d::GButton(pPosX, pPosY, pSizeX, pSizeY, pTexNameNormal, pTexNamePressed, pTexNameSelected, pTexNameDisabled);
	
	if (m_isLoaded)
	{
		err3d = button->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load button.");
			return err_cantLoadGui;
		}
	}

	m_guis.push_back(button);
	pButton = button;
	return err_noErr;
}

ErrCode Gui::CreateText(Doh3d::GText*& pGText, float pPosX, float pPosY, const std::string& pText, const std::string& pFontName)
{
	LOG("Gui::CreateText()");
	ErrCode3d err3d;

	Doh3d::GText* text = new Doh3d::GText(pPosX, pPosY, pText, pFontName);

	if (m_isLoaded)
	{
		err3d = text->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load text.");
			return err_cantLoadGui;
		}
	}
	
	m_guis.push_back(text);
	pGText = text;
	return err_noErr;
}

ErrCode Gui::CreateGGrid(Doh3d::GGrid*& pGGrid, float pPosX, float pPosY, float pSizeX, float pSizeY, int pNumberOfCells,
						   const std::string& pTextureName, const std::string& pFrameTextureName)
{
	LOG("Gui::CreateGGrid()");
	ErrCode3d err3d;

	Doh3d::GGrid* grid = new Doh3d::GGrid(pPosX, pPosY, pSizeX, pSizeY, pNumberOfCells, pTextureName, pFrameTextureName);

	if (m_isLoaded)
	{
		err3d = grid->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load grid.");
			return err_cantLoadGui;
		}
	}

	m_guis.push_back(grid);
	pGGrid = grid;
	return err_noErr;
}
