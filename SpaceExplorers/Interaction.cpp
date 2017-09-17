#include "stdafx.h"
#include "Interaction.h"

#include "Map.h"


namespace Controller
{

bool Interaction::interact(Model::GameObject* i_object,
                           Model::GameObject* i_subject,
                           Model::GameObject* i_tool)
{
  if (!i_object || !i_subject)
    return true;

  if (auto* pCharacter = dynamic_cast<Model::Character*>(i_object))
  {
    if (i_subject->isDoor() && !i_tool)
      return openDoor(*pCharacter, *i_subject);

    if (i_subject->isPickable() && !i_tool)
      return pickUpObject(*pCharacter, *i_subject);
  }

  // Such an objects can't interact
  return true;
}


bool Interaction::openDoor(Model::Character& i_object,
                           Model::GameObject& i_subject)
{
  if ((i_object.getPosition() - i_subject.getPosition()).lengthSq() > INTERACTMAXDISTSQ)
    return true;

  if (i_subject.isOpen())
  {
    // Check if there is nothing that can prevent the door to close
    if (const auto* pSubjectTile = i_subject.getMap().getTileUnderPosition(i_subject.getPosition()))
    {
      for (const auto* pGameObject : i_subject.getMap().getObjects())
      {
        if (pSubjectTile == i_subject.getMap().getTileUnderPosition(pGameObject->getPosition()))
        {
          // Something is placed on this tile
          return true;
        }
      }
    }

    i_subject.getStates().Remove(Model::State::Open);
    if (!i_subject.playAnimation("Close", 1))
      return false;
  }
  else
  {
    i_subject.getStates().Add(Model::State::Open);
    if (!i_subject.playAnimation("Open", 1))
      return false;
  }

  return true;
}

bool Interaction::pickUpObject(Model::Character& i_object,
                               Model::GameObject& i_subject)
{
  auto activeHand = i_object.getActiveHand();
  if (activeHand == Model::Hand::None)
    return true;

  if (i_object.getObjectInHand(activeHand))
  {
    // Hand is busy
    return true;
  }

  i_object.getMap().removeGameObject(&i_subject);
  i_object.setObjectInHand(activeHand, &i_subject);

  return true;
}

} // ns Controller
