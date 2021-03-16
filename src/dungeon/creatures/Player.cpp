#include <utility>
#include "Player.hpp"

Player::Player(
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
    int _hpMoves)
    : Creature(
    std::move(_name),
    _posX,
    _posY,
    _type,
    _hp,
    _maxhit,
    _visible,
    _room,
    _displayGrid,
    std::move(_actions)),
      hpMoves(_hpMoves),
      moves(0),
      inventory(new Inventory(displayGrid)),
      wornArmor(nullptr),
      wieldedSword(nullptr) {}

Inventory* Player::getInventory()
{
  return inventory;
}

void Player::updateHP()
{
  displayGrid->writeTopMessage(4, 0, std::string(3, ' '));
  displayGrid->writeTopMessage(4, 0, std::to_string(hp));
}

void Player::updateDamage(int previous)
{
  int damageTaken = previous - hp;
  std::string message = "Damage Taken: " + std::to_string(damageTaken);
  displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
  displayGrid->writeBottomMessage(6, 2, message);
}

void Player::updateMoves()
{
  moves++;
  if (!isDead() && moves >= hpMoves && moves % hpMoves == 0)
  {
    increaseHp(1);
    updateHP();
  }
}

Armor* Player::getWornArmor() const
{
  return wornArmor;
}

void Player::setWornArmor(Armor* _armor)
{
  if (!wornArmor)
  {
    wornArmor = _armor;
    if (wornArmor) displayGrid->writeBottomMessage(6, 2, "Wearing " + wornArmor->getName() + "!");
    inventory->armorWorn = wornArmor;
    if (!inventory->inventoryHidden()) inventory->displayInventory();
  }
  else
  {
    displayGrid->writeBottomMessage(
        6,
        2,
        "Already wearing " +
        wornArmor->getName() +
        "! Must drop before another armor is worn!");
  }
}

void Player::removeWornArmor(Armor* armor)
{
  if (wornArmor == armor)
  {
    displayGrid->writeBottomMessage(6, 2, "Take off " + wornArmor->getName() + "!");
    wornArmor = nullptr;
    inventory->armorWorn = nullptr;
    if (!inventory->inventoryHidden()) inventory->displayInventory();
  }
  else
  {
    displayGrid->writeBottomMessage(6, 2, "Not wearing " + armor->getName() + "!");
  }
}

Sword* Player::getWieldedSword() const
{
  return wieldedSword;
}

void Player::setWieldedSword(Sword* _sword)
{
  if (!wieldedSword)
  {
    wieldedSword = _sword;
    if (wieldedSword) displayGrid->writeBottomMessage(6, 2, "Wielding " + wieldedSword->getName() + "!");
    inventory->wieldedSword = wieldedSword;
    if (!inventory->inventoryHidden()) inventory->displayInventory();
  }
  else
  {
    displayGrid->writeBottomMessage(
        6,
        2,
        "Already wielding " +
        wieldedSword->getName() +
        "! Must drop before another sword is wielded!");
  }
}

void Player::removeWieldedSword()
{
  displayGrid->writeBottomMessage(6, 2, "Put away " + wieldedSword->getName() + "!");
  wieldedSword = nullptr;
  inventory->wieldedSword = nullptr;
  if (!inventory->inventoryHidden()) inventory->displayInventory();
}

void Player::runAction(const Action& action, const std::vector<Position>& openPositions, std::vector<Item*>& items)
{
  Creature::runAction(action, openPositions, items);
  if (action.name == "DropPack")
  {
    if (inventory->getSize() > 0)
    {
      Item* item = inventory->popFromInventory(1);
      item->setPosition(posX, posY);
      items.push_back(item);
      if (!action.message.empty())
      {
        displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
        displayGrid->writeBottomMessage(6, 2, action.message);
      }
    }
  }
  else if (action.name == "EmptyPack")
  {
    bool droppedItem = false;
    for (int i = 1; i <= inventory->getSize(); i++)
    {
      Item* item = inventory->popFromInventory(i);
      item->setPosition(posX, posY);
      items.insert(items.begin(), item);
      droppedItem = true;
    }
    if (droppedItem && !action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
  else if (action.name == "EndGame")
  {
    if (!action.message.empty())
    {
      displayGrid->writeBottomMessage(6, 2, std::string(displayGrid->getWidth() - 6, ' '));
      displayGrid->writeBottomMessage(6, 2, action.message);
    }
  }
}

Player::~Player()
{
  delete inventory;
}
