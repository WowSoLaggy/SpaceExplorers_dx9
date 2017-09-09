#pragma once

#include "IGui.h"


namespace View
{

class Panel : public IGui
{
public:

  Panel();
  virtual ~Panel() { }

  // TODO: this method is used only once (when loading the game)
  // All this should be in some other way - there is absolutely no need to override it
  // in every Gui class (or not?)
  virtual bool loadAllTextures() override;

  bool setTexture(const std::string& pTextureName);


  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Doh3d::TextureId d_ti;

};

} // ns View
