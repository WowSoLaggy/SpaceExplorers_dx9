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
		else if (m_gui.IsRemovalMode())
		{
			err = m_gui.SwitchRemovalMode(false);
			if (err != err_noErr)
			{
				echo("ERROR: Can't turn the removal mode off.");
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
	auto* pTile = m_scene->HitTestTile();
	auto* pThing = m_scene->HitTest();

	std::string text = "(" + std::to_string(coords.x) + ", " + std::to_string(coords.y) + "): ";

	if (pThing != nullptr) text.append(pThing->GetPrototype().TypeName());
	if (!pTile || pTile->IsPassable()) text.append(" P");
	if (!pTile || pTile->IsVentilated()) text.append(" V");
	

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
	m_gui.InventoryGrid->SelectCell(pItemIndex);
	return err_noErr;
}

ErrCode Game::OnBeltItemChanged()
{
	LOG("Game::OnBeltItemChanged()");
	ErrCode err;

	Prototype* pPrototype = dynamic_cast<Prototype*>(m_gui.InventoryGrid->GetSelectedItem());

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
	ErrCode err;

	if (!m_gui.InventoryGrid->GetSelectedItem())
		return err_noErr;

	auto* pPrototype = dynamic_cast<Prototype*>(m_gui.InventoryGrid->GetSelectedItem());
	if (!pPrototype)
	{
		echo("ERROR: Can't parse GridItem to Prototype.");
		return err_cantParseGridItemToPrototype;
	}

	Tile* tile = m_scene->HitTestTile();
	if (!tile || !pPrototype->CheckPrerequisites(tile))
		return err_noErr;

	RealThing* newThing = nullptr;

	if (pPrototype->NeedsSpace())
	{
		newThing = new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoordsTileTopLeft());
		tile->AddChild(newThing);
	}
	else if (pPrototype->NeedsLattice())
	{
		auto* pBasement = tile->FindChild("Lattice");
		if (!pBasement)
		{
			echo("ERROR: Can't find lattice, though it was checked.");
			return err_cantFindRequiredBasement;
		}

		newThing = new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoordsTileTopLeft());
		pBasement->AddChild(newThing);
	}
	else if (pPrototype->NeedsFloor())
	{
		auto* pBasement = tile->FindChild("Floor");
		if (!pBasement)
		{
			echo("ERROR: Can't find floor, though it was checked.");
			return err_cantFindRequiredBasement;
		}

		newThing = new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoordsTileTopLeft());
		pBasement->AddChild(newThing);
	}
	else if (pPrototype->NeedsSurface())
	{
		auto* pBasement = tile->FindChild("Table");
		if (!pBasement)
		{
			pBasement = tile->FindChild("Floor");
			if (!pBasement)
			{
				echo("ERROR: Can't find floor, though it was checked.");
				return err_cantFindRequiredBasement;
			}
		}

		newThing = new RealThing(pPrototype->TypeName(), m_scene->GetAbsoluteCoordsTileTopLeft());
		pBasement->AddChild(newThing);
	}
	else
	{
		echo("ERROR: Unknown requirements for the building: \"", pPrototype->TypeName(), "\".");
		return err_unknownRequirements;
	}

	if (newThing != nullptr)
	{
		err = newThing->Load();
		if (err != err_noErr)
		{
			echo("ERROR: Can't load the built thing.");
			return err_cantLoadThing;
		}
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


ErrCode Game::BeginRemoveMode()
{
	m_gui.SwitchRemovalMode(true);
	return err_noErr;
}

ErrCode Game::EndRemoveMode()
{
	m_gui.SwitchRemovalMode(false);
	return err_noErr;
}

ErrCode Game::TryRemove()
{
	LOG("Game::TryRemove()");
	ErrCode err;

	RealThing* thingToRemove = m_scene->HitTest();
	if (!thingToRemove || !thingToRemove->GetChilds().empty())
		return err_noErr;

	if (!thingToRemove->Parent())
	{
		// RealThing must have a parent (at least Tile)
		return err_realThingHasNoParent;
	}

	thingToRemove->Parent()->RemoveChild(thingToRemove);
	
	err = thingToRemove->Unload();
	if (err != err_noErr)
	{
		echo("ERROR: Can't unload the removed thing.");
		return err_cantUnloadThing;
	}

	delete thingToRemove;

	return err_noErr;
}


ErrCode Game::Interact()
{
	LOG("Game::Interact()");
	ErrCode err;

	RealThing* thingToInteract = m_scene->HitTest();
	if (!thingToInteract)
		return err_noErr;

	err = thingToInteract->Interact();
	if (err != err_noErr)
	{
		echo("ERROR: Can't interact with object: \"", thingToInteract->GetPrototype().TypeName(), "\".");
		return err;
	}

	return err_noErr;
}
