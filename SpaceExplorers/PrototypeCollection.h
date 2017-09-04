#pragma once

#include "Prototype.h"


class PrototypeCollection
{
public:

  void loadAllPrototypes();

  const Prototype* find(const std::string& i_name);

private:

  std::vector<Prototype> d_prototypes;

};
