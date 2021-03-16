#include "Room.hpp"

Room::Room(int _room, ObjectDisplayGrid* _displayGrid) : Structure(true, _displayGrid), roomNumber(_room) {}

void Room::display()
{
  if (visible)
  {
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
        {
          displayGrid->addObjectToGameMap('X', posX + j, posY + i);
        }
        else
        {
          displayGrid->addObjectToGameMap('.', posX + j, posY + i);
        }
      }
    }
  }
}

void Room::setBoundary(int _posX, int _posY, int _width, int _height)
{
  posX = _posX;
  posY = _posY;
  width = _width;
  height = _height;
}

int Room::check(int _posX, int _posY) const
{
  if (((_posX == posX || _posX == posX + width - 1) && (_posY >= posY && _posY < posY + height)) ||
      ((_posY == posY || _posY == posY + height - 1) && (_posX >= posX && _posX < posX + width)))
  {
    return 2;
  }
  else if ((_posX > posX && _posX < posX + width) && (_posY > posY && _posY < posY + height))
  {
    return 1;
  }
  else
  {
    return 0;
  }

}

int Room::getPosX() const
{
  return posX;
}

int Room::getPosY() const
{
  return posY;
}

int Room::getWidth() const
{
  return width;
}

int Room::getHeight() const
{
  return height;
}

int Room::getRoomNumber() const
{
  return roomNumber;
}
