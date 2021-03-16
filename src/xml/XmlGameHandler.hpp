#pragma once

#include <memory>
#include <map>
#include <vector>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include "ObjectDisplayGrid.hpp"
#include "Dungeon.hpp"

using namespace xercesc;

class XmlGameHandler : public DefaultHandler
{
private:
  ObjectDisplayGrid* displayGrid;
  Dungeon* dungeon;
  std::string data;
  std::vector<std::map<std::string, std::string>> fields;
  std::vector<Action> creatureActions;
  std::vector<Action> itemActions;
  std::vector<Item*> playerItems;
  bool insidePassageElement = false;
  bool insidePlayerElement = false;
  bool insideAction = false;
  std::vector<int> x;
  std::vector<int> y;

  static const XMLCh* getXMLChAttributeFromString(const Attributes& attributes, const char* strGet);
  static std::string xmlChToString(const XMLCh* xmlChName, int length);
  static int caseInsensitiveMatch(std::string s1, std::string s2);

public:
  ~XmlGameHandler() override;
  void startElement(
      const XMLCh* uri,
      const XMLCh* localname,
      const XMLCh* qname,
      const Attributes& attrs) override;
  void characters(const XMLCh* ch, XMLSize_t length) override;
  void endElement(
      const XMLCh* uri,
      const XMLCh* localname,
      const XMLCh* qname) override;
  void fatalError(const SAXParseException&) override;

  Dungeon* getDungeon();
};
