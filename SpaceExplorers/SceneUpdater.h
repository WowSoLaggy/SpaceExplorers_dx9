#pragma once

#ifndef INC_SCENEUPDATER_H
#define INC_SCENEUPDATER_H


class SceneUpdater : public Doh3d::IVisiter
{
public:

  bool update();

  virtual bool visit(Doh3d::ITreeItem& pTreeItem) override;

};


#endif // INC_SCENEUPDATER_H
