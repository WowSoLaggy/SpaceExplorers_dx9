#include "stdafx.h"
#include "Gui.h"


ErrCode Gui::OnMouseMove(bool& pHandled)
{
	LOG("Gui::OnMouseMove()");
	ErrCode err;
	ErrCode3d err3d;
	pHandled = false;

	for (auto& gui : m_guis)
	{
		err3d = gui->OnMouseMove(pHandled);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Error while OnMouseMove.");
			return err_guiInputError;
		}
	}

	err = SetNewGuiIfNeeded();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set new Guis.");
		return err;
	}

	return err_noErr;
}

ErrCode Gui::OnMouseDown(bool& pHandled, int pButton)
{
	LOG("Gui::OnMouseDown()");
	ErrCode err;
	ErrCode3d err3d;
	pHandled = false;

	for (auto& gui : m_guis)
	{
		err3d = gui->OnMouseDown(pHandled, pButton);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Error while OnMouseDown.");
			return err_guiInputError;
		}
	}

	err = SetNewGuiIfNeeded();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set new Guis.");
		return err;
	}

	return err_noErr;
}

ErrCode Gui::OnMouseUp(bool& pHandled, int pButton)
{
	LOG("Gui::OnMouseUp()");
	ErrCode err;
	ErrCode3d err3d;
	pHandled = false;

	for (auto& gui : m_guis)
	{
		err3d = gui->OnMouseUp(pHandled, pButton);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Error while OnMouseUp.");
			return err_guiInputError;
		}
	}

	err = SetNewGuiIfNeeded();
	if (err != err_noErr)
	{
		echo("ERROR: Can't set new Guis.");
		return err;
	}

	return err_noErr;
}

ErrCode Gui::OnKeyPressed(bool& pHandled, int pKey)
{
	LOG("Gui::OnKeyPressed()");
	pHandled = false;
	return err_noErr;
}

ErrCode Gui::OnKeyDown(bool& pHandled, int pKey)
{
	LOG("Gui::OnKeyDown()");
	pHandled = false;
	return err_noErr;
}

ErrCode Gui::OnKeyUp(bool& pHandled, int pKey)
{
	LOG("Gui::OnKeyUp()");
	pHandled = false;
	return err_noErr;
}
