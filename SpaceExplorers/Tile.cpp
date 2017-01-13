#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
	m_atmosphere.V() = 2;
	m_atmosphere.T() = 0;
}


void Tile::SetPosition(float pX, float pY, float pSize)
{
	SetPosition(D3DXVECTOR2(pX, pY), pSize);
}

void Tile::SetPosition(const D3DXVECTOR2& pPosition, float pSize)
{
	m_position = pPosition;
	m_tileRect = Doh3d::Geometry::Rect(m_position.x, m_position.y, m_position.x + pSize, m_position.y + pSize);
}
