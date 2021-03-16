#include <iostream>
#include <algorithm>
#include <string>
#include "Sword.hpp"
#include "Armor.hpp"
#include "Scroll.hpp"
#include "Dungeon.hpp"
#include "Structure.hpp"
#include "Room.hpp"
#include "Passage.hpp"
#include "XmlGameHandler.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Action.hpp"

int XmlGameHandler::caseInsensitiveMatch(std::string s1, std::string s2)
{
  std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
  std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
  if (s1 == s2)
  {
    return 1;
  }
  return 0;
}

std::string XmlGameHandler::xmlChToString(const XMLCh* xmlChName, int length = -1)
{
  char* chStarName = XMLString::transcode(xmlChName);
  if (length == -1)
  {
    std::string strName(chStarName);
    XMLString::release(&chStarName);
    return strName;
  }
  else
  {
    std::string strName(chStarName, 0, length);
    XMLString::release(&chStarName);
    return strName;
  }
}

const XMLCh* XmlGameHandler::getXMLChAttributeFromString(const Attributes& attributes, const char* strGet)
{
  XMLCh* xmlChGet = XMLString::transcode(strGet);
  const XMLCh* xmlChAttr = attributes.getValue(xmlChGet);
  XMLString::release((&xmlChGet));
  return xmlChAttr;
}

void XmlGameHandler::startElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname,
    const Attributes& attrs)
{
  char* qNameString = XMLString::transcode(qname);
  if (caseInsensitiveMatch(qNameString, "Dungeon"))
  {
    std::string name = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    int width = std::stoi(xmlChToString(getXMLChAttributeFromString(attrs, "width")));
    int topHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attrs, "topHeight")));
    int gameHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attrs, "gameHeight")));
    int bottomHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attrs, "bottomHeight")));

    displayGrid = new ObjectDisplayGrid(width, topHeight, gameHeight, bottomHeight);
    dungeon = new Dungeon(name, displayGrid);
  }
  else if (caseInsensitiveMatch(qNameString, "Room"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["room"] = xmlChToString(getXMLChAttributeFromString(attrs, "room"));
    dungeon->addRoom(new Room(std::stoi(elementMap["room"]), displayGrid));
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "Passage"))
  {
    insidePassageElement = true;
    std::map<std::string, std::string> elementMap;
    elementMap["room1"] = xmlChToString(getXMLChAttributeFromString(attrs, "room1"));
    elementMap["room2"] = xmlChToString(getXMLChAttributeFromString(attrs, "room2"));
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "Player"))
  {
    insidePlayerElement = true;
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["room"] = fields.back()["room"];
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "Monster"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["room"] = fields.back()["room"];
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "Scroll"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["room"] = fields.back()["room"];
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "Sword"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["room"] = fields.back()["room"];
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "Armor"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["room"] = fields.back()["room"];
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "CreatureAction"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["type"] = xmlChToString(getXMLChAttributeFromString(attrs, "type"));
    insideAction = true;
    fields.push_back(elementMap);
  }
  else if (caseInsensitiveMatch(qNameString, "ItemAction"))
  {
    std::map<std::string, std::string> elementMap;
    elementMap["name"] = xmlChToString(getXMLChAttributeFromString(attrs, "name"));
    elementMap["type"] = xmlChToString(getXMLChAttributeFromString(attrs, "type"));
    insideAction = true;
    fields.push_back(elementMap);
  }
  XMLString::release(&qNameString);
}

void XmlGameHandler::characters(const XMLCh* const ch, const XMLSize_t length)
{
  data = xmlChToString(ch, (int) length);
}

