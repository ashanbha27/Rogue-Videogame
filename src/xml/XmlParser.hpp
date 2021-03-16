#pragma once

#include <string>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

using namespace xercesc;

class XmlParser
{
private:
  DefaultHandler& handler;
  SAX2XMLReader* parser;

public:
  XmlParser(DefaultHandler& handler);
  ~XmlParser();
  void parse(const std::string& xmlFile);
};
