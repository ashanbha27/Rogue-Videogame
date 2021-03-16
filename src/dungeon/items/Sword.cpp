#include <utility>
#include "Sword.hpp"

Sword::Sword(
    std::string _name,
    ItemType _type,
    char _displayCharacter,
    int _posX,
    int _posY,
    bool _visible,
    int _itemIntValue,
    ObjectDisplayGrid* _displayGrid,
    std::vector<Action> _actions) :
    Item(
        std::move(_name),
        _type,
        _displayCharacter,
        _posX,
        _posY,
        _visible,
        _displayGrid,
        std::move(_actions)),
    itemIntValue(_itemIntValue) {}

int Sword::getItemIntValue() const
{
  return itemIntValue;
}

void Sword::setItemIntValue(int _itemIntValue)
{
  itemIntValue = _itemIntValue;
}

ItemType Sword::getType()
{
  return ITEMTYPE_SWORD;
}