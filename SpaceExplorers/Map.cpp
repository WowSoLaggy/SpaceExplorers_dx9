#include "stdafx.h"
#include "Map.h"


Map::Map(int pWidth, int pHeight)
	: m_width(pWidth)
	, m_height(pHeight)
{
	m_tiles.resize(pWidth * pHeight);
}


ErrCode Map::Load()
{
	LOG("Map::Load()");
	ErrCode err;

	for (auto& tile : m_tiles)
	{
		err = tile.Load();
		if (err != err_noErr)
		{
			echo("ERROR: Can't load tile.");
			return err;
		}
	}

	return err_noErr;
}

ErrCode Map::Unload()
{
	LOG("Map::Load()");
	ErrCode err;

	for (auto& tile : m_tiles)
	{
		err = tile.Unload();
		if (err != err_noErr)
		{
			echo("ERROR: Can't unload tile.");
			return err;
		}
	}

	return err_noErr;
}

Tile* Map::HitTest(const D3DXVECTOR2& pAbsolutePosition)
{
	int ceilX = (int)std::floor(pAbsolutePosition.x);
	int ceilY = (int)std::floor(pAbsolutePosition.y);

	if (ceilX < 0 || ceilX >= m_width || ceilY < 0 || ceilY >= m_height)
		return nullptr;

	return &m_tiles[ceilX + ceilY * m_width];
}
