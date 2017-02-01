#include "stdafx.h"
#include "RenderDevice.h"


bool RenderDevice::check()
{
  return Doh3d::RenderMan::isCreated();
}

bool RenderDevice::recreate(const std::string& pWindowCaption)
{
  if (!Doh3d::RenderMan::recreate(getRenderPars(), pWindowCaption))
    return false;

  return true;
}


Doh3d::RenderPars RenderDevice::getRenderPars()
{
  Doh3d::RenderPars renderPars;

  // TODO: create option chooser via C#? Or in-game?
  // I think it will be good to load not-fullscreen with resolution = desktop resolution by default
  // and change settings only in the in-game menu

  renderPars.resolutionWidth() = 1920;
  renderPars.resolutionHeight() = 1080;
  renderPars.windowed() = true;

  renderPars.fullScreenRefreshRate() = 60;
  renderPars.hasBorder() = false;

  return renderPars;
}
