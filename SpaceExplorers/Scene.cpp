#include "stdafx.h"
#include "Scene.h"

#include "Engine.h"


ErrCode Scene::Load()
{
	LOG("Scene::Load()");
	ErrCode3d err;

	// Background

	err = Doh3d::ResourceMan::GetTi(c_backgroundTextureName, m_backgroundTi);
	if (err != err3d_noErr)
	{
		echo("ERROR: Can't get TI for scene background: \"", c_backgroundTextureName, "\".");
		return err_cantLoadBackground;
	}

	// Get background scale

	D3DXVECTOR2 sizeOrig = D3DXVECTOR2((FLOAT)Doh3d::RenderMan::GetRenderPars().ResolutionWidth, (FLOAT)Doh3d::RenderMan::GetRenderPars().ResolutionHeight);
	D3DXVECTOR2 scaleCenter(0, 0);
	D3DXVECTOR2 scale = D3DXVECTOR2(sizeOrig.x / 1920, sizeOrig.y / 1024);
	if (scale.x > scale.y)
		scale.y = scale.x;
	else
		scale.x = scale.y;

	D3DXMatrixTransformation2D(&m_backgroundTransformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);

	// Get required zoom for all tiles

	m_viewport.PositionX = 5;
	m_viewport.PositionY = 4;
	m_viewport.Width2 = 10;
	m_viewport.Height2 = 8;
	scale.x = scale.y = 1;
	D3DXMatrixTransformation2D(&m_transformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);

	return err_noErr;
}

ErrCode Scene::Unload()
{
	return err_noErr;
}


ErrCode Scene::Draw(Doh3d::Sprite& pSprite) const
{
	LOG("Scene::Draw()");
	ErrCode err;
	ErrCode3d err3d;
	HRESULT hRes;

	// Begin

	err3d = Doh3d::Drawer::BeginScene();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't begin scene.");
		return err_cantBeginScene;
	}

	err3d = pSprite.Begin();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't begin sprite.");
		return err_cantBeginSprite;
	}

	// Background

	pSprite.Get()->SetTransform(&m_backgroundTransformMatrix);
	hRes = pSprite.Get()->Draw(Doh3d::ResourceMan::GetTexture(m_backgroundTi).Get(), 0, 0, &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
	if (hRes != S_OK)
	{
		echo("ERROR: Can't draw scene background.");
		return err_cantDrawBackground;
	}

	// Map

	if (Engine::GetInstance()->GetGame().HasMap())
	{
		err = DrawMap(pSprite, Engine::GetInstance()->GetGame().GetMap());
		if (err != err_noErr)
		{
			echo("ERROR: Can't draw map.");
			return err;
		}
	}

	// Gui

	err = Engine::GetInstance()->GetGame().GetGui().Draw(pSprite);
	if (err != err_noErr)
	{
		echo("ERROR: Can't draw Gui.");
		return err;
	}
	
	// Cursor

	err3d = Doh3d::Cursor::Draw(pSprite);
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't draw cursor.");
		return err_cantDrawCursor;
	}

	// End

	err3d = pSprite.End();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't end sprite.");
		return err_cantEndSprite;
	}

	err3d = Doh3d::Drawer::EndScene();
	if (err3d != err3d_noErr)
	{
		echo("ERROR: Can't end scene.");
		return err_cantEndScene;
	}

	return err_noErr;
}


ErrCode Scene::DrawMap(Doh3d::Sprite& pSprite, const std::shared_ptr<Map>& pMap) const
{
	LOG("Scene::DrawMap()");
	ErrCode err;

	int left = (int)(m_viewport.PositionX - m_viewport.Width2);
	if (left < 0) left = 0;

	int top = (int)(m_viewport.PositionY - m_viewport.Height2);
	if (top < 0) top = 0;

	int right = (int)(m_viewport.PositionX + m_viewport.Width2 + 1);
	if (right > pMap->GetWidth() - 1)
		right = pMap->GetWidth() - 1;

	int bottom = (int)(m_viewport.PositionY + m_viewport.Height2 + 1);
	if (bottom > pMap->GetHeight() - 1)
		bottom = pMap->GetHeight() - 1;

	pSprite.Get()->SetTransform(&m_transformMatrix);
	for (int y = top; y < bottom; ++y)
	{
		for (int x = left; x < right; ++x)
		{
			err = pMap->GetTile(x, y).Draw(pSprite, D3DXVECTOR3(
				(m_viewport.PositionX - m_viewport.Width2) * Map::c_tileSize,
				(m_viewport.PositionY - m_viewport.Height2) * Map::c_tileSize, 0));
			if (err != err_noErr)
			{
				echo("ERROR: Can't draw map tile (x: ", x, ", y: ", y, ").");
				return err;
			}
		}
	}

	return err_noErr;
}


Tile* Scene::HitTest(const D3DXVECTOR2& pScreenPosition)
{
	if (!Engine::GetInstance()->GetGame().HasMap())
		return nullptr;

	D3DXVECTOR2 position(
		pScreenPosition.x / Doh3d::RenderMan::GetRenderPars().ResolutionWidth * (m_viewport.Width2 * 2),
		pScreenPosition.y / Doh3d::RenderMan::GetRenderPars().ResolutionHeight * (m_viewport.Height2 * 2));
	position += D3DXVECTOR2(m_viewport.PositionX - m_viewport.Width2, m_viewport.PositionY - m_viewport.Height2);

	return Engine::GetInstance()->GetGame().GetMap()->HitTest(position);
}

Vector2 Scene::GetCoords(const D3DXVECTOR2& pScreenPosition)
{
	if (!Engine::GetInstance()->GetGame().HasMap())
		return Vector2::Empty();

	D3DXVECTOR2 position(
		pScreenPosition.x / Doh3d::RenderMan::GetRenderPars().ResolutionWidth * (m_viewport.Width2 * 2),
		pScreenPosition.y / Doh3d::RenderMan::GetRenderPars().ResolutionHeight * (m_viewport.Height2 * 2));
	position += D3DXVECTOR2(m_viewport.PositionX - m_viewport.Width2, m_viewport.PositionY - m_viewport.Height2);

	return Vector2(std::floor(position.x), std::floor(position.y));
}
