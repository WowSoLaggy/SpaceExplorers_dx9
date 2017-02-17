#pragma once

#ifndef INC_CURSOR_H
#define INC_CURSOR_H


#include "SceneObject.h"
#include "IGui.h"


class Cursor : public virtual SceneObject, public virtual IGui
{
public:

  Cursor();
  virtual ~Cursor() { }

  virtual bool loadAllTextures() override;

  bool setTexture(const std::string& pTextureName);


  // Input handlers

  virtual bool onMouseMove() override { return false; }
  virtual bool onMouseDown(Doh3d::MouseButton pButton) override { return false; }
  virtual bool onMouseUp(Doh3d::MouseButton pButton) override { return false; }

  virtual bool onKeyPressed(Doh3d::Key pKey) override { return false; }
  virtual bool onKeyDown(Doh3d::Key pKey) override { return false; }
  virtual bool onKeyUp(Doh3d::Key pKey) override { return false; }

private:

  Doh3d::TextureId d_ti;

  virtual bool updateSelf(float pDt) override;
  virtual bool drawSelf(Doh3d::Sprite& pSprite) const override;

};


#endif // INC_CURSOR_H
