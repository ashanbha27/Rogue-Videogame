#pragma once

#include <string>
#include "Displayable.hpp"

class Structure : public Displayable
{
public:
  Structure(bool _visible, ObjectDisplayGrid* _displayGrid);
  int getPosX() const override = 0;
  int getPosY() const override = 0;
  int check(int _posX, int _posY) const override = 0;
};
