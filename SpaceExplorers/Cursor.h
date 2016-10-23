#pragma once

#ifndef INC_CURSOR_H
#define INC_CURSOR_H


#include "ErrCodes.h"


class Cursor
{
public:

	static ErrCode SetNormal();

private:

	static const std::string c_textureNameNormal;

};


#endif // INC_CURSOR_H
