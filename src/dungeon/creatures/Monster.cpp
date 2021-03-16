#include <utility>
#include <vector>
#include <random>
#include "Monster.hpp"
#include "Action.hpp"

Monster::Monster(
    std::string _name,
    int _posX,
    int _posY,
    char _type,
    int _hp,
    int _maxhit,
    bool _visible,
    Room* _room,
    ObjectDisplayGrid* _displayGrid,
    std::vector<Action> _actions)
    : Creature(std::move(_name), _posX, _posY, _type, _hp, _maxhit, _visible, _room, _displayGrid, std::move(_actions)),
      score(0) {}

void Monster::runAction(const Action& action, const std::vector<Position>& openPositions, std::vector<Item*>& items)
{
  Creature::runAction(action, openPositions, items);
  if (action.name == "YouWin")
  {
    score = action.intValue;
    if (!action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
}

int Monster::getScore() const
{
  return score;
}
