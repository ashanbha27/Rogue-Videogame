#include <utility>
#include <vector>
#include "Item.hpp"


Item::Item(
    std::string _name,
    ItemType _type,
    char _displayCharacter,
    int _posX,
    int _posY,
    bool _visible,
    ObjectDisplayGrid* _displayGrid,
    std::vector<Action> _actions)
    : Displayable(_posX, _posY, _visible, _displayGrid),
      name(std::move(_name)),
      type(_type),
      displayCharacter(_displayCharacter),
      defaultDisplayCharacter(displayCharacter),
      actions(std::move(_actions)) {}

std::string Item::getName() const
{
  return name;
}

ItemType Item::getType()
{
  return ITEMTYPE_INVALID;
}

char Item::getDisplayCharacter() const
{
  return displayCharacter;
}

void Item::setDisplayCharacter(char _displayCharacter)
{
  displayCharacter = _displayCharacter;
}

void Item::restoreDefaultCharacter()
{
  displayCharacter = defaultDisplayCharacter;
}

std::vector<Action> Item::getActions() const
{
  return actions;
}

void Item::display()
{
  if (visible) displayGrid->addObjectToGameDisplay(displayCharacter, posX, posY);
}
