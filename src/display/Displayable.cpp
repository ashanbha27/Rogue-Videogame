#include "Displayable.hpp"

Displayable::Displayable(int _posX, int _posY, bool _visible, ObjectDisplayGrid* _displayGrid)
    : posX(_posX), posY(_posY), visible(_visible), displayGrid(_displayGrid) {}

void Displayable::setPosition(int _posX, int _posY)
{
  posX = _posX;
  posY = _posY;
}

int Displayable::getPosX() const
{
  return posX;
}

int Displayable::getPosY() const
{
  return posY;
}

void Displayable::setVisible(bool _visible)
{
  visible = _visible;
}

int Displayable::check(int _posX, int _posY) const
{
  return _posX == posX && _posY == posY;
}
