#pragma once

#include "Prototype.h"


namespace Model
{

class PrototypeCollection
{
public:

  static bool initAllPrototypes();
  static bool loadAllPrototypes();

  static const Prototype* find(const std::string& i_name);

private:

  PrototypeCollection() { } //< Hide ctor

  static std::vector<Prototype*> d_prototypes;

};

} // ns Model
