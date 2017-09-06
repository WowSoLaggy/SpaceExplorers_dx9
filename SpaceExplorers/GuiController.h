#pragma once


namespace SpaceExplorers
{
namespace Controller
{

class Scene;


class GuiController
{
public:

  static bool createLoadingGui(Scene& pScene);
  static bool deleteLoadingGui(Scene& pScene);

  static bool createMainMenu(Scene& pScene);
  static bool deleteMainMenu(Scene& pScene);

  static bool createIngameMenu(Scene& pScene);
  static bool deleteIngameMenu(Scene& pScene);

};

} // ns Controller
} // ns SpaceExplorers
