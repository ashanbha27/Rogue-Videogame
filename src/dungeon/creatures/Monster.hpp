#pragma once

#include <vector>
#include "Creature.hpp"
#include "Action.hpp"
#include "Item.hpp"

class Monster : public Creature
{
private:
  int score;
  void runAction(const Action& action, const std::vector<Position>& openPositions, std::vector<Item*>& items) override;

public:
  Monster(
      std::string _name,
      int _posX,
      int _posY,
      char _type,
      int _hp,
      int _maxhit,
      bool _visible,
      Room* _room,
      ObjectDisplayGrid* displayGrid,
      std::vector<Action> _actions);
  int getScore() const;
};
