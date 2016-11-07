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

	std::vector<Tile>& Tiles() { return m_tiles; }
	const std::vector<Tile>& Tiles() const { return m_tiles; }

	Tile& GetTile(int x, int y) { return m_tiles[x + y * m_width]; }
	const Tile& GetTile(int x, int y) const { return m_tiles[x + y * m_width]; }

	ErrCode Load();
	ErrCode Unload();

	Tile* HitTestTile(const D3DXVECTOR2& pAbsolutePosition);

public:

	static const std::string c_mapFolder;
	static ErrCode SaveToFile(const Map& pMap, const std::string& pFileName);
	static ErrCode LoadFromFile(Map*& pMap, const std::string& pFileName);

private:

	int m_width;
	int m_height;

	std::vector<Tile> m_tiles;

};


#endif // INC_MAP_H
