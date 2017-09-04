#pragma once

#include "Prototype.h"


class PrototypeCollection
{
public:

  static void loadAllPrototypes();

  static const Prototype* find(const std::string& i_name);

private:

  PrototypeCollection() { } //< Hide ctor

  static std::vector<Prototype> d_prototypes;

};
