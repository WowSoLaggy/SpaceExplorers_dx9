#include "stdafx.h"
#include "Game.h"

#include "Engine.h"
#include "RealThing.h"


ErrCode Game::EscapeHit()
{
	LOG("Game::EscapeHit()");
	ErrCode err;

	if (m_mode == GameMode::InGame)
	{
		if (m_gui.IsBuildMode())
		{
			err = SelectBeltItem(-1);
			if (err != err_noErr)
			{
				echo("ERROR: Can't select -1 belt item.");
				return err;
			}
		}
		else
		{
			err = CallEscapeMenu();
			if (err != err_noErr)
			{
				echo("ERROR: Can't call escape menu.");
				return err;
			}
		}
	}
	else if (m_mode == GameMode::EscapeMenu)
	{
		err = ReturnToGame();
		if (err != err_noErr)
		{
			echo("ERROR: Can't return to game.");
			return err;
		}
	}

	err = m_gui.SetNewGuiIfNeeded();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set new Guis.");
		return err;
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


ErrCode Game::TryBuild()
{
	LOG("Game::TryBuild()");

	D3DXVECTOR2 position2 = Doh3d::InputMan::GetCursorPosition();

	if (!m_gui.InventoryGrid->GetSelectedItem())
		return err_noErr;

	auto* pPrototype = dynamic_cast<Prototype*>(m_gui.InventoryGrid->GetSelectedItem());
	if (!pPrototype)
	{
		echo("ERROR: Can't parse GridItem to Prototype.");
		return err_cantParseGridItemToPrototype;
	}

	Tile* tile = m_scene->HitTest(position2);
	if (!tile || !pPrototype->CheckPrerequisites(tile))
		return err_noErr;

	if (pPrototype->NeedsSpace())
	{
		tile->AddChild(new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoords()));
	}
	else if (pPrototype->NeedsLattice())
	{
		auto* pBasement = tile->FindChild("Lattice");
		if (!pBasement)
		{
			echo("ERROR: Can't find lattice, though it was checked.");
			return err_cantFindRequiredBasement;
		}

		pBasement->AddChild(new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoords()));
	}
	else if (pPrototype->NeedsFloor())
	{
		auto* pBasement = tile->FindChild("Floor");
		if (!pBasement)
		{
			echo("ERROR: Can't find lattice, though it was checked.");
			return err_cantFindRequiredBasement;
		}

		pBasement->AddChild(new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoords()));
	}
	else
	{
		echo("ERROR: Unknown requirements for the building: \"", pPrototype->TypeName(), "\".");
		return err_unknownRequirements;
	}

	return err_noErr;
}


ErrCode Game::SaveMap()
{
	LOG("Game::SaveMap()");
	ErrCode err;

	if (!m_map)
		return err_noErr;

	err = Map::SaveToFile(*m_map, "main.map");
	if (err != err_noErr)
	{
		echo("ERROR: Can't save map.");
		return err;
	}

	return err_noErr;
}
