#pragma once

#include <vector>
#include "Displayable.hpp"
#include "Room.hpp"
#include "Action.hpp"
#include "Item.hpp"

class Creature : public Displayable
{
protected:
  std::string name;
  char displayCharacter;
  char defaultDisplayCharacter;
  int hp, maxhit;
  Room* room;
  std::vector<Action> actions;
  virtual void runAction(const Action& action, const std::vector<Position>& openPositions, std::vector<Item*>& items);

public:
  Creature(
      std::string _name,
      int _posX,
      int _posY,
      char _displayCharacter,
      int _hp,
      int _maxhit,
      bool _visible,
      Room* _room,
      ObjectDisplayGrid* _displayGrid,
      std::vector<Action> _actions);
  virtual ~Creature() = default;
  void display() override;
  Room* getRoom();
  void setRoom(Room* _room);
  int getHP() const;
  int getMaxHit() const;
  void increaseHp(int change);
  virtual bool isDead();
  void runActions(
      const std::string& actionType,
      const std::vector<Position>& openPositions,
      std::vector<Item*>& items);
  void setDisplayCharacter(char _displayCharacter);
  void restoreDefaultCharacter();
};
