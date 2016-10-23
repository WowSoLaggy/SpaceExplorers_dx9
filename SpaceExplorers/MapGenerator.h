#pragma once

#ifndef INC_MAPGENERATOR_H
#define INC_MAPGENERATOR_H


#include "Map.h"
#include "Prototype.h"


class MapGenerator
{
public:

	static Map* CreateEmpty();
	static Map* CreateStartLocation();

};


#endif // INC_MAPGENERATOR_H
