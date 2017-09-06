#pragma once

#include "IGui.h"
#include "ButtonStates.h"


namespace SpaceExplorers
{
namespace View
{

class Button : public IGui
{
public:

  Button();
  virtual ~Button() { }

  virtual bool loadAllTextures() override;

  bool setTexture(
    const std::string& pTextureNameNormal,
    const std::string& pTextureNamePressed,
    const std::string& pTextureNameSelected,
    const std::string& pTextureNameDisabled);


  void setOnClickEvent(std::function<bool()> pEvent) { d_onClickEvent = pEvent; }
  bool click();


  virtual void setSize(const Doh3d::Size2I& pSize) override;


  bool setText(const std::string& pText);
  bool setFont(const std::string& pFontName);
  bool setTextAlign(Doh3d::TextAlign pTextAlign);


  // Input handlers

  virtual bool onMouseMove(bool& pHandled) override;
  virtual bool onMouseDown(Doh3d::MouseButton pButton, bool& pHandled) override;
  virtual bool onMouseUp(Doh3d::MouseButton pButton, bool& pHandled) override;

  virtual bool onKeyPressed(Doh3d::Key pKey) override;
  virtual bool onKeyDown(Doh3d::Key pKey) override;
  virtual bool onKeyUp(Doh3d::Key pKey) override;

private:

  Doh3d::TextureId d_tiNormal;
  Doh3d::TextureId d_tiPressed;
  Doh3d::TextureId d_tiSelected;
  Doh3d::TextureId d_tiDisabled;

  ButtonState d_state;

  Doh3d::TextContainer d_textContainer;

  std::function<bool()> d_onClickEvent;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};

} // ns View
} // ns SpaceExplorers
