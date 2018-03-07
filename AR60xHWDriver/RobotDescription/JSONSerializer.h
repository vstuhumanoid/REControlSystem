#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

//#include <Libs/JSON/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "AR60xDescription.h"

class JSONSerializer
{
    AR60xDescription * desc;
public:
    JSONSerializer();

    void setDesc(AR60xDescription *desc);
    bool serialize(std::string fileName);
    bool deserialize(std::string fileName);
};

#endif // JSONSERIALIZER_H
