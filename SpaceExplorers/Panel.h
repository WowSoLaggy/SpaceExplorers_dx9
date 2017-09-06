#pragma once

#include "SceneObject.h"
#include "IGui.h"


namespace SpaceExplorers
{
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

private:

  Doh3d::TextureId d_ti;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};

} // ns View
} // ns SpaceExplorers
