#include "stdafx.h"
#include "Game.h"

#include "Engine.h"


ErrCode Game::EscapeHit()
{
	if (m_mode == GameMode::InGame)
	{
		m_mode = GameMode::EscapeMenu;
		m_gui.CreateOrUpdateGui(GuiMode::EscapeMenu);
	}
	else if (m_mode == GameMode::EscapeMenu)
	{
		m_mode = GameMode::InGame;
		m_gui.CreateOrUpdateGui(GuiMode::InGame);
	}

	return err_noErr;
}


ErrCode Game::InfoUnderCursor()
{
	Vector2 coords = m_scene->GetTileCoords(Doh3d::InputMan::GetCursorPosition());
	Tile* tile = m_scene->HitTest(Doh3d::InputMan::GetCursorPosition());

	std::string text = "(" + std::to_string(coords.x) + ", " + std::to_string(coords.y) + "): ";

	if (!tile || tile->IsPassable()) text.append("P");
	if (!tile || tile->IsVentilated()) text.append("V");

	m_gui.InfoText->SetText(text);

	return err_noErr;
}


ErrCode Game::MoveCameraLeft()
{
	if (!HasMap())
		return err_noErr;

	float newPosX = Engine::GetInstance()->GetScene().GetViewport().PositionX - 0.5f;
	if (newPosX < 0) newPosX = 0;
	Engine::GetInstance()->GetScene().GetViewport().PositionX = newPosX;

	return err_noErr;
}

ErrCode Game::MoveCameraRight()
{
	if (!HasMap())
		return err_noErr;

	float newPosX = Engine::GetInstance()->GetScene().GetViewport().PositionX + 0.5f;
	if (newPosX > m_map->GetWidth()) newPosX = (float)m_map->GetWidth();
	Engine::GetInstance()->GetScene().GetViewport().PositionX = newPosX;

	return err_noErr;
}

ErrCode Game::MoveCameraUp()
{
	if (!HasMap())
		return err_noErr;

	float newPosY = Engine::GetInstance()->GetScene().GetViewport().PositionY - 0.5f;
	if (newPosY < 0) newPosY = 0;
	Engine::GetInstance()->GetScene().GetViewport().PositionY = newPosY;

	return err_noErr;
}

ErrCode Game::MoveCameraDown()
{
	if (!HasMap())
		return err_noErr;

	float newPosY = Engine::GetInstance()->GetScene().GetViewport().PositionY + 0.5f;
	if (newPosY > m_map->GetHeight()) newPosY = (float)m_map->GetHeight();
	Engine::GetInstance()->GetScene().GetViewport().PositionY = newPosY;

	return err_noErr;
}


ErrCode Game::SelectBeltItem(int pItemIndex)
{
	LOG("Game::SelectBeltItem()");
	ErrCode err;

	Prototype* pPrototype = dynamic_cast<Prototype*>(m_gui.InventoryGrid->SelectCell(pItemIndex));
	
	err = m_gui.SwitchBuildMode(pPrototype);
	if (err != err_noErr)
	{
		echo("ERROR: Can't switch to build mode.");
		return err;
	}

	return err_noErr;
}
