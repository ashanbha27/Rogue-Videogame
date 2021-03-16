#pragma once

#include <string>
#include <map>
#include "Player.hpp"
#include "Monster.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "Passage.hpp"
#include "ObjectDisplayGrid.hpp"

class Dungeon
{
private:
  std::string name;
  ObjectDisplayGrid* displayGrid;
  int width, height;
  Player* player = nullptr;
  std::vector<Monster*> monsters;
  std::vector<Item*> items;
  std::map<int, Room*> rooms;
  std::vector<Passage*> passages;
  int score;
  Item* getItem(int x, int y);

  int hallucinateSteps;

public:
  Dungeon(std::string _name, ObjectDisplayGrid* _displayGrid);
  ~Dungeon();
  void display() const;
  void addMonster(Monster* monster);
  void addItem(Item* item);
  void addPlayer(Player* _player);
  Player* getPlayer();
  void movePlayer(int horizontalDistance, int verticalDistance);
  void attackCreature(Monster* monster);
  void addRoom(Room* room);
  Room* getRoom(int room);
  Room* getRoom(int x, int y);
  void addPassage(Passage* passage);
  void pickUpItem();
  void dropItem(int inventoryNumber);
  void clearInfoDisplay();
  void topDisplay();
  void infoDisplay();
  void runItemActions(int inventoryNumber);
  void takeOffArmor(int inventoryNumber);
  ObjectDisplayGrid* getDisplayGrid();
  void wearArmor(int inventoryNumber);
  void wieldSword(char inventoryNumber);
};
