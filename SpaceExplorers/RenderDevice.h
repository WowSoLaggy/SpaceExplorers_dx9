#pragma once

#ifndef INC_RENDERDEVICE_H
#define INC_RENDERDEVICE_H


class RenderDevice
{
public:

  bool init();
  bool dispose();

  bool check();
  bool recreate(const std::string& pWindowCaption);

private:

  Doh3d::RenderPars getRenderPars();

};


#endif // INC_RENDERDEVICE_H
