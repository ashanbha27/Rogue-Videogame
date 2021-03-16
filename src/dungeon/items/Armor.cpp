#include <utility>
#include "Armor.hpp"

Armor::Armor(
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

int Armor::getItemIntValue() const
{
  return itemIntValue;
}

void Armor::setItemIntValue(int _itemIntValue)
{
  itemIntValue = _itemIntValue;
}

ItemType Armor::getType()
{
  return ITEMTYPE_ARMOR;
}