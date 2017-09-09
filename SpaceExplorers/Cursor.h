#pragma once

#include "IGui.h"


namespace View
{

class Cursor : public IGui
{
public:

  Cursor();
  virtual ~Cursor() { }

  virtual bool loadAllTextures() override;

  bool setTexture(const std::string& pTextureName);


  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Doh3d::TextureId d_ti;

};

} // ns View
