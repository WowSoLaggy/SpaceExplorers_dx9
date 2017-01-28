#pragma once

#ifndef INC_SCENE_H
#define INC_SCENE_H


#include "Object.h"


class Scene : public Object
{
public:

  bool& lol() { return d_lol; }
  const bool& lol() const { return d_lol; }

private:

  bool d_lol;

};


#endif // INC_SCENE_H
