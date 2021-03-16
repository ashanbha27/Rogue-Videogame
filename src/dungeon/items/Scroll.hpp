#pragma once

#include <vector>
#include "Item.hpp"

class Scroll : public Item
{
public:
  Scroll(
      std::string _name,
      ItemType _item,
      char _displayCharacter,
      int _posX,
      int _posY,
      bool _visible,
      ObjectDisplayGrid* _displayGrid,
      std::vector<Action> _actions);
  ItemType getType() override;
};
