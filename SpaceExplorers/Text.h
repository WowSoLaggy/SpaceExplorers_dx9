#pragma once

#include "SceneObject.h"
#include "IGui.h"


namespace SpaceExplorers
{
namespace View
{

class Text : public IGui
{
public:

  Text();
  virtual ~Text() { }

  virtual bool loadAllTextures() override;

  bool setText(const std::string& pText);
  bool setFont(const std::string& pFontName);
  bool setTextAlign(Doh3d::TextAlign pTextAlign);

private:

  Doh3d::TextContainer d_textContainer;

  void updateSize();

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};

} // ns View
} // ns SpaceExplorers
