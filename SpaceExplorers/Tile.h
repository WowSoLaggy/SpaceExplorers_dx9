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

	void SetPosition(float pX, float pY, float pSize);
	void SetPosition(const D3DXVECTOR2& pPosition, float pSize);
	const D3DXVECTOR2& Position() const { return m_position; }
	const Doh3d::Geometry::Rect& TileRect() const { return m_tileRect; }


	class Atmosphere& Atmosphere() { return m_atmosphere; }
	const class Atmosphere& Atmosphere() const { return m_atmosphere; }

private:

	D3DXVECTOR2 m_position;
	Doh3d::Geometry::Rect m_tileRect;

	class Atmosphere m_atmosphere;

};


#endif // INC_THING_H
