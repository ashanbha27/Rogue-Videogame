#include <utility>
#include <random>
#include "Scroll.hpp"

Scroll::Scroll(
    std::string _name,
    ItemType _item,
    char _displayCharacter,
    int _posX,
    int _posY,
    bool _visible,
    ObjectDisplayGrid* _displayGrid,
    std::vector<Action> _actions) :
    Item(
        std::move(_name),
        _item,
        _displayCharacter,
        _posX,
        _posY,
        _visible,
        _displayGrid,
        std::move(_actions)) {}

ItemType Scroll::getType()
{
  return ITEMTYPE_SCROLL;
}
