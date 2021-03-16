#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <iostream>
#include "XmlParser.hpp"

XmlParser::XmlParser(DefaultHandler& _handler) : handler(_handler)
{
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& e)
  {
    char* message = XMLString::transcode(e.getMessage());
    std::cout << "Error during initialization! :\n";
    std::cout << "Exception message is: \n"
              << message << "\n";
    XMLString::release(&message);
    exit(-1);
  }

  parser = XMLReaderFactory::createXMLReader();
  parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional
  parser->setContentHandler(&handler);
  parser->setErrorHandler(&handler);
}

void XmlParser::parse(const std::string& xmlFile)
{
  std::string xmlFilePath = "xmlfiles/" + xmlFile;

  try
  {
    parser->parse(xmlFilePath.c_str());
  }
  catch (const XMLException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    std::cout << "Exception message is: \n"
              << message << "\n";
    XMLString::release(&message);
    exit(-1);
  }
  catch (const SAXParseException& toCatch)
  {
    char* message = XMLString::transcode(toCatch.getMessage());
    std::cout << "Exception message is: \n"
              << message << "\n";
    XMLString::release(&message);
    exit(-1);
  }
  catch (...)
  {
    std::cout << "Unexpected Exception \n";
    exit(-1);
  }
}

XmlParser::~XmlParser()
{
  delete parser;

  XMLPlatformUtils::Terminate();
}
