#pragma once

#include "SceneObject.h"


class Game;


class Scene : public SceneObject
{
public:

  Scene(Game& i_game);
  virtual ~Scene();

  Game& getGame() { return d_game; }
  const Game& getGame() const { return d_game; }

private:

  Game& d_game;

};
