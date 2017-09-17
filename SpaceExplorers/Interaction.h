#pragma once

#include "Tile.h"
#include "Character.h"


namespace Controller
{

class Interaction
{
public:

  static bool interact(Model::GameObject* i_object,
                       Model::GameObject* i_subject,
                       Model::GameObject* i_tool);

private:

  static const int INTERACTMAXDIST = Model::Tile::DEFAULT_TILE_SIZE + Model::Tile::DEFAULT_TILE_SIZE / 2;
  static const int INTERACTMAXDISTSQ = INTERACTMAXDIST * INTERACTMAXDIST;


  static bool openDoor(Model::Character& i_object,
                       Model::GameObject& i_subject);

  static bool pickUpObject(Model::Character& i_object,
                           Model::GameObject& i_subject);
};

} // ns Controller
