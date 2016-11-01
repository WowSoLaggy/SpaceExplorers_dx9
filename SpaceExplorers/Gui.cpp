#include "stdafx.h"
#include "Gui.h"

#include "Game.h"
#include "Prototype.h"


ErrCode Gui::Init(Game* pGame)
{
	m_isLoaded = false;
	m_whatToBuild = nullptr;
	m_game = pGame;
	m_newGuiReady = false;

	return err_noErr;
}

ErrCode Gui::Dispose()
{
	LOG("Gui::Dispose()");
	ErrCode err;

	m_isLoaded = false;

	err = DeleteGuis();
	if (err != err_noErr)
	{
		echo("ERROR: Can't delete Guis.");
		return err;
	}

	return err_noErr;
}


ErrCode Gui::Load()
{
	LOG("Gui::Load()");
	ErrCode3d err3d;

	// Update Gui

	CreateOrUpdateGui(m_mode);

	// Load Guis

	for (auto& gui : m_newGuis)
	{
		err3d = gui->Load();
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't load GUI.");
			return err_cantLoadGui;
		}
	}

	// Get zoom for Gui

	D3DXVECTOR2 scaleCenter(0, 0);
	D3DXVECTOR2 scale = D3DXVECTOR2(1, 1);
	D3DXMatrixTransformation2D(&m_transformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);

	m_isLoaded = true;

	return err_noErr;
}

ErrCode Gui::Unload()
{
	m_isLoaded = false;
	return err_noErr;
}

ErrCode Gui::Draw(Doh3d::Sprite& pSprite)
{
	LOG("Gui::Draw()");
	ErrCode3d err3d;
	HRESULT hRes;

	if (m_game->Mode() == GameMode::InGame)
	{
		// Draw building mode blueprint

		if (m_whatToBuild != nullptr)
		{
			D3DXVECTOR2 position2 = Doh3d::InputMan::GetCursorPosition();

			Tile* tile = m_scene->HitTestTile();
			auto color = m_whatToBuild->CheckPrerequisites(tile) ? D3DCOLOR_ARGB(255, 155, 255, 155) : D3DCOLOR_ARGB(255, 255, 155, 155);

			position2 = m_scene->GetScreenCoords(m_scene->GetTileCoords(position2));
			D3DXVECTOR3 position3(position2.x, position2.y, 0);
			hRes = pSprite.Get()->Draw(Doh3d::ResourceMan::GetTexture(m_whatToBuild->Ti()).Get(), 0, 0, &position3, color);
			if (hRes != S_OK)
			{
				echo("ERROR: Can't draw thing (type name: \"", m_whatToBuild->TypeName(), "\").");
				return err_cantDrawThing;
			}
		}
	}

	// Draw Gui

	pSprite.Get()->SetTransform(&m_transformMatrix);
	for (auto& gui : m_guis)
	{
		err3d = gui->Draw(pSprite);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't draw Gui.");
			return err_cantDrawGui;
		}
	}

	return err_noErr;
}


ErrCode Gui::SwitchBuildMode(const Prototype* pWhatToBuild)
{
	m_whatToBuild = pWhatToBuild;
	return err_noErr;
}


ErrCode Gui::DeleteGuis()
{
	for (auto& gui : m_guis)
		delete gui;

	m_guis.clear();

	return err_noErr;
}

ErrCode Gui::CreateOrUpdateGui(GuiMode pGuiMode)
{
	LOG("Gui::CreateOrUpdateGui()");
	ErrCode err;

	switch (pGuiMode)
	{
	case GuiMode::MainMenu:
		err = CreateMainMenu();
		break;

	case GuiMode::InGame:
		err = CreateGameGui();
		break;

	case GuiMode::EscapeMenu:
		err = CreateEscapeMenu();
		break;

	default:
		err = err_unknownGuiMode;
		break;
	}

	m_newGuiReady = true;

	if (err != err_noErr)
	{
		echo("ERROR: Can't create GUI for mode: (", (int)pGuiMode, ").");
		return err;
	}

	return err_noErr;
}


ErrCode Gui::CreateMainMenu()
{
	LOG("Gui::CreateMainMenu()");

	int screenWidth = Doh3d::RenderMan::GetRenderPars().ResolutionWidth;
	int screenHeight = Doh3d::RenderMan::GetRenderPars().ResolutionHeight;

	CreatePanel(MainMenu_Background, 0, 0,
		(float)(screenWidth), (float)(screenHeight),
				"MainMenu_1920_1080_1.png");

	CreateButton(MainMenu_CreateNewMapBtn, (FLOAT)(screenWidth - 256 - 64), (FLOAT)(screenHeight - 224), 256, 32,
				 "Button_256_32_1.png", "ButtonPressed_256_32_1.png",
				 "ButtonLight_256_32_1.png", "ButtonBw_256_32_1.png");
	MainMenu_CreateNewMapBtn->SetFont("Gadugi");
	MainMenu_CreateNewMapBtn->SetText("Create new map");
	MainMenu_CreateNewMapBtn->SetOnClickEvent(std::bind(&Game::StartNewMap, m_game));

	CreateButton(MainMenu_LoadMapBtn, (FLOAT)(screenWidth - 256 - 64), (FLOAT)(screenHeight - 176), 256, 32,
				 "Button_256_32_1.png", "ButtonPressed_256_32_1.png",
				 "ButtonLight_256_32_1.png", "ButtonBw_256_32_1.png");
	MainMenu_LoadMapBtn->SetFont("Gadugi");
	MainMenu_LoadMapBtn->SetText("Load map");
	MainMenu_LoadMapBtn->SetOnClickEvent(std::bind(&Game::LoadMap, m_game));

	CreateButton(MainMenu_ExitBtn, (FLOAT)(screenWidth - 256 - 64), (FLOAT)(screenHeight - 96), 256, 32,
				 "Button_256_32_1.png", "ButtonPressed_256_32_1.png",
				 "ButtonLight_256_32_1.png", "ButtonBw_256_32_1.png");
	MainMenu_ExitBtn->SetFont("Gadugi");
	MainMenu_ExitBtn->SetText("Exit");
	MainMenu_ExitBtn->SetOnClickEvent(std::bind(&Game::End, m_game));

	CreateText(MainMenu_VersionText, 12, (FLOAT)(screenHeight - 30), "");
	std::string version;
	if (!Log::GetProductVersion("SpaceExplorers.exe", version))
	{
		echo("ERROR: Can't get file version.");
		return err_cantGetFileVersion;
	}
	MainMenu_VersionText->SetText("Space Explorers v." + version);

	return err_noErr;
}

