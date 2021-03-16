#pragma once

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

using namespace xercesc;

class XmlPrintHandler : public DefaultHandler
{
private:
  static int case_insensitive_match(std::string s1, std::string s2);
  static std::string trim(std::string& str, const std::string& chars);
  static std::string xmlChToString(const XMLCh* xmlChName, int length);
  static const XMLCh* getXMLChAttributeFromString(const Attributes& attributes, const char* strGet);

public:
  void startElement(
      const XMLCh* uri,
      const XMLCh* localname,
      const XMLCh* qname,
      const Attributes& attrs
  ) override;
  void characters(const XMLCh* ch, XMLSize_t length) override;
  void fatalError(const SAXParseException&) override;
};
