#pragma once

#ifndef INC_REALTHING_H
#define INC_REALTHING_H


#include "ErrCodes.h"
#include "Thing.h"
#include "Prototype.h"


class RealThing : public Thing
{
public:

	RealThing(const std::string& pPrototypeName)
		: RealThing(pPrototypeName, D3DXVECTOR3(0, 0, 0)) { }

	RealThing(const std::string& pPrototypeName, float pPosX, float pPosY)
		: RealThing(pPrototypeName, D3DXVECTOR3(pPosX, pPosY, 0)) { }

	RealThing(const std::string& pPrototypeName, int pPosX, int pPosY)
		: RealThing(pPrototypeName, D3DXVECTOR3((FLOAT)pPosX, (FLOAT)pPosY, 0)) { }

	RealThing(const std::string& pPrototypeName, const D3DXVECTOR2& pPosition)
		: m_prototype(Prototype::Find(pPrototypeName))
		, m_position(pPosition.x, pPosition.y, 0) { }

	RealThing(const std::string& pPrototypeName, const D3DXVECTOR3& pPosition)
		: m_prototype(Prototype::Find(pPrototypeName))
		, m_position(pPosition) { }


	const Prototype& GetPrototype() const { return m_prototype; }

	Doh3d::AnimationController& Ac() { return m_ac; }
	const Doh3d::AnimationController& Ac() const { return m_ac; }

	D3DXVECTOR3& Position() { return m_position; }
	const D3DXVECTOR3& Position() const { return m_position; }

	D3DCOLOR& DrawColor() { return m_drawColor; }
	const D3DCOLOR& DrawColor() const { return m_drawColor; }
	void ResetDrawColor() { m_drawColor = D3DCOLOR_ARGB(255, 255, 255, 255); }


	virtual bool IsPassable() const override;
	virtual bool IsVentilated() const override;

	virtual Thing* HitTest() override;


	virtual ErrCode Draw(Doh3d::Sprite& pSprite, const D3DXVECTOR3& pOffset) const override;
	virtual ErrCode Load() override;
	virtual ErrCode Unload() override;
	virtual ErrCode Update(float pDeltaTime) override;

private:

	D3DXVECTOR3 m_position;
	D3DCOLOR m_drawColor;

	const Prototype& m_prototype;

	Doh3d::AnimationController m_ac;

};


#endif // INC_REALTHING_H
