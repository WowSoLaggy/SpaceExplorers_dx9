#pragma once

#include "SceneObject.h"


namespace SpaceExplorers
{
namespace Controller
{

class GameController : public SceneObject
{
public:

  GameController(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);

  void stopGame();

private:

  enum class State
  {
    NotInited,
    GameLoading,
    GameLoadOk,
    GameLoadFailed,
    ReadyForMainMenu,
    InGame,
    GameStopping,
    GameStopped,
  };

  const std::string d_textureDir;
  const std::string d_fontDir;

  bool& d_runMainLoop;
  State d_state;

  bool initGameLoadMenu();
  bool checkGameIsLoaded();

  bool initResourceManager();
  bool createLoadingGui();
  bool startGameLoadingThread();
  void loadGame();
  bool deleteLoadingGui();
  bool createMainMenu();

  bool unloadGame();

  virtual bool updateSelf(float pDt) override;

};

} // ns Controller
} // ns SpaceExplorers
