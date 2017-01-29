#pragma once

#ifndef INC_GAMEINITIALIZER_H
#define INC_GAMEINITIALIZER_H


#include "SceneObject.h"


class GameInitializer : public SceneObject
{
public:

  GameInitializer();

  virtual bool updateSelf(float pDt) override;

private:

  enum class State
  {
    NotInited,
    GameLoading,
  };

  State d_state;

  bool initGameLoadMenu();
  bool checkGameIsLoaded();

};


#endif // INC_GAMEINITIALIZER_H