ErrCode Gui::CreateGameGui()
{
	CreatePanel(InfoPanel, 20, 20, 256, 96, "Panel_256_96_1.png");

	CreateText(InfoText, 38, 34, "");

	int gridSizeX = 735;
	int gridSizeY = 96;
	int screenWidth = Doh3d::RenderMan::GetRenderPars().ResolutionWidth;
	int screenHeight = Doh3d::RenderMan::GetRenderPars().ResolutionHeight;

	CreateGGrid(InventoryGrid,
		(float)((screenWidth - gridSizeX) / 2), (float)((screenHeight - gridSizeY)),
				(float)gridSizeX, (float)gridSizeY, 10, "Inventory_735_96_1.png", "Frame_68_68_1.png");

	InventoryGrid->SetFrameOffset(D3DXVECTOR3(14, 14, 0));
	InventoryGrid->SetGridOffset(D3DXVECTOR3(16, 16, 0));
	InventoryGrid->SetGridShift(D3DXVECTOR3(71, 0, 0));
	InventoryGrid->SetItemSize(D3DXVECTOR3(64, 64, 0));

	InventoryGrid->OnSelectedItemChanged = std::bind(&Game::OnBeltItemChanged, m_game);

	InventoryGrid->Items()[0] = &Prototype::Find("Lattice");
	InventoryGrid->Items()[1] = &Prototype::Find("Floor");
	InventoryGrid->Items()[2] = &Prototype::Find("Wall");
	InventoryGrid->Items()[3] = &Prototype::Find("Table");
	InventoryGrid->Items()[4] = &Prototype::Find("Door");

	return err_noErr;
}

ErrCode Gui::CreateEscapeMenu()
{
	int screenWidth = Doh3d::RenderMan::GetRenderPars().ResolutionWidth;
	int screenHeight = Doh3d::RenderMan::GetRenderPars().ResolutionHeight;

	CreatePanel(EscapeMenu_Fade, 0, 0, (FLOAT)screenWidth, (FLOAT)screenHeight, "MenuFade_32_32_1.png");

	CreateButton(EscapeMenu_ReturnToGame, (FLOAT)((screenWidth - 256) / 2), (FLOAT)((screenHeight - 32) / 2 - 88), 256, 32,
				 "Button_256_32_1.png", "ButtonPressed_256_32_1.png",
				 "ButtonLight_256_32_1.png", "ButtonBw_256_32_1.png");
	EscapeMenu_ReturnToGame->SetFont("Gadugi");
	EscapeMenu_ReturnToGame->SetText("Return to Game");
	EscapeMenu_ReturnToGame->SetOnClickEvent(std::bind(&Game::ReturnToGame, m_game));

	CreateButton(EscapeMenu_SaveMap, (FLOAT)((screenWidth - 256) / 2), (FLOAT)((screenHeight - 32) / 2 - 40), 256, 32,
				 "Button_256_32_1.png", "ButtonPressed_256_32_1.png",
				 "ButtonLight_256_32_1.png", "ButtonBw_256_32_1.png");
	EscapeMenu_SaveMap->SetFont("Gadugi");
	EscapeMenu_SaveMap->SetText("Save Map");
	EscapeMenu_SaveMap->SetOnClickEvent(std::bind(&Game::SaveMap, m_game));

	CreateButton(EscapeMenu_ExitToMain, (FLOAT)((screenWidth - 256) / 2), (FLOAT)((screenHeight - 32) / 2 + 24), 256, 32,
				 "Button_256_32_1.png", "ButtonPressed_256_32_1.png",
				 "ButtonLight_256_32_1.png", "ButtonBw_256_32_1.png");
	EscapeMenu_ExitToMain->SetFont("Gadugi");
	EscapeMenu_ExitToMain->SetText("Exit to Main Menu");
	EscapeMenu_ExitToMain->SetOnClickEvent(std::bind(&Game::ReturnToMainMenu, m_game));

	return err_noErr;
}

ErrCode Gui::SetNewGuiIfNeeded()
{
	LOG("Gui::SetNewGuiIfNeeded()");
	ErrCode err;

	if (!m_newGuiReady)
		return err_noErr;

	err = DeleteGuis();
	if (err != err_noErr)
	{
		echo("ERROR: Can't delete Guis.");
		return err;
	}

	if (m_newGuis.size() != 0)
	{
		m_guis.resize(m_newGuis.size());
		std::copy(m_newGuis.begin(), m_newGuis.end(), m_guis.begin());
		m_newGuis.clear();
	}

	m_newGuiReady = false;
	return err_noErr;
}
