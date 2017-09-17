#include "stdafx.h"
#include "Character.h"


namespace Model
{

Character::Character(Map& i_map, const Prototype& i_prototype)
  : GameObject(i_map, i_prototype)
  , d_activeHand(Hand::None)
{
  d_itemsInHands = {
    { Hand::Right, nullptr},
    { Hand::Left, nullptr } };
}


GameObject* Character::removeObjectFromHand(Hand i_hand)
{
  GameObject* object = d_itemsInHands[i_hand];
  d_itemsInHands[i_hand] = nullptr;
  return object;
}

} // ns Model
