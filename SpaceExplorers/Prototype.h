#pragma once


class Prototype final
{
public:

  const std::string& getName() const { return d_name; }
  void setName(const std::string& i_name) { d_name = i_name; }

  bool getTileBased() const { return d_tileBased; }
  void setTileBased(bool i_tileBased) { d_tileBased = i_tileBased; }

  const std::string& getTextureName() const { return d_textureName; }
  void setTextureName(const std::string& i_textureName) { d_textureName = i_textureName; }

  int getTi() const { return d_ti; }
  void setTi(int i_ti) { d_ti = i_ti; }

private:

  std::string d_name;

  bool d_tileBased;

  std::string d_textureName;
  int d_ti;

};
