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

};


#endif // INC_THING_H
