#pragma once

#ifndef INC_GUICONTROLLER_H
#define INC_GUICONTROLLER_H


class Scene;


class GuiController
{
public:

  static bool createLoadingGui(Scene& pScene);
  static bool deleteLoadingGui(Scene& pScene);

  static bool createMainMenu(Scene& pScene);

};


#endif // INC_GUICONTROLLER_H
