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

	class Atmosphere& Atmosphere() { return m_atmosphere; }
	const class Atmosphere& Atmosphere() const { return m_atmosphere; }

private:

	class Atmosphere m_atmosphere;

};


#endif // INC_THING_H
