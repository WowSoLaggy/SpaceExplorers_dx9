#pragma once

#ifndef INC_GAMEINITIALIZER_H
#define INC_GAMEINITIALIZER_H


#include "SceneObject.h"


class GameInitializer : public SceneObject
{
public:

  GameInitializer(const std::string& pTextureDir, const std::string& pFontDir);

private:

  enum class State
  {
    NotInited,
    GameLoading,
    GameLoadOk,
    GameLoadFailed,
    ReadyForMainMenu,
  };

  const std::string d_textureDir;
  const std::string d_fontDir;

  State d_state;

  bool initGameLoadMenu();
  bool checkGameIsLoaded();

  bool initResourceManager();
  bool createLoadingGui();
  bool startGameLoadingThread();
  void loadGame();
  bool createMainMenu();
  bool deleteLoadingGui();
  bool deleteSelf();

  virtual bool updateSelf(float pDt) override;

};


#endif // INC_GAMEINITIALIZER_H
