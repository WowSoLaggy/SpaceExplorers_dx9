#pragma once

#include "InputController.h"
#include "GuiController.h"
#include "MapController.h"


namespace Controller
{

class Scene;

enum class GameState
{
  NotInited,
  Loading,
  LoadOk,
  LoadFailed,
  ReadyForMainMenu,
  Stopping,
  Stopped,

  MainMenu,
  InGame,
  EscapeMenu,
};


class Game
  : public Doh3d::IUpdatable
  , public Doh3d::IDrawable
{

public:

  Game(Scene& i_scene, bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);


  const Scene& getScene() const { return d_scene; }
  Scene& getScene() { return d_scene; }

  GameState getGameState() const { return d_gameState; }

  InputController& getInputController() { return d_inputController; }
  GuiController& getGuiController() { return d_guiController; }


  bool stop();

  bool startNewGame();
  bool stopGame();
  bool showEscapeMenu();
  bool returnFromEscapeMenu();

  virtual bool draw(Doh3d::Sprite& i_sprite) const override;
  virtual bool update(float i_dt) override;


private:

  Scene& d_scene;

  GameState d_gameState;

  const std::string d_textureDir;
  const std::string d_fontDir;

  bool& d_runMainLoop;

  InputController d_inputController;
  GuiController d_guiController;
  MapController d_mapController;


  bool updateControllers(float i_dt);


  // Game_loading

  bool initGameLoadMenu();
  bool checkGameIsLoaded();

  bool initResourceManager();
  bool createLoadingGui();
  bool startGameLoadingThread();
  void loadGame();
  bool deleteLoadingGui();
  bool createMainMenu();

  bool unloadGame();

  bool createBindCamera();
  bool deleteCamera();
  bool createBindController();

};

} // ns Controller
