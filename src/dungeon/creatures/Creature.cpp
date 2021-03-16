#include <utility>
#include <random>
#include "Creature.hpp"
#include "Room.hpp"

Creature::Creature(
    std::string _name,
    int _posX,
    int _posY,
    char _displayCharacter,
    int _hp,
    int _maxhit,
    bool _visible,
    Room* _room,
    ObjectDisplayGrid* _displayGrid,
    std::vector<Action> _actions)
    : Displayable(_posX, _posY, _visible, _displayGrid),
      name(std::move(_name)),
      displayCharacter(_displayCharacter),
      defaultDisplayCharacter(displayCharacter),
      hp(_hp),
      maxhit(_maxhit),
      room(_room),
      actions(std::move(_actions)) {}

void Creature::display()
{
  if (visible) displayGrid->addObjectToGameDisplay(displayCharacter, posX, posY);
}

void Creature::setDisplayCharacter(char _displayCharacter)
{
  displayCharacter = _displayCharacter;
}

void Creature::restoreDefaultCharacter()
{
  displayCharacter = defaultDisplayCharacter;
}

void Creature::setRoom(Room* _room)
{
  room = _room;
}

Room* Creature::getRoom()
{
  return room;
}

int Creature::getHP() const
{
  return hp;
}

int Creature::getMaxHit() const
{
  return maxhit;
}

void Creature::increaseHp(int change)
{
  hp += change;
  if (hp < 0) hp = 0;
}

bool Creature::isDead()
{
  return hp == 0;
}

void Creature::runAction(const Action& action, const std::vector<Position>& openPositions, std::vector<Item*>& items)
{
  if (action.name == "ChangeDisplayedType")
  {
    displayCharacter = action.charValue;
    if (!action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
  else if (action.name == "Teleport")
  {
    std::random_device randomDevice;
    int randomPosition = std::uniform_int_distribution<int>(0, openPositions.size())(randomDevice);
    displayGrid->restoreObjectFromGameMap(posX, posY);
    setPosition(std::get<0>(openPositions[randomPosition]), std::get<1>(openPositions[randomPosition]));
    display();
    if (!action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
  else if (action.name == "Remove")
  {
    displayGrid->restoreObjectFromGameMap(posX, posY);
    if (!action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
  else if (action.name == "UpdateDisplay")
  {
    display();
    if (!action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
}

void Creature::runActions(
    const std::string& actionType,
    const std::vector<Position>& openPositions,
    std::vector<Item*>& items)
{
  for (const Action& action : actions)
  {
    if (action.type == actionType)
    {
      runAction(action, openPositions, items);
    }
  }
}
