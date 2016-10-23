#include "stdafx.h"
#include "Game.h"


ErrCode Game::OnMouseMove(bool& pHandled)
{
	LOG("Game::OnMouseMove()");
	ErrCode err = err_noErr;

	if (m_mode == GameMode::InGame)
	{
		err = InfoUnderCursor();
		if (err != err_noErr)
		{
			echo("ERROR: Can't get info under cursor.");
			return err;
		}
	}

	return err_noErr;
}

ErrCode Game::OnMouseDown(bool& pHandled, int pButton)
{
	return err_noErr;
}

ErrCode Game::OnMouseUp(bool& pHandled, int pButton)
{
	return err_noErr;
}


ErrCode Game::OnKeyPressed(bool& pHandled, int pKey)
{
	LOG("Game::OnKeyPressed()");
	ErrCode err = err_noErr;

	// TODO: make a map, set handled = true

	if (m_mode == GameMode::InGame)
	{
		if (pKey == DIK_W) err = MoveCameraUp();
		else if (pKey == DIK_A) err = MoveCameraLeft();
		else if (pKey == DIK_S) err = MoveCameraDown();
		else if (pKey == DIK_D) err = MoveCameraRight();
	}

	if (err != err_noErr)
	{
		echo("ERROR: Can't handle key press: \"", pKey, "\".");
		return err;
	}

	return err_noErr;
}

ErrCode Game::OnKeyDown(bool& pHandled, int pKey)
{
	LOG("Game::OnKeyDown()");
	ErrCode err = err_noErr;

	if (m_mode == GameMode::EscapeMenu)
	{
		if (pKey == DIK_ESCAPE) err = EscapeHit();
	}
	else if (m_mode == GameMode::InGame)
	{
		if (pKey == DIK_ESCAPE) err = EscapeHit();
		
		else if (pKey == DIK_GRAVE) err = SelectBeltItem(-1);
		else if (pKey == DIK_1) err = SelectBeltItem(0);
		else if (pKey == DIK_2) err = SelectBeltItem(1);
		else if (pKey == DIK_3) err = SelectBeltItem(2);
		else if (pKey == DIK_4) err = SelectBeltItem(3);
		else if (pKey == DIK_5) err = SelectBeltItem(4);
		else if (pKey == DIK_6) err = SelectBeltItem(5);
		else if (pKey == DIK_7) err = SelectBeltItem(6);
		else if (pKey == DIK_8) err = SelectBeltItem(7);
		else if (pKey == DIK_9) err = SelectBeltItem(8);
		else if (pKey == DIK_0) err = SelectBeltItem(9);
	}

	return err_noErr;
}

ErrCode Game::OnKeyUp(bool& pHandled, int pKey)
{
	return err_noErr;
}
