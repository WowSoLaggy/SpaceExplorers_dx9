#include "stdafx.h"
#include "MapGenerator.h"

#include "RealThing.h"


Map* MapGenerator::CreateEmpty()
{
	return new Map(20, 20);
}

Map* MapGenerator::CreateStartLocation()
{
	Map* map = new Map(15, 15);

	const std::string WALL = "Wall";
	const std::string FLOOR = "Floor";
	const std::string TABLE = "Table";
	const std::string DOOR = "Door";


	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
			map->GetTile(x, y).AddChild(new RealThing(FLOOR, x * Map::c_tileSize, y * Map::c_tileSize));
	}

	for (int x = 0; x < 10; ++x)
	{
		map->GetTile(x, 0).GetChilds()[0]->AddChild(new RealThing(WALL, x * Map::c_tileSize, 0 * Map::c_tileSize));
		map->GetTile(x, 9).GetChilds()[0]->AddChild(new RealThing(WALL, x * Map::c_tileSize, 9 * Map::c_tileSize));
	}

	for (int y = 1; y < 9; ++y)
	{
		map->GetTile(0, y).GetChilds()[0]->AddChild(new RealThing(WALL, 0 * Map::c_tileSize, y * Map::c_tileSize));

		if (y != 7)
			map->GetTile(9, y).GetChilds()[0]->AddChild(new RealThing(WALL, 9 * Map::c_tileSize, y * Map::c_tileSize));
	}

	map->GetTile(3, 3).GetChilds()[0]->AddChild(new RealThing(TABLE, 3 * Map::c_tileSize, 3 * Map::c_tileSize));
	map->GetTile(9, 7).GetChilds()[0]->AddChild(new RealThing(DOOR, 9 * Map::c_tileSize, 7 * Map::c_tileSize));

	return map;
}

