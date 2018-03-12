#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include "Libs/TinyXML2/tinyxml2.h"
#include "RobotDescription/AR60xDescription.h"
#include <string>

using namespace tinyxml2;

class XMLSerializer
{
public:
    XMLSerializer();

    bool serialize(std::string fileName, AR60xDescription * desc);
    bool deserialize(std::string fileName);
};

#endif // XMLSERIALIZER_H
