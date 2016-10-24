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


	const Prototype& GetPrototype() { return m_prototype; }

	D3DXVECTOR3& Position() { return m_position; }
	const D3DXVECTOR3& Position() const { return m_position; }

	virtual bool IsPassable() const override;
	virtual bool IsVentilated() const override;


	virtual ErrCode Draw(Doh3d::Sprite& pSprite, const D3DXVECTOR3& pOffset) const override;
	virtual ErrCode Load() override;
	virtual ErrCode Unload() override;

public:

	D3DXVECTOR3 m_position;

	const Prototype& m_prototype;

};


#endif // INC_REALTHING_H
