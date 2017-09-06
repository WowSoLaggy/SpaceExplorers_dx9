#include "stdafx.h"
#include "ResourceController.h"


namespace SpaceExplorers
{
namespace Engine
{

bool ResourceController::init()
{
  return Doh3d::ResourceMan::init();
}

bool ResourceController::dispose()
{
  return Doh3d::ResourceMan::dispose();
}

} // ns Engine
} // ns SpaceExplorers
