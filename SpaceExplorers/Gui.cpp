#include "stdafx.h"
#include "Gui.h"


#include "Prototype.h"


ErrCode Gui::Init()
{
	m_isLoaded = false;
	m_whatToBuild = nullptr;

	return err_noErr;
}

ErrCode Gui::Dispose()
{
	m_isLoaded = false;

	for (auto& gui : m_guis)
		delete gui;
	
	return err_noErr;
}


ErrCode Gui::Load()
{
	LOG("Gui::Load()");
	ErrCode3d err3d;

	// Load Guis

	for (auto& gui : m_guis)
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


	// Rescale Gui

	int screenWidth = Doh3d::RenderMan::GetRenderPars().ResolutionWidth;
	int screenHeight = Doh3d::RenderMan::GetRenderPars().ResolutionHeight;

	int gridSizeX = 735;
	int gridSizeY = 96;
	InventoryGrid->Position().x = (float)((screenWidth - gridSizeX) / 2);
	InventoryGrid->Position().y = (float)((screenHeight - gridSizeY));
	InventoryGrid->SetFrameOffset(D3DXVECTOR3(14, 14, 0));
	InventoryGrid->SetGridOffset(D3DXVECTOR3(16, 16, 0));
	InventoryGrid->SetGridShift(D3DXVECTOR3(71, 0, 0));


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
	
	// Draw building mode blueprint

	if (m_whatToBuild != nullptr)
	{
		D3DXVECTOR2 position2 = Doh3d::InputMan::GetCursorPosition();

		Tile* tile = m_scene->HitTest(position2);
		auto color = m_whatToBuild->CheckPrerequisites(tile) ? D3DCOLOR_ARGB(255, 155, 255, 155) : D3DCOLOR_ARGB(255, 255, 155, 155);
		
		D3DXVECTOR3 position3(position2.x, position2.y, 0);
		hRes = pSprite.Get()->Draw(Doh3d::ResourceMan::GetTexture(m_whatToBuild->Ti()).Get(), 0, 0, &position3, color);
		if (hRes != S_OK)
		{
			echo("ERROR: Can't draw thing (type name: \"", m_whatToBuild->TypeName(), "\").");
			return err_cantDrawThing;
		}
	}

	return err_noErr;
}


ErrCode Gui::CreateGameGui()
{
	// TODO: Why InfoText is misplaced?

	CreatePanel(InfoPanel, 20, 20, 256, 96, "Panel_256_96_1.png");
	CreateText(InfoText, 37, 33, "");


	int gridSizeX = 735;
	int gridSizeY = 96;
	CreateGGrid(InventoryGrid,
						 (float)(Doh3d::RenderMan::GetRenderPars().ResolutionWidth / 2),
						 (float)(Doh3d::RenderMan::GetRenderPars().ResolutionHeight / 2),
						 (float)gridSizeX, (float)gridSizeY, 10, "Inventory_735_96_1.png", "Frame_68_68_1.png");
	
	InventoryGrid->Items()[0] = &Prototype::Find("Floor");
	InventoryGrid->Items()[1] = &Prototype::Find("Wall");
	InventoryGrid->Items()[2] = &Prototype::Find("Table");
	InventoryGrid->Items()[3] = &Prototype::Find("Door");

	return err_noErr;
}


ErrCode Gui::SwitchBuildMode(const Prototype* pWhatToBuild)
{
	m_whatToBuild = pWhatToBuild;
	return err_noErr;
}
