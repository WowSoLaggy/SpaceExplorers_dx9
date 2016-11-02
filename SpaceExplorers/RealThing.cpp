#include "stdafx.h"
#include "RealThing.h"

#include "Engine.h"


ErrCode RealThing::Draw(Doh3d::Sprite& pSprite, const D3DXVECTOR3& pOffset) const
{
	LOG("RealThing::Draw()");
	HRESULT hRes;

	hRes = pSprite.Get()->Draw(Doh3d::ResourceMan::GetTexture(m_prototype.Ti()).Get(), 0, 0, &(m_position - pOffset), m_drawColor);
	if (hRes != S_OK)
	{
		echo("ERROR: Can't draw thing (type name: \"", m_prototype.TypeName(), "\").");
		return err_cantDrawThing;
	}

	return Thing::Draw(pSprite, pOffset);
}

ErrCode RealThing::Load()
{
	ResetDrawColor();
	return Doh3d::ITreeThing<ErrCode>::Load();
}

ErrCode RealThing::Unload()
{
	return Doh3d::ITreeThing<ErrCode>::Unload();
}



bool RealThing::IsPassable() const
{
	if (!m_prototype.IsPassable())
		return false;

	for (auto& child : m_childs)
	{
		Thing* pThing = dynamic_cast<Thing*>(child);
		if (pThing && !pThing->IsPassable())
			return false;
	}

	return true;
}

bool RealThing::IsVentilated() const
{
	if (!m_prototype.IsVentilated())
		return false;

	for (auto& child : m_childs)
	{
		Thing* pThing = dynamic_cast<Thing*>(child);
		if (pThing && !pThing->IsVentilated())
			return false;
	}

	return true;
}


Thing* RealThing::HitTest()
{
	Thing* pThing = Thing::HitTest();
	if (pThing != nullptr)
		return pThing;

	auto point = Engine::GetInstance()->GetScene().GetCursorAbsoluteCoords() - D3DXVECTOR2(m_position.x, m_position.y);
	return Doh3d::ResourceMan::GetTexture(m_prototype.Ti()).HitTest(point) ? this : nullptr;
}
