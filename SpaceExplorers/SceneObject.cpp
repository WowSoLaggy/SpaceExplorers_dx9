#include "stdafx.h"
#include "SceneObject.h"

#include "Scene.h"


bool SceneObject::updateSelf(float pDt)
{
  return true;
}

bool SceneObject::drawSelf(Doh3d::Sprite& pSprite) const
{
  return true;
}


Scene* SceneObject::scene()
{
  SceneObject* pSceneObject = this;
  
  while (true)
  {
    if (Scene* pScene = dynamic_cast<Scene*>(pSceneObject))
      return pScene;
    if (pSceneObject = dynamic_cast<SceneObject*>(pSceneObject->parent()))
      continue;
    else
      return nullptr;
  }
}

const Scene* SceneObject::scene() const
{
  const SceneObject* pSceneObject = this;

  while (true)
  {
    if (const Scene* pScene = dynamic_cast<const Scene*>(pSceneObject))
      return pScene;
    if (pSceneObject = dynamic_cast<const SceneObject*>(pSceneObject->parent()))
      continue;
    else
      return nullptr;
  }
}


SceneObject* SceneObject::findChild(const std::string& pChildName, int pDepth /* = -1 */) const
{
  if (pDepth == 0)
    return nullptr;
  --pDepth;

  for (auto* pChild : d_children)
  {
    if (auto* pSceneObject = dynamic_cast<SceneObject*>(pChild))
    {
      if (pSceneObject->name() == pChildName)
        return pSceneObject;

      if (pSceneObject = pSceneObject->findChild(pChildName, pDepth))
        return pSceneObject;
    }
  }

  return nullptr;
}
