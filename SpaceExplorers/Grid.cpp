#include "stdafx.h"
#include "Grid.h"


namespace View
{

Grid::Grid()
  : d_tiUl(0)
  , d_tiUr(0)
  , d_tiBl(0)
  , d_tiBr(0)
  , d_tiU(0)
  , d_tiR(0)
  , d_tiB(0)
  , d_tiL(0)
  , d_tiItem(0)
  , d_tiFrame(0)
{
  setGridSize({ 1, 1 });
}


bool Grid::update(float i_dt)
{
  return true;
}

bool Grid::draw(Doh3d::Sprite& i_sprite) const
{
  auto pos = getPosition();
  if (!drawPart(i_sprite, d_tiUl, pos)) return false;

  pos = getPosition() + Doh3d::Position2I(d_gridSize.x * 72 + 13, 0);
  if (!drawPart(i_sprite, d_tiUr, pos)) return false;

  pos = getPosition() + Doh3d::Position2I(0, d_gridSize.y * 72 + 13);
  if (!drawPart(i_sprite, d_tiBl, pos)) return false;

  pos = getPosition() + Doh3d::Position2I(d_gridSize.x * 72 + 13, d_gridSize.y * 72 + 13);
  if (!drawPart(i_sprite, d_tiBr, pos)) return false;


  for (int y = 0; y < d_gridSize.y; ++y)
  {
    pos = getPosition() + Doh3d::Position2I(0, y * 72 + 13);
    if (!drawPart(i_sprite, d_tiL, pos)) return false;

    pos = getPosition() + Doh3d::Position2I(d_gridSize.x * 72 + 13, y * 72 + 13);
    if (!drawPart(i_sprite, d_tiR, pos)) return false;
  }

  for (int x = 0; x < d_gridSize.x; ++x)
  {
    pos = getPosition() + Doh3d::Position2I(x * 72 + 13, 0);
    if (!drawPart(i_sprite, d_tiU, pos)) return false;

    pos = getPosition() + Doh3d::Position2I(x * 72 + 13, d_gridSize.y * 72 + 13);
    if (!drawPart(i_sprite, d_tiB, pos)) return false;
  }

  for (int y = 0; y < d_gridSize.y; ++y)
  {
    for (int x = 0; x < d_gridSize.x; ++x)
    {
      pos = getPosition() + Doh3d::Position2I(x * 72 + 13, y * 72 + 13);
      if (!drawPart(i_sprite, d_tiItem, pos)) return false;
    }
  }

  return true;
}

bool Grid::drawPart(Doh3d::Sprite& i_sprite, int d_ti, const Doh3d::Position2I& i_position) const
{
  if (!i_sprite.draw(Doh3d::ResourceMan::getTexture(d_ti).get(),
                     &Doh3d::ResourceMan::getTexture(d_ti).getFrame(0),
                     0, i_position, D3DCOLOR_ARGB(255, 255, 255, 255)))
  {
    return false;
  }

  return true;
}


void Grid::setGridSize(const Doh3d::Size2I& i_gridSize)
{
  d_gridSize = i_gridSize;
  
  setSize({ 13 * 2 + d_gridSize.x * 72, 13 * 2 + d_gridSize.y * 72 });
}


bool Grid::setTexture(const std::string& i_textureUl,
                      const std::string& i_textureUr,
                      const std::string& i_textureBl,
                      const std::string& i_textureBr,
                      const std::string& i_textureU,
                      const std::string& i_textureR,
                      const std::string& i_textureB,
                      const std::string& i_textureL,
                      const std::string& i_textureItem,
                      const std::string& i_textureFrame)
{
  if (!Doh3d::ResourceMan::getTi(i_textureUl, d_tiUl)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureUr, d_tiUr)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureBl, d_tiBl)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureBr, d_tiBr)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureU, d_tiU)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureR, d_tiR)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureB, d_tiB)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureL, d_tiL)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureItem, d_tiItem)) return false;
  if (!Doh3d::ResourceMan::getTi(i_textureFrame, d_tiFrame)) return false;

  return true;
}

bool Grid::loadAllTextures()
{
  if (!Doh3d::ResourceMan::getTexture(d_tiUl).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiUr).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiBl).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiBr).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiU).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiR).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiB).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiL).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiItem).load()) return false;
  if (!Doh3d::ResourceMan::getTexture(d_tiFrame).load()) return false;

  return true;
}

} // ns View
