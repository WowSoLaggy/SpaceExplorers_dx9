#include "stdafx.h"
#include "Gui.h"


ErrCode Gui::CreatePanel(Doh3d::GPanel*& pPanel, int pPosX, int pPosY, int pSizeX, int pSizeY, const std::string& pTextureName)
{
	LOG("Gui::CreatePanel()");
	ErrCode3d err3d;

	Doh3d::GPanel* panel = new Doh3d::GPanel((float)pPosX, (float)pPosY, (float)pSizeX, (float)pSizeY, pTextureName);
	
	if (m_isLoaded)
	{
		err3d = panel->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load panel.");
			return err_cantLoadGui;
		}
	}

	m_newGuis.push_back(panel);
	pPanel = panel;
	return err_noErr;
}


ErrCode Gui::CreateButton(Doh3d::GButton*& pButton, int pPosX, int pPosY, int pSizeX, int pSizeY,
							const std::string& pTexNameNormal, const std::string& pTexNamePressed, const std::string& pTexNameSelected, const std::string& pTexNameDisabled)
{
	LOG("Gui::CreateButton()");
	ErrCode3d err3d;

	Doh3d::GButton* button = new Doh3d::GButton((float)pPosX, (float)pPosY, (float)pSizeX, (float)pSizeY, pTexNameNormal, pTexNamePressed, pTexNameSelected, pTexNameDisabled);
	
	if (m_isLoaded)
	{
		err3d = button->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load button.");
			return err_cantLoadGui;
		}
	}

	m_newGuis.push_back(button);
	pButton = button;
	return err_noErr;
}

ErrCode Gui::CreateText(Doh3d::GText*& pGText, int pPosX, int pPosY, const std::string& pText, const std::string& pFontName)
{
	LOG("Gui::CreateText()");
	ErrCode3d err3d;

	Doh3d::GText* text = new Doh3d::GText((float)pPosX, (float)pPosY, pText, pFontName);

	if (m_isLoaded)
	{
		err3d = text->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load text.");
			return err_cantLoadGui;
		}
	}
	
	m_newGuis.push_back(text);
	pGText = text;
	return err_noErr;
}

ErrCode Gui::CreateGGrid(Doh3d::GGrid*& pGGrid, int pPosX, int pPosY, int pSizeX, int pSizeY, int pNumberOfCells,
						   const std::string& pTextureName, const std::string& pFrameTextureName)
{
	LOG("Gui::CreateGGrid()");
	ErrCode3d err3d;

	Doh3d::GGrid* grid = new Doh3d::GGrid((float)pPosX, (float)pPosY, (float)pSizeX, (float)pSizeY, pNumberOfCells, pTextureName, pFrameTextureName);

	if (m_isLoaded)
	{
		err3d = grid->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load grid.");
			return err_cantLoadGui;
		}
	}

	m_newGuis.push_back(grid);
	pGGrid = grid;
	return err_noErr;
}
