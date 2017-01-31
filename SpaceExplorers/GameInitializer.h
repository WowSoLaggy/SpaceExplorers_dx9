#pragma once

#ifndef INC_GAMEINITIALIZER_H
#define INC_GAMEINITIALIZER_H


#include "SceneObject.h"


class GameInitializer : public SceneObject
{
public:

  GameInitializer(const std::string& pTextureDir, const std::string& pFontDir);

  virtual bool updateSelf(float pDt) override;

private:

  enum class State
  {
    NotInited,
    GameLoading,
    GameLoaded,
  };

  const std::string d_textureDir;
  const std::string d_fontDir;

  State d_state;

  bool initGameLoadMenu();
  bool checkGameIsLoaded();

  bool initResourceManager();
  bool createLoadingGui();

};


#endif // INC_GAMEINITIALIZER_H
