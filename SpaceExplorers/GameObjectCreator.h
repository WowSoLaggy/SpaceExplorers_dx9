#pragma once

#include "GameObject.h"


class GameObjectCreator
{
public:

  static GameObject* createLattice();
  static GameObject* createMan();

};