void XmlGameHandler::endElement(const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname)
{
  char* qNameString = XMLString::transcode(qname);
  if (caseInsensitiveMatch(qNameString, "posX"))
  {
    if (insidePassageElement)
    {
      x.push_back(std::stoi(data));
    }
    else
    {
      fields.back()["posX"] = data;
    }
  }
  else if (caseInsensitiveMatch(qNameString, "posY"))
  {
    if (insidePassageElement)
    {
      y.push_back(std::stoi(data));
    }
    else
    {
      fields.back()["posY"] = data;
    }
  }
  else if (caseInsensitiveMatch(qNameString, "width"))
  {
    fields.back()["width"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "height"))
  {
    fields.back()["height"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "type") && !insideAction)
  {
    fields.back()["type"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "visible"))
  {
    fields.back()["visible"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "hp"))
  {
    fields.back()["hp"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "maxhit"))
  {
    fields.back()["maxhit"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "hpMoves"))
  {
    fields.back()["hpMoves"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "actionMessage"))
  {
    fields.back()["actionMessage"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "actionIntValue"))
  {
    fields.back()["actionIntValue"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "actionCharValue"))
  {
    fields.back()["actionCharValue"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "ItemIntValue"))
  {
    fields.back()["ItemIntValue"] = data;
  }
  else if (caseInsensitiveMatch(qNameString, "Player"))
  {
    std::map<std::string, std::string>& elementMap = fields.back();
    std::map<std::string, std::string>& superElementMap = fields.end()[-2];
    int _posX = elementMap["posX"].empty() ? 0 : std::stoi(elementMap["posX"]);
    int _posY = elementMap["posY"].empty() ? 0 : std::stoi(elementMap["posY"]);
    int _roomPosX = superElementMap["posX"].empty() ? 0 : std::stoi(superElementMap["posX"]);
    int _roomPosY = superElementMap["posY"].empty() ? 0 : std::stoi(superElementMap["posY"]);
    int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
    int _hp = elementMap["hp"].empty() ? 0 : std::stoi(elementMap["hp"]);
    int _maxhit = elementMap["maxhit"].empty() ? 0 : std::stoi(elementMap["maxhit"]);
    int _hpMoves = elementMap["hpMoves"].empty() ? 0 : std::stoi(elementMap["hpMoves"]);
    Player* player =
        new Player(
            elementMap["name"],
            _posX + _roomPosX,
            _posY + _roomPosY,
            '@',
            _hp,
            _maxhit,
            _visible,
            dungeon->getRoom(std::stoi(elementMap["room"])),
            displayGrid,
            creatureActions,
            _hpMoves);
    for (Item* item : playerItems)
    {
      player->getInventory()->addToInventory(item);
    }
    dungeon->addPlayer(player);
    creatureActions.clear();
    fields.pop_back();
    insidePlayerElement = false;
  }
  else if (caseInsensitiveMatch(qNameString, "Monster"))
  {
    std::map<std::string, std::string>& elementMap = fields.back();
    std::map<std::string, std::string>& superElementMap = fields.end()[-2];
    int _posX = elementMap["posX"].empty() ? 0 : std::stoi(elementMap["posX"]);
    int _posY = elementMap["posY"].empty() ? 0 : std::stoi(elementMap["posY"]);
    int _roomPosX = superElementMap["posX"].empty() ? 0 : std::stoi(superElementMap["posX"]);
    int _roomPosY = superElementMap["posY"].empty() ? 0 : std::stoi(superElementMap["posY"]);
    int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
    int _hp = elementMap["hp"].empty() ? 0 : std::stoi(elementMap["hp"]);
    int _maxhit = elementMap["maxhit"].empty() ? 0 : std::stoi(elementMap["maxhit"]);
    dungeon->addMonster(
        new Monster(
            elementMap["name"],
            _posX + _roomPosX,
            _posY + _roomPosY,
            elementMap["type"][0],
            _hp,
            _maxhit,
            _visible,
            dungeon->getRoom(std::stoi(elementMap["room"])),
            displayGrid,
            creatureActions));
    creatureActions.clear();
    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "CreatureAction"))
  {
    insideAction = false;
    std::map<std::string, std::string>& elementMap = fields.back();
    Action action;
    action.name = elementMap["name"];
    action.type = elementMap["type"];
    action.message = elementMap["actionMessage"].empty() ? " " : elementMap["actionMessage"];
    if (!elementMap["actionIntValue"].empty()) action.intValue = std::stoi(elementMap["actionIntValue"]);
    if (!elementMap["actionCharValue"].empty()) action.charValue = elementMap["actionCharValue"][0];
    creatureActions.push_back(action);
    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "Scroll"))
  {
    if (!insidePlayerElement)
    {
      std::map<std::string, std::string>& elementMap = fields.back();
      int _posX = elementMap["posX"].empty() ? 0 : std::stoi(elementMap["posX"]);
      int _posY = elementMap["posY"].empty() ? 0 : std::stoi(elementMap["posY"]);
      int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
      dungeon->addItem(
          new Scroll(
              elementMap["name"],
              ITEMTYPE_SCROLL,
              '?',
              _posX,
              _posY,
              _visible,
              displayGrid,
              itemActions));
    }
    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "Sword"))
  {
    std::map<std::string, std::string>& elementMap = fields.back();
    int _posX = elementMap["posX"].empty() ? 0 : std::stoi(elementMap["posX"]);
    int _posY = elementMap["posY"].empty() ? 0 : std::stoi(elementMap["posY"]);
    int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
    int _itemIntValue = elementMap["ItemIntValue"].empty() ? 0 : std::stoi(elementMap["ItemIntValue"]);
    Sword* sword = new Sword(
        elementMap["name"],
        ITEMTYPE_SWORD,
        ')',
        _posX,
        _posY,
        _visible,
        _itemIntValue,
        displayGrid,
        itemActions);
    if (!insidePlayerElement) dungeon->addItem(sword);
    else playerItems.push_back(sword);
    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "Armor"))
  {
    std::map<std::string, std::string>& elementMap = fields.back();
    int _posX = elementMap["posX"].empty() ? 0 : std::stoi(elementMap["posX"]);
    int _posY = elementMap["posY"].empty() ? 0 : std::stoi(elementMap["posY"]);
    int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
    int _itemIntValue = elementMap["ItemIntValue"].empty() ? 0 : std::stoi(elementMap["ItemIntValue"]);
    Armor* armor =
        new Armor(
            elementMap["name"],
            ITEMTYPE_ARMOR,
            ']',
            _posX,
            _posY,
            _visible,
            _itemIntValue,
            displayGrid,
            itemActions);
    if (!insidePlayerElement) dungeon->addItem(armor);
    else playerItems.push_back(armor);
    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "ItemAction"))
  {
    insideAction = false;
    std::map<std::string, std::string>& elementMap = fields.back();
    Action action;
    action.name = elementMap["name"];
    action.type = elementMap["type"];
    action.message = elementMap["actionMessage"].empty() ? " " : elementMap["actionMessage"];
    if (!elementMap["actionIntValue"].empty()) action.intValue = std::stoi(elementMap["actionIntValue"]);
    if (!elementMap["actionCharValue"].empty()) action.charValue = elementMap["actionCharValue"][0];
    itemActions.push_back(action);
    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "Room"))
  {
    std::map<std::string, std::string>& elementMap = fields.back();
    int _posX = elementMap["posX"].empty() ? 0 : std::stoi(elementMap["posX"]);
    int _posY = elementMap["posY"].empty() ? 0 : std::stoi(elementMap["posY"]);
    int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
    int _height = elementMap["height"].empty() ? 0 : std::stoi(elementMap["height"]);
    int _width = elementMap["width"].empty() ? 0 : std::stoi(elementMap["width"]);
    int _room = elementMap["room"].empty() ? 0 : std::stoi(elementMap["room"]);

    dungeon->getRoom(_room)->setBoundary(_posX, _posY, _width, _height);
    dungeon->getRoom(_room)->setVisible(_visible);

    fields.pop_back();
  }
  else if (caseInsensitiveMatch(qNameString, "Passage"))
  {
    std::map<std::string, std::string>& elementMap = fields.back();
    int _room1 = elementMap["room1"].empty() ? 0 : std::stoi(elementMap["room1"]);
    int _visible = elementMap["visible"].empty() ? 1 : std::stoi(elementMap["visible"]);
    int _room2 = elementMap["room2"].empty() ? 0 : std::stoi(elementMap["room2"]);
    dungeon->addPassage(new Passage(dungeon->getRoom(_room1), dungeon->getRoom(_room2), x, y, _visible, displayGrid));
    insidePassageElement = false;
    x.clear();
    y.clear();
  }
  XMLString::release(&qNameString);
}

void XmlGameHandler::fatalError(const SAXParseException& exception)
{
  char* message = XMLString::transcode(exception.getMessage());
  std::cout << "Fatal Error: " << message
            << " at line: " << exception.getLineNumber()
            << std::endl;
  XMLString::release(&message);
}

Dungeon* XmlGameHandler::getDungeon()
{
  return dungeon;
}

XmlGameHandler::~XmlGameHandler()
{
  delete dungeon;
}
