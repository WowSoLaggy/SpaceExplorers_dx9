#pragma once

#ifndef INC_SCENEOBJECT_H
#define INC_SCENEOBJECT_H


class Scene;


class SceneObject : public virtual Doh3d::IDrawableTreeItem, public virtual Doh3d::IUpdatableTreeItem
{
public:

  virtual ~SceneObject() { }

protected:

  Scene* scene();
  const Scene* scene() const;

private:

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};


#endif // INC_SCENEOBJECT_H
