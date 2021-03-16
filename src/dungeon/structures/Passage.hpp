#pragma once

#include <vector>
#include <set>
#include <tuple>
#include "Structure.hpp"
#include "Room.hpp"

class Passage : public Structure
{
private:
  Room* room1;
  Room* room2;
  std::vector<int> x;
  std::vector<int> y;
  std::set<std::tuple<int, int>> path;

public:
  Passage(
      Room* _room1,
      Room* _room2,
      std::vector<int> _x,
      std::vector<int> _y,
      bool _visible,
      ObjectDisplayGrid* _displayGrid);
  virtual ~Passage() = default;
  void display() override;
  int getPosX() const override;
  int getPosY() const override;
  int check(int _posX, int _posY) const override;
};
