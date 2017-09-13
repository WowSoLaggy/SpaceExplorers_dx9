#include "stdafx.h"
#include "Interaction.h"

#include "GameObject.h"
#include "Tile.h"


namespace Controller
{

bool Interaction::interact(Model::GameObject* i_object,
                           Model::GameObject* i_subject)
{
  if (!i_object || !i_subject)
    return true;

  if (!i_subject->isDoor())
    return true;

  const int interactMaxDist = Model::Tile::DEFAULT_TILE_SIZE + Model::Tile::DEFAULT_TILE_SIZE / 2;
  const int interactMaxDistSq = interactMaxDist * interactMaxDist;

  if ((i_object->getPosition() - i_subject->getPosition()).lengthSq() > interactMaxDistSq)
    return true;

  if (i_subject->isOpen())
  {
    i_subject->getStates().Remove(Model::State::Open);
    if (!i_subject->playAnimation("Close", 1))
      return false;
  }
  else
  {
    i_subject->getStates().Add(Model::State::Open);
    if (!i_subject->playAnimation("Open", 1))
      return false;
  }

  return true;
}

} // ns Controller
