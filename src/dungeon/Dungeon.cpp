#include <utility>
#include <algorithm>
#include <random>
#include "Armor.hpp"
#include "Sword.hpp"
#include "Dungeon.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "Passage.hpp"

Dungeon::Dungeon(std::string _name, ObjectDisplayGrid* _displayGrid)
    : name(std::move(_name)),
      displayGrid(_displayGrid),
      width(displayGrid->getWidth()),
      height(displayGrid->getGameHeight()),
      score(0),
      hallucinateSteps(-1) {}

void Dungeon::topDisplay()
{
  displayGrid->writeTopMessage(0, 0, "HP: " + std::to_string(player->getHP()));
  displayGrid->writeTopMessage(0, 1, "Score: " + std::to_string(score));
}

void Dungeon::infoDisplay()
{
  displayGrid->writeBottomMessage(0, 2, "Info: ");
}

void Dungeon::display() const
{
  for (auto const& room : rooms)
  {
    room.second->display();
  }

  for (Passage* passage: passages)
  {
    passage->display();
  }

  for (Monster* creature : monsters)
  {
    creature->display();
  }

  for (Item* item : items)
  {
    item->display();
  }

  player->display();
}

void Dungeon::clearInfoDisplay()
{
  displayGrid->writeBottomMessage(6, 2, std::string(width - 6, ' '));
}

void Dungeon::addMonster(Monster* creature)
{
  monsters.push_back(creature);
}

void Dungeon::addPlayer(Player* _player)
{
  player = _player;
}

Player* Dungeon::getPlayer()
{
  return player;
}

void Dungeon::addItem(Item* item)
{
  items.push_back(item);
}

Item* Dungeon::getItem(int x, int y)
{
  for (auto it = items.rbegin(); it != items.rend(); ++it)
  {
    if ((*it)->check(x, y) != 0) return *it;
  }

  return nullptr;
}

void Dungeon::addRoom(Room* room)
{
  rooms[room->getRoomNumber()] = room;
}

Room* Dungeon::getRoom(int room)
{
  return rooms[room];
}

Room* Dungeon::getRoom(int x, int y)
{
  for (auto const& room : rooms)
  {
    if (room.second->check(x, y) != 0) return room.second;
  }

  return nullptr;
}

void Dungeon::addPassage(Passage* passage)
{
  passages.push_back(passage);
}
void Dungeon::attackCreature(Monster* monster)
{
  std::vector<Position> positions;
  for (auto const& room : rooms)
  {
    for (int x = 0; x < room.second->getWidth(); x++)
    {
      for (int y = 0; y < room.second->getHeight(); y++)
      {
        int posX = room.second->getPosX() + x;
        int posY = room.second->getPosY() + y;

        bool positionOccupied = room.second->check(posX, posY) != 1;
        for (Monster* m : monsters)
        {
          if (m->check(posX, posY))
          {
            positionOccupied = true;
            break;
          }
        }

        for (Item* i : items)
        {
          if (i->check(posX, posY))
          {
            positionOccupied = true;
            break;
          }
        }

        if (!positionOccupied) positions.emplace_back(posX, posY);
      }
    }
  }

  if (!player->isDead() && !monster->isDead())
  {
    std::random_device randomDevice;
    std::uniform_int_distribution<int> dist;
    dist = std::uniform_int_distribution<int>(0, player->getMaxHit());
    monster->increaseHp(-dist(randomDevice));
    if (player->getWieldedSword()) monster->increaseHp(-player->getWieldedSword()->getItemIntValue());
    monster->runActions("hit", positions, items);
    int previous = player->getHP();
    dist = std::uniform_int_distribution<int>(0, monster->getMaxHit());
    int damage = -dist(randomDevice);
    if (player->getWornArmor())
    {
      damage += player->getWornArmor()->getItemIntValue();
    }
    if (damage < 0) player->increaseHp(damage);
    player->updateDamage(previous);
    player->updateHP();
    player->runActions("hit", positions, items);
  }

  if (monster->isDead())
  {
    monster->runActions("death", positions, items);
    score += monster->getScore();
    displayGrid->writeTopMessage(7, 1, std::to_string(score));
    monsters.erase(std::remove(monsters.begin(), monsters.end(), monster), monsters.end());
  }

  if (player->isDead())
  {
    player->runActions("death", positions, items);
  }

  display();
}

void Dungeon::movePlayer(int horizontalDistance, int verticalDistance)
{
  if (player->isDead()) return;
  int oldPosX = player->getPosX();
  int oldPosY = player->getPosY();
  int newPosX = oldPosX + horizontalDistance;
  int newPosY = oldPosY - verticalDistance;

  for (Monster* c : monsters)
  {
    if (c->check(newPosX, newPosY))
    {
      if (!c->isDead())
      {
        attackCreature(c);
        return;
      }
      return;
    }
  }

  int newPassageSpaceType = 0;
  for (Passage* passage : passages)
  {
    newPassageSpaceType = passage->check(newPosX, newPosY);
    if (newPassageSpaceType != 0) break;
  }

  if (
      newPosX >= 0 &&
      newPosY >= 0 &&
      newPosX < width &&
      newPosY < height &&
      (player->getRoom()->check(newPosX, newPosY) == 1
       || newPassageSpaceType != 0))
  {
    if (!getItem(oldPosX, oldPosY)) displayGrid->restoreObjectFromGameMap(oldPosX, oldPosY);
    player->setPosition(newPosX, newPosY);
  }

  if (newPassageSpaceType == 2)
  {
    if (Room* newRoom = getRoom(newPosX, newPosY)) player->setRoom(newRoom);
  }

  if (hallucinateSteps-- >= 0)
  {
    std::random_device randomDevice;
    std::uniform_int_distribution<char> dist(0x20, 0x7E);
    player->setDisplayCharacter(dist(randomDevice));
    for (Monster* monster : monsters)
    {
      monster->setDisplayCharacter(dist(randomDevice));
    }
    for (Item* item : items)
    {
      item->setDisplayCharacter(dist(randomDevice));
    }
  }
  else
  {
    player->restoreDefaultCharacter();
    for (Monster* monster : monsters) monster->restoreDefaultCharacter();
    for (Item* item : items) item->restoreDefaultCharacter();
  }

  display();
}

