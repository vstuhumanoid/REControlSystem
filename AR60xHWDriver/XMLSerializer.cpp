#include "XMLSerializer.h"

XMLSerializer::XMLSerializer()
{

}

void XMLSerializer::Serialize(std::string fileName)
{
    QDomDocument document("AR60xConfig");
    QDomElement  domElement = document.createElement("AR60xConfig");
    document.appendChild(domElement);

    QDomElement domJointElement;

    domJointElement.setAttribute("number", 1);
    domJointElement.setAttribute("channel", 1);
    domJointElement.setAttribute("name", QString::fromStdString("name"));
    domJointElement.setAttribute("isReverce", QString::number(true));

    domElement.appendChild(domJointElement);

    qDebug() << QString::number(true) << endl;

    QFile file(QString::fromStdString( fileName ));
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << document.toString();
        file.close();
    }
}
