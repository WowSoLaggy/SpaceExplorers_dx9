#pragma once


class Prototype final
{
public:

  const std::string& getName() const { return d_name; }
  void setName(const std::string& i_name) { d_name = i_name; }

  bool getTileBased() const { return d_tileBased; }
  void setTileBased(bool i_tileBased) { d_tileBased = i_tileBased; }

  bool getMovable() const { return d_movable; }
  void setMovable(bool i_movable) { d_movable = i_movable; }

  const std::string& getTextureName() const { return d_textureName; }
  void setTextureName(const std::string& i_textureName) { d_textureName = i_textureName; }

  int getTi() const { return d_ti; }
  void setTi(int i_ti) { d_ti = i_ti; }

  const Doh3d::Size2I& getSize() const { return d_size; }
  const Doh3d::Size2I& getSize2() const { return d_size2; }
  void setSize(const Doh3d::Size2I& i_size) { d_size = i_size; d_size2 = i_size / 2; }

private:

  std::string d_name;

  bool d_tileBased;
  bool d_movable;

  std::string d_textureName;
  int d_ti;

  Doh3d::Size2I d_size;
  Doh3d::Size2I d_size2;

};
