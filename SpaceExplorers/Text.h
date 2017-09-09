#pragma once

#include "IGui.h"


namespace View
{

class Text
  : public IGui
{
public:

  Text();
  virtual ~Text() { }

  virtual bool loadAllTextures() override;

  bool setText(const std::string& pText);
  bool setFont(const std::string& pFontName);
  bool setTextAlign(Doh3d::TextAlign pTextAlign);


  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Doh3d::TextContainer d_textContainer;

  void updateSize();

};

} // ns View
