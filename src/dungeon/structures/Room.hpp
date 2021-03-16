#pragma once

#include "Structure.hpp"

class Room : public Structure
{
private:
  int posX = 0, posY = 0;
  int height = 0, width = 0;
  int roomNumber;

public:
  Room(int _room, ObjectDisplayGrid* _displayGrid);
  virtual ~Room() = default;
  void display() override;
  void setBoundary(int _posX, int _posY, int _width, int _height);
  int check(int _posX, int _posY) const override;
  int getPosX() const override;
  int getPosY() const override;
  int getWidth() const;
  int getHeight() const;
  int getRoomNumber() const;
};
