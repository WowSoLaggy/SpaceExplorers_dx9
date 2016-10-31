#pragma once

#ifndef INC_THING_H
#define INC_THING_H


#include "ErrCodes.h"


class Thing : public Doh3d::ITreeThing<ErrCode>
{
public:

	Thing() { }

	virtual bool IsPassable() const;
	virtual bool IsVentilated() const;


	// pDepth == -1 for infinite depth, pDepth == 1 for childs only, not childs of childs
	Thing* FindChild(const std::string& pChildName, int pDepth = 1) const;

	virtual Thing* HitTest();

};


#endif // INC_THING_H
