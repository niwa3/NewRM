#ifndef APPLICATIONHELPER_H
#define APPLICATIONHELPER_H

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

#include "../helpers/applicationhelper.h"
#include "../helpers/curlhelper.h"
#include "../helpers/xmlhelper.h"

//Declare and define of anonymitymethod
struct ANONYMITYMETHOD{
  static const int NONE = 0;
  static const int NOISE = 1;
  static const int FLAT = 2;
};


class T_HELPER_EXPORT ApplicationHelper
{
  public:
    QList<QVariantMap> createRelationMap(ServiceInfo service, QList<DeviceInfo> deviceList);
  private:
};

#endif // APPLICATIONHELPER_H
