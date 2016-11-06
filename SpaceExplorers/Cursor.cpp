#include "stdafx.h"
#include "Cursor.h"


const std::string Cursor::c_textureNameNormal = "Cursor_32_32_1_n.png";


ErrCode Cursor::SetNormal()
{
	LOG("Cursor::SetNormal()");
	ErrCode3d err3d;

	err3d = Doh3d::Cursor::SetCursorTexture(c_textureNameNormal);
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't set normal cursor.");
		return err_cantSetCursor;
	}

	return err_noErr;
}
