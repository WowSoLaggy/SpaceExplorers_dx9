#pragma once

#ifndef INC_TILE_H
#define INC_TILE_H


#include "ErrCodes.h"
#include "Thing.h"
#include "Atmosphere.h"


class Tile : public Thing
{
public:

	Tile();

private:

	Atmosphere m_atmosphere;

};


#endif // INC_THING_H
