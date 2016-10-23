#include "stdafx.h"
#include "Engine.h"


void Engine::OnMouseMove()
{
	LOG("Engine::OnMouseMove()");
	ErrCode err;

	// Handle by GUI

	bool handled = false;
	err = m_game.GetGui().OnMouseMove(handled);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking Scene OnMouseMove.");
		return;
	}
	if (handled)
		return;

	// Handle by game

	err = m_game.OnMouseMove(handled);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking game OnMouseMove.");
		return;
	}
}

void Engine::OnMouseDown(int pButton)
{
	LOG("Engine::OnMouseDown()");
	ErrCode err;

	// Handle by GUI

	bool handled = false;
	err = m_game.GetGui().OnMouseDown(handled, pButton);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking Scene OnMouseDown.");
		return;
	}
	if (handled)
		return;

	// Handle by game

	err = m_game.OnMouseDown(handled, pButton);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking game OnMouseDown.");
		return;
	}
}

void Engine::OnMouseUp(int pButton)
{
	LOG("Engine::OnMouseUp()");
	ErrCode err;

	// Handle by GUI

	bool handled = false;
	err = m_game.GetGui().OnMouseUp(handled, pButton);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking Scene OnMouseUp.");
		return;
	}
	if (handled)
		return;

	// Handle by game

	err = m_game.OnMouseUp(handled, pButton);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking game OnMouseUp.");
		return;
	}
}


void Engine::OnKeyPressed(int pKey)
{
	LOG("Engine::OnKeyPressed()");
	ErrCode err;

	// Handle by GUI

	bool handled = false;
	err = m_game.GetGui().OnKeyPressed(handled, pKey);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking Scene OnKeyPressed.");
		return;
	}
	if (handled)
		return;

	// Handle by game

	err = m_game.OnKeyPressed(handled, pKey);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking game OnKeyPressed.");
		return;
	}
}

void Engine::OnKeyDown(int pKey)
{
	LOG("Engine::OnKeyDown()");
	ErrCode err;

	// Handle by GUI

	bool handled = false;
	err = m_game.GetGui().OnKeyDown(handled, pKey);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking Scene OnKeyDown.");
		return;
	}
	if (handled)
		return;

	// Handle by game

	err = m_game.OnKeyDown(handled, pKey);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking game OnKeyDown.");
		return;
	}
}

void Engine::OnKeyUp(int pKey)
{
	LOG("Engine::OnKeyUp()");
	ErrCode err;

	// Handle by GUI

	bool handled = false;
		err = m_game.GetGui().OnKeyUp(handled, pKey);
		if (err != err_noErr)
		{
			echo("ERROR: Error occurred while checking Scene OnKeyUp.");
			return;
		}
	if (handled)
		return;

	// Handle by game

	err = m_game.OnKeyUp(handled, pKey);
	if (err != err_noErr)
	{
		echo("ERROR: Error occurred while checking game OnKeyUp.");
		return;
	}
}
