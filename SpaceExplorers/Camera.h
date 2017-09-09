#pragma once


namespace Model
{
class GameObject;
} // ns Model


namespace Controller
{

class Camera
  : public Doh3d::IPositioned2I
  , public Doh3d::IUpdatable
{
public:

  void bindToObject(const Model::GameObject* i_object);
  void unbindFromObject();


  virtual bool update(float i_dt) override;

private:

  const Model::GameObject* d_bindedObject;
};

} // ns Controller
