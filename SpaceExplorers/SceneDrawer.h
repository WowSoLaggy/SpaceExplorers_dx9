#pragma once

#ifndef INC_SCENEDRAWER_H
#define INC_SCENEDRAWER_H


class SceneDrawer : public Doh3d::IVisiter
{
public:

  bool draw();

  virtual bool visit(Doh3d::ITreeItem& pTreeItem) override;
  virtual bool visit(const Doh3d::ITreeItem& pTreeItem) const override;

};


#endif // INC_SCENEDRAWER_H
