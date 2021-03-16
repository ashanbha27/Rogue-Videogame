#include <utility>
#include "Passage.hpp"
#include "Room.hpp"

Passage::Passage(
    Room* _room1,
    Room* _room2,
    std::vector<int> _x,
    std::vector<int> _y,
    bool _visible,
    ObjectDisplayGrid* _displayGrid) : Structure(
    _visible, _displayGrid), room1(_room1), room2(_room2), x(std::move(_x)), y(std::move(_y)) {}

void Passage::display()
{
  if (visible)
  {
    for (std::size_t i = 0; i < (x.size() - 1); i++)
    {
      int lower = y[i] < y[i + 1] ? y[i] : y[i + 1];
      int higher = y[i] > y[i + 1] ? y[i] : y[i + 1];
      for (int j = lower; j <= higher; j++)
      {
        if (room1->check(x[i], j) == 2 || room2->check(x[i], j) == 2)
        {
          displayGrid->addObjectToGameMap('+', x[i], j);
        }
        else
        {
          displayGrid->addObjectToGameMap('#', x[i], j);
        }
        path.emplace(x[i], j);
      }

      lower = x[i] < x[i + 1] ? x[i] : x[i + 1];
      higher = x[i] > x[i + 1] ? x[i] : x[i + 1];
      for (int j = lower; j <= higher; j++)
      {
        if (room1->check(j, y[i]) == 2 || room2->check(j, y[i]) == 2)
        {
          displayGrid->addObjectToGameMap('+', j, y[i]);
        }
        else
        {
          displayGrid->addObjectToGameMap('#', j, y[i]);
        }
        path.emplace(j, y[i]);
      }
    }
  }
}

int Passage::getPosX() const
{
  return x[0];
}

int Passage::getPosY() const
{
  return y[0];
}

int Passage::check(int _posX, int _posY) const
{
  if ((x[0] == _posX && y[0] == _posY) || (x.back() == _posX && y.back() == _posY))
  {
    return 2;
  }

  for (std::size_t i = 0; i < x.size(); i++)
  {
    if (path.count(std::make_tuple(_posX, _posY)))
    {
      return 1;
    }
  }

  return 0;
}