void Dungeon::pickUpItem()
{
  if (Item* itemAtPlayerLocation = getItem(player->getPosX(), player->getPosY()))
  {
    if (player->getInventory()->addToInventory(itemAtPlayerLocation))
    {
      items.erase(std::remove(items.begin(), items.end(), itemAtPlayerLocation), items.end());
      display();
    }
  }
}

void Dungeon::dropItem(int inventoryNumber)
{
  if (Item* item = player->getInventory()->getFromInventory(inventoryNumber))
  {
    if (item == player->getWieldedSword()) player->removeWieldedSword();
    else if (item == player->getWornArmor()) player->removeWornArmor((Armor*) item);
    player->getInventory()->popFromInventory(inventoryNumber);
    item->setPosition(player->getPosX(), player->getPosY());
    items.push_back(item);
  }
}

void Dungeon::wieldSword(char inventoryNumber)
{
  Item* item = player->getInventory()->getFromInventory(inventoryNumber);
  if (item)
  {
    if (item->getType() == ITEMTYPE_SWORD) player->setWieldedSword((Sword*) item);
    else displayGrid->writeBottomMessage(6, 2, "Item is not sword and cannot be wielded!");
  }
}

void Dungeon::wearArmor(int inventoryNumber)
{
  Item* item = player->getInventory()->getFromInventory(inventoryNumber);
  if (item)
  {
    if (item->getType() == ITEMTYPE_ARMOR) player->setWornArmor((Armor*) item);
    else displayGrid->writeBottomMessage(6, 2, "Item is not armor and cannot be worn!");
  }
}

void Dungeon::takeOffArmor(int inventoryNumber)
{
  Item* item = player->getInventory()->getFromInventory(inventoryNumber);
  if (item)
  {
    if (item->getType() == ITEMTYPE_ARMOR) player->removeWornArmor((Armor*) item);
    else displayGrid->writeBottomMessage(6, 2, "Item is not armor and cannot be taken off!");
  }
}

void Dungeon::runItemActions(int inventoryNumber)
{
  if (!player->getInventory()->inventoryHidden())
  {
    Item* item = player->getInventory()->getFromInventory(inventoryNumber);
    if (item)
    {
      if (item->getType() == ITEMTYPE_SCROLL)
      {
        player->getInventory()->popFromInventory(inventoryNumber);
        for (const Action& action : item->getActions())
        {
          if (action.name == "Hallucinate")
          {
            hallucinateSteps = action.intValue;
            displayGrid->writeBottomMessage(6, 2, action.message);
            movePlayer(0, 0);
          }
          else if (action.name.find("Bless") != std::string::npos
                   || action.name.find("Curse") != std::string::npos)
          {
            if (action.charValue == 'a')
            {
              Armor* playerArmor = player->getWornArmor();
              if (playerArmor)
              {
                playerArmor->setItemIntValue(playerArmor->getItemIntValue() + action.intValue);
                if (action.intValue < 0)
                {
                  displayGrid->writeBottomMessage(
                      6,
                      2,
                      playerArmor->getName() +
                      " cursed! " +
                      std::to_string(action.intValue) +
                      " taken from its effectiveness.");
                }
                else
                {
                  displayGrid->writeBottomMessage(
                      6,
                      2,
                      playerArmor->getName() +
                      " blessed! " +
                      std::to_string(action.intValue) +
                      " added to its effectiveness.");
                }
              }
            }
            else if (action.charValue == 'w')
            {
              Sword* sword = player->getWieldedSword();
              if (sword)
              {
                sword->setItemIntValue(sword->getItemIntValue() + action.intValue);
                if (action.intValue < 0)
                {
                  displayGrid->writeBottomMessage(
                      6,
                      2,
                      sword->getName() +
                      " cursed! " +
                      std::to_string(action.intValue) +
                      " taken from its effectiveness.");
                }
                else
                {
                  displayGrid->writeBottomMessage(
                      6,
                      2,
                      sword->getName() +
                      " blessed! " +
                      std::to_string(action.intValue) +
                      " added to its effectiveness.");
                }
              }
            }
            if (!player->getInventory()->inventoryHidden()) player->getInventory()->displayInventory();
          }
        }
      }
    }
  }
}
ObjectDisplayGrid* Dungeon::getDisplayGrid()
{
  return displayGrid;
}

Dungeon::~Dungeon()
{
  delete displayGrid;
  delete player;

  for (Monster* creature : monsters)
  {
    delete creature;
  }

  for (Item* item : items)
  {
    delete item;
  }

  for (auto const& room : rooms)
  {
    delete room.second;
  }

  for (Passage* passage : passages)
  {
    delete passage;
  }
}
