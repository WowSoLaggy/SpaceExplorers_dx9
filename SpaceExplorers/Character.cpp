#include "stdafx.h"
#include "Character.h"


namespace Model
{

Character::Character(const Map& i_map, const Prototype& i_prototype)
  : GameObject(i_map, i_prototype)
  , d_activeHand(ActiveHand::None)
{
}

} // ns Model
