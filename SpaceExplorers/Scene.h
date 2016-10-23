#pragma once

#ifndef INC_SCENE_H
#define INC_SCENE_H


#include "ErrCodes.h"
#include "Map.h"
#include "Vector2.h"


class Scene
{
public:

	Doh3d::Viewport& GetViewport() { return m_viewport; }
	const Doh3d::Viewport& GetViewport() const { return m_viewport; }

	ErrCode Load();
	ErrCode Unload();

	ErrCode Draw(Doh3d::Sprite& pSprite) const;

	Tile* HitTest(const D3DXVECTOR2& pScreenPosition);
	Vector2 GetCoords(const D3DXVECTOR2& pScreenPosition);

private:

	Doh3d::Viewport m_viewport;
	D3DXMATRIX m_transformMatrix;

	const std::string c_backgroundTextureName = "Space_1920_1024_1.png";
	D3DXMATRIX m_backgroundTransformMatrix;
	int m_backgroundTi;


	ErrCode DrawMap(Doh3d::Sprite& pSprite, const std::shared_ptr<Map>& pMap) const;

};


#endif // INC_SCENE_H
