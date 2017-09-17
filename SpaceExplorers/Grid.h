#pragma once

#include "IGui.h"


namespace View
{

class Grid : public IGui
{
public:

  Grid();
  virtual ~Grid() { }

  virtual bool loadAllTextures() override;

  bool setTexture(const std::string& i_textureUl,
                  const std::string& i_textureUr,
                  const std::string& i_textureBl,
                  const std::string& i_textureBr,
                  const std::string& i_textureU,
                  const std::string& i_textureR,
                  const std::string& i_textureB,
                  const std::string& i_textureL,
                  const std::string& i_textureItem,
                  const std::string& i_textureFrame);

  const Doh3d::Size2I& getGridSize() const { return d_gridSize; }
  void setGridSize(const Doh3d::Size2I& i_gridSize);

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Doh3d::TextureId d_tiUl;
  Doh3d::TextureId d_tiUr;
  Doh3d::TextureId d_tiBl;
  Doh3d::TextureId d_tiBr;
  Doh3d::TextureId d_tiU;
  Doh3d::TextureId d_tiR;
  Doh3d::TextureId d_tiB;
  Doh3d::TextureId d_tiL;
  Doh3d::TextureId d_tiItem;
  Doh3d::TextureId d_tiFrame;

  Doh3d::Size2I d_gridSize;


  bool drawPart(Doh3d::Sprite& i_sprite, int d_ti, const Doh3d::Position2I& i_position) const;

};

} // ns View
