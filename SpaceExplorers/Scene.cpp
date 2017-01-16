#include "stdafx.h"
#include "Scene.h"

#include "Engine.h"


const int Scene::TILESIZE = 64;


ErrCode Scene::Init()
{
	m_backgroundTextureName = "";
	m_isLoaded = false;
	return err_noErr;
}

ErrCode Scene::Dispose()
{
	m_backgroundTextureName = "";
	m_isLoaded = false;
	return err_noErr;
}


ErrCode Scene::Load()
{
	LOG("Scene::Load()");
	ErrCode err;

	err = LoadBackground();
	if (err != err_noErr)
	{
		echo("ERROR: Can't load scene background.");
		return err;
	}

	// Set viewport

	m_viewport.PositionX = 25;
	m_viewport.PositionY = 25;
	m_viewport.Width2 = 10;
	m_viewport.Height2 = 8;
	
	// Get required zoom for all tiles

	D3DXVECTOR2 scaleCenter(0, 0);
	D3DXVECTOR2 scale(1, 1);
	D3DXMatrixTransformation2D(&m_transformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);

	m_isLoaded = true;

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
	hRes = pSprite.Get()->Draw(Doh3d::ResourceMan::GetTexture(m_backgroundTi).Get(), &Doh3d::ResourceMan::GetTexture(m_backgroundTi).GetFrame(0), 0, &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(255, 255, 255, 255));
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
				(m_viewport.PositionX - m_viewport.Width2) * TILESIZE,
				(m_viewport.PositionY - m_viewport.Height2) * TILESIZE, 0));
			if (err != err_noErr)
			{
				echo("ERROR: Can't draw map tile (x: ", x, ", y: ", y, ").");
				return err;
			}
		}
	}

	return err_noErr;
}


ErrCode Scene::SetBackground(const std::string& pTextureName)
{
	LOG("Scene::SetBackground()");
	ErrCode err;
	
	m_backgroundTextureName = pTextureName;
	
	if (m_isLoaded)
	{
		err = LoadBackground();
		if (err != err_noErr)
		{
			echo("ERROR: Can't load scene background.");
			return err;
		}
	}

	return err_noErr;
}

ErrCode Scene::LoadBackground()
{
	LOG("Scene::LoadBackground()");
	ErrCode3d err3d;

	if (m_backgroundTextureName.size() != 0)
	{
		// Background

		err3d = Doh3d::ResourceMan::GetTi(m_backgroundTextureName, m_backgroundTi);
		if (err3d != err3d_noErr)
		{
			echo("ERROR: Can't get TI for scene background: \"", m_backgroundTextureName, "\".");
			return err_cantLoadBackground;
		}

		// Get background scale

		D3DXVECTOR2 scaleCenter(0, 0);
		D3DXVECTOR2 sizeOrig = D3DXVECTOR2((FLOAT)Doh3d::RenderMan::GetRenderPars().ResolutionWidth, (FLOAT)Doh3d::RenderMan::GetRenderPars().ResolutionHeight);
		auto backgroundSize = Doh3d::ResourceMan::GetTexture(m_backgroundTi).GetSize();
		D3DXVECTOR2 scale = D3DXVECTOR2(sizeOrig.x / backgroundSize.x, sizeOrig.y / backgroundSize.y);
		if (scale.x > scale.y)
			scale.y = scale.x;
		else
			scale.x = scale.y;
		D3DXMatrixTransformation2D(&m_backgroundTransformMatrix, &scaleCenter, 0, &scale, 0, 0, 0);
	}

	return err_noErr;
}


Tile* Scene::HitTestTile()
{
	if (!Engine::GetInstance()->GetGame().HasMap())
		return nullptr;

	auto screenPosition = Doh3d::InputMan::GetCursorPosition();

	D3DXVECTOR2 position(
		screenPosition.x / Doh3d::RenderMan::GetRenderPars().ResolutionWidth * (m_viewport.Width2 * 2),
		screenPosition.y / Doh3d::RenderMan::GetRenderPars().ResolutionHeight * (m_viewport.Height2 * 2));
	position += D3DXVECTOR2(m_viewport.PositionX - m_viewport.Width2, m_viewport.PositionY - m_viewport.Height2);

	return Engine::GetInstance()->GetGame().GetMap()->HitTestTile(position);
}

Thing* Scene::HitTest()
{
	if (auto* pTile = HitTestTile())
		return dynamic_cast<Thing*>(pTile->HitTest());

	return nullptr;
}


Vector2 Scene::GetTileCoords()
{
	return GetTileCoords(Doh3d::InputMan::GetCursorPosition());
}

Vector2 Scene::GetTileCoords(const D3DXVECTOR2& pScreenPosition)
{
	if (!Engine::GetInstance()->GetGame().HasMap())
		return Vector2::Empty();

	D3DXVECTOR2 position(
		pScreenPosition.x / Doh3d::RenderMan::GetRenderPars().ResolutionWidth * (m_viewport.Width2 * 2),
		pScreenPosition.y / Doh3d::RenderMan::GetRenderPars().ResolutionHeight * (m_viewport.Height2 * 2));
	position += D3DXVECTOR2(m_viewport.PositionX - m_viewport.Width2, m_viewport.PositionY - m_viewport.Height2);

	return Vector2(std::floor(position.x), std::floor(position.y));
}

D3DXVECTOR2 Scene::GetScreenCoords(const Vector2& pTilePosition)
{
	return GetScreenCoords(D3DXVECTOR2((FLOAT)pTilePosition.x, (FLOAT)pTilePosition.y));
}

D3DXVECTOR2 Scene::GetScreenCoords(const D3DXVECTOR2& pTilePosition)
{
	if (!Engine::GetInstance()->GetGame().HasMap())
		return D3DXVECTOR2(0, 0);

	FLOAT x = (pTilePosition.x - m_viewport.PositionX + m_viewport.Width2) * TILESIZE;
	FLOAT y = (pTilePosition.y - m_viewport.PositionY + m_viewport.Height2) * TILESIZE;

	return D3DXVECTOR2(x, y);
}

D3DXVECTOR2 Scene::GetAbsoluteCoordsTileTopLeft()
{
	if (!Engine::GetInstance()->GetGame().HasMap())
		return D3DXVECTOR2(0, 0);

	auto tileCoords = GetTileCoords();
	return D3DXVECTOR2((FLOAT)(tileCoords.x * TILESIZE), (FLOAT)(tileCoords.y * TILESIZE));
}

D3DXVECTOR2 Scene::GetCursorAbsoluteCoords()
{
	return Doh3d::InputMan::GetCursorPosition() + D3DXVECTOR2(m_viewport.Left() * TILESIZE, m_viewport.Top() * TILESIZE);
}


ErrCode Scene::Update(float pDeltaTime)
{
	LOG("Scene::Update()");
	ErrCode err;

	// Update game

	err = Engine::GetInstance()->GetGame().Update(pDeltaTime);
	if (err != err_noErr)
	{
		echo("ERROR: Can't update game.");
		return err;
	}

	return err_noErr;
}
