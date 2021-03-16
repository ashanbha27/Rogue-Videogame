#pragma once

#include <vector>
#include "Armor.hpp"
#include "Sword.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include "Inventory.hpp"
#include "ObjectDisplayGrid.hpp"
#include "Action.hpp"

class Player : public Creature
{
private:
  int hpMoves;
  int moves;
  Inventory* inventory;
  Armor* wornArmor;
  Sword* wieldedSword;
  void runAction(const Action& action, const std::vector<Position>& openPositions, std::vector<Item*>& items) override;

public:
  Player(
      std::string _name,
      int _posX,
      int _posY,
      char _type,
      int _hp,
      int _maxhit,
      bool _visible,
      Room* _room,
      ObjectDisplayGrid* _displayGrid,
      std::vector<Action> _actions,
      int _hpMoves);
  ~Player() override;
  Inventory* getInventory();
  void updateHP();
  void updateDamage(int previous);
  void updateMoves();
  Armor* getWornArmor() const;
  Sword* getWieldedSword() const;
  void setWornArmor(Armor* _armor);
  void setWieldedSword(Sword* _sword);
  void removeWornArmor(Armor* armor);
  void removeWieldedSword();
};
