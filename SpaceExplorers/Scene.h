#pragma once

#ifndef INC_SCENE_H
#define INC_SCENE_H


#include "ErrCodes.h"
#include "Map.h"
#include "Vector2.h"
#include "Thing.h"


class Scene
{

public:

	static const int TILESIZE;
	static const int TILESIZE2;

public:

	ErrCode Init();
	ErrCode Dispose();

	ErrCode Load();
	ErrCode Unload();

	ErrCode Draw(Doh3d::Sprite& pSprite) const;
	ErrCode Update(float pDeltaTime);


	Doh3d::Viewport& GetViewport() { return m_viewport; }
	const Doh3d::Viewport& GetViewport() const { return m_viewport; }


	ErrCode SetBackground(const std::string& pTextureName);

	Tile* HitTestTile();
	Thing* HitTest();
	Vector2 GetTileCoords(const D3DXVECTOR2& pScreenPosition);		//< Screen -> tile
	Vector2 GetTileCoords();										//< Screen -> tile
	D3DXVECTOR2 GetScreenCoords(const Vector2& pTilePosition);		//< Tile -> screen
	D3DXVECTOR2 GetScreenCoords(const D3DXVECTOR2& pTilePosition);	//< Tile -> screen
	D3DXVECTOR2 GetAbsoluteCoordsTileTopLeft();
	D3DXVECTOR2 GetCursorAbsoluteCoords();

private:

	bool m_isLoaded;

	Doh3d::Viewport m_viewport;
	D3DXMATRIX m_transformMatrix;

	std::string m_backgroundTextureName;
	D3DXMATRIX m_backgroundTransformMatrix;
	int m_backgroundTi;


	ErrCode DrawMap(Doh3d::Sprite& pSprite, const std::shared_ptr<Map>& pMap) const;
	ErrCode LoadBackground();

};


#endif // INC_SCENE_H
