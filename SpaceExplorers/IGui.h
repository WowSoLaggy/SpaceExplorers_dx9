#pragma once

#ifndef INC_IGUI_H
#define INC_IGUI_H


class IGui : public Doh3d::IPositioned, public Doh3d::ITextured, public Doh3d::ISized
{
public:

  virtual ~IGui() { }

};


#endif // INC_IGUI_H
