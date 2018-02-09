#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <type_traits>
#include <string>
#include <utility>
#include <vector>

#include <treefrog/TGlobal>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QList>

#include "customerinfo.h"
#include "venderinfo.h"
#include "deviceinfo.h"
#include "serviceinfo.h"
#include "relationship.h"


class T_HELPER_EXPORT XmlHelper
{
  public:
    XmlHelper();
    QDomDocument getXml();
    template <class T> QDomDocument createXml(T info);
    template <class T> QDomDocument createXmlFromList(QList<T> info);
    template <class T> QDomDocument createInfoListXml(T info, QList<Relationship> relationList);
    QDomDocument createXmlForDist(QList<Relationship> relationList);
    QList<QVariantMap> parseXml(QString infoName, QString rawXml);
    //QDomDocument concatXml(QDomDocument firstXml, QDomDocument secondXml);

  private:
    QDomDocument doc;
    QDomElement body;

    QDomElement _setXmlInfo(CustomerInfo info);
    QDomElement _setXmlInfo(DeviceInfo info);
    QDomElement _setXmlInfo(VenderInfo info);
    QDomElement _setXmlInfo(ServiceInfo info);
    QDomElement _setXmlInfo(Relationship info);
    QDomElement _createXmlElement(QString elementName, QString elementText);
    QDomElement _setXmlRelation(Relationship info);
};

#endif // XMLHELPER_H
