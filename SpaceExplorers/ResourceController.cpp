#include "stdafx.h"
#include "ResourceController.h"


bool ResourceController::init()
{
  return Doh3d::ResourceMan::init();
}

bool ResourceController::dispose()
{
  return Doh3d::ResourceMan::dispose();
}
