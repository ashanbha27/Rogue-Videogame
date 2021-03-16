#pragma once

#include "ObjectDisplayGrid.hpp"

class Displayable
{
protected:
  Displayable(int _posX, int _posY, bool _visible, ObjectDisplayGrid* _displayGrid);
  int posX, posY;
  bool visible;
  ObjectDisplayGrid* displayGrid;

public:
  virtual void display() = 0;
  virtual void setPosition(int _posX, int _posY);
  virtual int getPosX() const;
  virtual int getPosY() const;
  virtual void setVisible(bool _visible);
  virtual int check(int _posX, int _posY) const;
};
