#include <iostream>
#include <algorithm>
#include "XmlPrintHandler.hpp"

int XmlPrintHandler::case_insensitive_match(std::string s1, std::string s2)
{
  std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
  std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
  if (s1 == s2)
  {
    return 1;
  }
  return 0;
}

std::string XmlPrintHandler::trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
  str.erase(0, str.find_first_not_of(chars));
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}

std::string XmlPrintHandler::xmlChToString(const XMLCh* xmlChName, int length = -1)
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

const XMLCh* XmlPrintHandler::getXMLChAttributeFromString(const Attributes& attributes, const char* strGet)
{
  XMLCh* xmlChGet = XMLString::transcode(strGet);
  const XMLCh* xmlChAttr = attributes.getValue(xmlChGet);
  XMLString::release((&xmlChGet));
  return xmlChAttr;
}

void XmlPrintHandler::startElement(
    const XMLCh* const uri,
    const XMLCh* const localname,
    const XMLCh* const qname,
    const Attributes& attrs)
{
  char* qNameStr = XMLString::transcode(qname);
  std::cout << qNameStr << ": ";
  if (case_insensitive_match(qNameStr, "Dungeon"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "width=" << xmlChToString(getXMLChAttributeFromString(attrs, "width")) << " ";
    std::cout << "topHeight=" << xmlChToString(getXMLChAttributeFromString(attrs, "topHeight")) << " ";
    std::cout << "gameHeight=" << xmlChToString(getXMLChAttributeFromString(attrs, "gameHeight")) << " ";
    std::cout << "bottomHeight=" << xmlChToString(getXMLChAttributeFromString(attrs, "bottomHeight")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Room"))
  {
    std::cout << "room=" << xmlChToString(getXMLChAttributeFromString(attrs, "room")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Passage"))
  {
    std::cout << "room1=" << xmlChToString(getXMLChAttributeFromString(attrs, "room1")) << " ";
    std::cout << "room2=" << xmlChToString(getXMLChAttributeFromString(attrs, "room2")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Player"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "room=" << xmlChToString(getXMLChAttributeFromString(attrs, "room")) << " ";
    std::cout << "serial=" << xmlChToString(getXMLChAttributeFromString(attrs, "serial")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Monster"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "room=" << xmlChToString(getXMLChAttributeFromString(attrs, "room")) << " ";
    std::cout << "serial=" << xmlChToString(getXMLChAttributeFromString(attrs, "serial")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Scroll"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "room=" << xmlChToString(getXMLChAttributeFromString(attrs, "room")) << " ";
    std::cout << "serial=" << xmlChToString(getXMLChAttributeFromString(attrs, "serial")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Sword"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "room=" << xmlChToString(getXMLChAttributeFromString(attrs, "room")) << " ";
    std::cout << "serial=" << xmlChToString(getXMLChAttributeFromString(attrs, "serial")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "Armor"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "room=" << xmlChToString(getXMLChAttributeFromString(attrs, "room")) << " ";
    std::cout << "serial=" << xmlChToString(getXMLChAttributeFromString(attrs, "serial")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "CreatureAction"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "type=" << xmlChToString(getXMLChAttributeFromString(attrs, "type")) << " ";
  }
  else if (case_insensitive_match(qNameStr, "ItemAction"))
  {
    std::cout << "name=" << xmlChToString(getXMLChAttributeFromString(attrs, "name")) << " ";
    std::cout << "type=" << xmlChToString(getXMLChAttributeFromString(attrs, "type")) << " ";
  }
}

void XmlPrintHandler::characters(const XMLCh* const ch, const XMLSize_t length)
{
  std::string data = xmlChToString(ch, (int) length);
  std::cout << trim(data, " ");
}

void XmlPrintHandler::fatalError(const SAXParseException& exception)
{
  char* message = XMLString::transcode(exception.getMessage());
  std::cout << "Fatal Error: " << message
            << " at line: " << exception.getLineNumber()
            << std::endl;
  XMLString::release(&message);
}
