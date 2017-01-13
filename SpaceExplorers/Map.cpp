#include "stdafx.h"
#include "Map.h"

#include "Scene.h"


Map::Map(int pWidth, int pHeight)
	: m_width(pWidth)
	, m_height(pHeight)
{
	m_tiles.resize(m_width * m_height);

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
			m_tiles[x + y * m_width].SetPosition((float)x * Scene::TILESIZE, (float)y * Scene::TILESIZE, (float)Scene::TILESIZE);
	}
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

Tile* Map::HitTestTile(const D3DXVECTOR2& pAbsolutePosition)
{
	int ceilX = (int)std::floor(pAbsolutePosition.x);
	int ceilY = (int)std::floor(pAbsolutePosition.y);

	if (ceilX < 0 || ceilX >= m_width || ceilY < 0 || ceilY >= m_height)
		return nullptr;

	return &m_tiles[ceilX + ceilY * m_width];
}
