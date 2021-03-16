#include <algorithm>
#include "Inventory.hpp"

Inventory::Inventory(ObjectDisplayGrid* _displayGrid)
    : displayGrid(_displayGrid),
      maxNumberOfItems(9),
      wieldedSword(nullptr),
      armorWorn(nullptr)
{
  displayGrid->writeBottomMessage(0, 0, "Pack: ");
}

void Inventory::displayInventory()
{
  int position = 6;
  displayGrid->writeBottomMessage(position, 0, std::string(displayGrid->getWidth() - position, ' '));
  for (int i = 0; i < maxNumberOfItems && i < items.size(); i++)
  {
    std::string message = std::to_string(i + 1) + ". " + items[i]->getName();
    if (items[i]->getType() == ITEMTYPE_SWORD)
    {
      int value = (reinterpret_cast<Sword*>(items[i]))->getItemIntValue();
      if (value < 0) message += " (-" + std::to_string(value) + ")";
      else message += " (+" + std::to_string(value) + ")";
      if (wieldedSword == ((Sword*) items[i])) message += " (w)";
    }
    else if (items[i]->getType() == ITEMTYPE_ARMOR)
    {
      int value = (reinterpret_cast<Armor*>(items[i]))->getItemIntValue();
      if (value < 0) message += " (-" + std::to_string(value) + ")";
      else message += " (+" + std::to_string(value) + ")";
      if (armorWorn == ((Armor*) items[i])) message += " (a)";
    }
    displayGrid->writeBottomMessage(position, 0, message);
    position += message.size() + 1;
  }
}

bool Inventory::addToInventory(Item* item)
{
  if (items.size() < maxNumberOfItems)
  {
    items.push_back(item);
    openInventory();
    return true;
  }

  return false;
}

Item* Inventory::getFromInventory(int inventoryNumber)
{
  Item* item = nullptr;
  int index = inventoryNumber - 1;
  if (index < items.size())
  {
    item = items.at(index);
  }
  else
  {
    displayGrid->writeBottomMessage(6, 2, "Item " + std::to_string(inventoryNumber) + " does not exist");
  }

  return item;
}

void Inventory::removeFromInventory(Item* item)
{
  if (item) items.erase(std::remove(items.begin(), items.end(), item), items.end());
  if (!isInventoryHidden) displayInventory();
}

Item* Inventory::popFromInventory(int inventoryNumber)
{
  Item* item = getFromInventory(inventoryNumber);
  removeFromInventory(item);
  displayInventory();
  return item;
}

void Inventory::openInventory()
{
  displayInventory();
  isInventoryHidden = false;
}

void Inventory::closeInventory()
{
  displayGrid->writeBottomMessage(6, 0, std::string(displayGrid->getWidth() - 6, ' '));
  isInventoryHidden = true;
}

bool Inventory::inventoryHidden() const
{
  return isInventoryHidden;
}

int Inventory::getSize()
{
  return items.size();
}

Inventory::~Inventory()
{
  for (Item* item : items)
  {
    delete item;
  }
}
