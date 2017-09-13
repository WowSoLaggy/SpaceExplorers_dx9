#pragma once


namespace Model
{
class Map;
class GameObject;
} // ns Model

namespace Controller
{

class Game;


class MapController
  : public Doh3d::IUpdatable
  , public Doh3d::IDrawable
{
public:

  MapController(Game& i_game);

  Model::Map* getMap() { return d_map; }
  const Model::Map* getMap() const { return d_map; }

  bool createMap(int i_width, int i_height);
  bool deleteMap();

  Model::GameObject* hitTest() const;

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Game& d_game;

  Model::Map* d_map;
};

} // ns Controller
