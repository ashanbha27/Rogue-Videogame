#pragma once

#include "Item.hpp"

class Sword : public Item
{
private:
  int itemIntValue;

public:
  Sword(
      std::string _name,
      ItemType _type,
      char _displayCharacter,
      int _posX,
      int _posY,
      bool _visible,
      int _itemIntValue,
      ObjectDisplayGrid* _displayGrid,
      std::vector<Action> _actions);
  ItemType getType() override;
  int getItemIntValue() const;
  void setItemIntValue(int _itemIntValue);
};
