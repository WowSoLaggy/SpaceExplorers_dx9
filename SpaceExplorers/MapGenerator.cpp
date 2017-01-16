#include "stdafx.h"
#include "MapGenerator.h"

#include "Thing.h"
#include "Scene.h"


Map* MapGenerator::CreateEmpty()
{
	return new Map(50, 50);
}

Map* MapGenerator::CreateStartLocation()
{
	Map* map = new Map(50, 50);
	
	const std::string LATTICE = "Lattice";
	const std::string WALL = "Wall";
	const std::string FLOOR = "Floor";
	const std::string TABLE = "Table";
	const std::string DOOR = "Door";

	for (int y = 20; y < 30; ++y)
	{
		for (int x = 20; x < 30; ++x)
		{
			map->GetTile(x, y).AddChild(new Thing(LATTICE, x * Scene::TILESIZE, y * Scene::TILESIZE));
			map->GetTile(x, y).GetChilds()[0]->AddChild(new Thing(FLOOR, x * Scene::TILESIZE, y * Scene::TILESIZE));
		}
	}

	for (int x = 20; x < 30; ++x)
	{
		map->GetTile(x, 20).GetChilds()[0]->GetChilds()[0]->AddChild(new Thing(WALL, x * Scene::TILESIZE, 20 * Scene::TILESIZE));
		map->GetTile(x, 29).GetChilds()[0]->GetChilds()[0]->AddChild(new Thing(WALL, x * Scene::TILESIZE, 29 * Scene::TILESIZE));
	}

	for (int y = 21; y < 29; ++y)
	{
		map->GetTile(20, y).GetChilds()[0]->GetChilds()[0]->AddChild(new Thing(WALL, 20 * Scene::TILESIZE, y * Scene::TILESIZE));

		if (y != 27)
			map->GetTile(29, y).GetChilds()[0]->GetChilds()[0]->AddChild(new Thing(WALL, 29 * Scene::TILESIZE, y * Scene::TILESIZE));
	}

	map->GetTile(23, 23).GetChilds()[0]->GetChilds()[0]->AddChild(new Thing(TABLE, 23 * Scene::TILESIZE, 23 * Scene::TILESIZE));
	map->GetTile(29, 27).GetChilds()[0]->GetChilds()[0]->AddChild(new Thing(DOOR, 29 * Scene::TILESIZE, 27 * Scene::TILESIZE));

	return map;
}

