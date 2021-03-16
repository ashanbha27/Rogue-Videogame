#pragma once

#include <string>
#include <vector>
#include "Action.hpp"
#include "Displayable.hpp"

typedef enum ItemType
{
  ITEMTYPE_SCROLL,
  ITEMTYPE_SWORD,
  ITEMTYPE_ARMOR,
  ITEMTYPE_INVALID = -1
} ItemType;

class Item : public Displayable
{
protected:
  std::string name;
  ItemType type;
  char displayCharacter;
  char defaultDisplayCharacter;
  std::vector<Action> actions;

public:
  Item(
      std::string _name,
      ItemType _type,
      char _displayCharacter,
      int _posX,
      int _posY,
      bool _visible,
      ObjectDisplayGrid* _displayGrid,
      std::vector<Action> _actions);
  virtual ~Item() = default;
  std::string getName() const;
  void display() override;
  char getDisplayCharacter() const;
  void setDisplayCharacter(char _displayCharacter);
  void restoreDefaultCharacter();
  std::vector<Action> getActions() const;
  virtual ItemType getType();
};
