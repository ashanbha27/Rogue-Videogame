#pragma once

#include <vector>
#include <KeyboardListener.hpp>
#include "Item.hpp"
#include "Sword.hpp"
#include "Armor.hpp"

class Inventory
{
private:
  ObjectDisplayGrid* displayGrid;
  bool isInventoryHidden = true;
  std::vector<Item*> items;
  int maxNumberOfItems;

public:
  Inventory(ObjectDisplayGrid* _displayGrid);
  ~Inventory();
  bool addToInventory(Item* item);
  Item* popFromInventory(int inventoryNumber);
  void displayInventory();
  void openInventory();
  void closeInventory();
  bool inventoryHidden() const;
  int getSize();
  Item* getFromInventory(int inventoryNumber);
  void removeFromInventory(Item* item);
  Sword* wieldedSword;
  Armor* armorWorn;
};
