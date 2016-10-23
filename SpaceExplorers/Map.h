#pragma once

#ifndef INC_MAP_H
#define INC_MAP_H


#include "ErrCodes.h"
#include "Tile.h"


class Map
{
public:

	Map(int pWidth, int pHeight);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	Tile& GetTile(int x, int y) { return m_tiles[x + y * m_width]; }
	const Tile& GetTile(int x, int y) const { return m_tiles[x + y * m_width]; }

	ErrCode Load();
	ErrCode Unload();

	Tile* HitTest(const D3DXVECTOR2& pAbsolutePosition);

private:

	int m_width;
	int m_height;

	std::vector<Tile> m_tiles;

public:

	static const int c_tileSize;
	
};


#endif // INC_MAP_H
