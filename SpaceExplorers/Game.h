#pragma once

#include "Scene.h"


namespace SpaceExplorers
{
namespace Controller
{

enum class GameState
{
  Unknown,
  MainMenu,
  InGame,
  EscapeMenu,
};


class Game : public Doh3d::IInputHandler
{
public:

  static Game* create(bool& pRunMainLoop, const std::string& pTextureDir, const std::string& pFontDir);

public:

  const Scene& getScene() const { return d_scene; }
  Scene& getScene() { return d_scene; }


  bool stop();

  bool startNewGame();
  bool showInGameMenu();


  Doh3d::Controller* createNewController();
  Doh3d::Controller* getController(Doh3d::ControllerId i_controllerId);
  bool removeController(Doh3d::ControllerId i_controllerId);


  // Input handlers

  virtual bool onMouseMove(bool& pHandled) override;
  virtual bool onMouseDown(Doh3d::MouseButton pButton, bool& pHandled) override;
  virtual bool onMouseUp(Doh3d::MouseButton pButton, bool& pHandled) override;

  virtual bool onKeyPressed(Doh3d::Key pKey) override;
  virtual bool onKeyDown(Doh3d::Key pKey) override;
  virtual bool onKeyUp(Doh3d::Key pKey) override;

private:

  Game();

  Scene d_scene;
  std::vector<Doh3d::Controller*> d_controllers;

  GameState d_gameState;

  bool createMap();
  bool createBindCamera();
  bool createBindController();
  void bindControllerActions(Doh3d::Controller& i_controller);

};

} // ns Controller
} // ns SpaceExplorers
