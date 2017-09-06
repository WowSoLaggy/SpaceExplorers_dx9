#pragma once


namespace Controller
{

class SceneObject
{
public:

  virtual ~SceneObject() { }

  const std::string& getName() const { return d_name; }
  void setName(const std::string& pNewName) { d_name = pNewName; }

private:

  std::string d_name;

};

} // ns Controller
