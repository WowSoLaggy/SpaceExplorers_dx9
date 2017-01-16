#pragma once

#ifndef INC_ENTITY_H
#define INC_ENTITY_H


#include "ErrCodes.h"


class Entity : public Doh3d::ITreeThing<ErrCode>
{
public:

	Entity() { }

	virtual bool IsPassable() const;
	virtual bool IsVentilated() const;


	// pDepth == -1 for infinite depth, pDepth == 1 for childs only, not childs of childs
	Entity* FindChild(const std::string& pChildName, int pDepth = 1) const;

	virtual Entity* HitTest();

};


#endif // INC_ENTITY_H
