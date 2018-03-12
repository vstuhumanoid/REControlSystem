#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include <string>

class XMLSerializer
{
public:
    XMLSerializer();

    void Serialize(std::string fileName);
};

#endif // XMLSERIALIZER_H
