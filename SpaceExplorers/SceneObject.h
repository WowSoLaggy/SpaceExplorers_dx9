#pragma once

#ifndef INC_SCENEOBJECT_H
#define INC_SCENEOBJECT_H


class Scene;


class SceneObject : public virtual Doh3d::IDrawableTreeItem, public virtual Doh3d::IUpdatableTreeItem
{
public:

  virtual ~SceneObject() { }

  std::string& name() { return d_name; }
  const std::string& name() const { return d_name; }

  SceneObject* findChild(const std::string& pChildName) const;

protected:

  Scene* scene();
  const Scene* scene() const;

private:

  std::string d_name;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};


#endif // INC_SCENEOBJECT_H