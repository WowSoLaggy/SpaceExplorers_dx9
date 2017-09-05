#pragma once


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
