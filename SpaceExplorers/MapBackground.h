#pragma once


namespace Model
{

class MapBackground
  : public Doh3d::IDrawable
  , public Doh3d::IUpdatable
{
public:

  virtual ~MapBackground();

  bool setTexture(const std::string& pTexture);

  virtual bool update(float i_dt) override;
  virtual bool draw(Doh3d::Sprite& i_sprite) const override;

private:

  Doh3d::TextureId d_ti;

  Doh3d::Vector2F d_scale;

  void updateScale();
};

} // ns Model
