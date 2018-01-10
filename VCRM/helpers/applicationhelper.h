#ifndef APPLICATIONHELPER_H
#define APPLICATIONHELPER_H

#include <type_traits>
#include <string>
#include <utility>
#include <vector>

#include <treefrog/TGlobal>
#include <QtXml/QDomDocument>
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


class T_HELPER_EXPORT ApplicationHelper
{
  public:
    template <class T> QDomDocument createXml(T info);
    template <class T> QDomDocument createXmlFromList(QList<T> info);

  private:
    QDomElement _setXmlInfo(CustomerInfo info);
    QDomElement _setXmlInfo(DeviceInfo info);
    QDomElement _setXmlInfo(VenderInfo info);
    QDomElement _setXmlInfo(ServiceInfo info);
    QDomElement _setXmlInfo(Relationship info);
    QDomElement _createXmlElement(QString elementName, QString elementText);
};

#endif // APPLICATIONHELPER_H
