#pragma once


namespace Controller
{

class Camera;
class Game;


class Scene
{
public:

  virtual ~Scene() { }

  Camera* getCamera() { return d_camera; }
  const Camera* getCamera() const { return d_camera; }

  void setCamera(Camera* i_camera) { d_camera = i_camera; }
  void resetCamera() { d_camera = nullptr; }

  bool updateCamera(float i_dt);

  bool draw(const Game& i_game);

  bool onRenderDeviceRecreate();

private:

  Doh3d::Sprite d_sprite;
  Camera* d_camera;

};

} // ns Controller
