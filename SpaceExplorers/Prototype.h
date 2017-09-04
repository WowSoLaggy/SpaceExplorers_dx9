#pragma once


class Prototype
{
public:

  const std::string& getName() { return d_name; }
  void setName(const std::string& i_name) { d_name = i_name; }

  bool getTileBased() { return d_tileBased; }
  void setTileBased(bool i_tileBased) { d_tileBased = i_tileBased; }

private:

  std::string d_name;

  bool d_tileBased;

};
