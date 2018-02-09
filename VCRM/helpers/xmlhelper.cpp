#include "xmlhelper.h"


XmlHelper::XmlHelper() : body(doc.createElement("body"))
{
  doc.appendChild(body);
}


QDomDocument XmlHelper::getXml()
{
  return doc;
}

/**
 * createXml(T)
 * T = CustomerInfo, DeviceInfo, VenderInfo, ServiceInfo, Relationship
 * return QDomDocument
 */
template <typename T>
QDomDocument XmlHelper::createXml(T info)
{
  body.appendChild(this->_setXmlInfo(info));

  return doc;
}

template QDomDocument XmlHelper::createXml<CustomerInfo>(CustomerInfo);
template QDomDocument XmlHelper::createXml<DeviceInfo>(DeviceInfo);
template QDomDocument XmlHelper::createXml<VenderInfo>(VenderInfo);
template QDomDocument XmlHelper::createXml<ServiceInfo>(ServiceInfo);
template QDomDocument XmlHelper::createXml<Relationship>(Relationship);


template <typename T>
QDomDocument XmlHelper::createXmlFromList(QList<T> infoList)
{
  for (auto info : infoList){
    body.appendChild(this->_setXmlInfo(info));
  }

  return doc;
}

template QDomDocument XmlHelper::createXmlFromList<CustomerInfo>(QList<CustomerInfo>);
template QDomDocument XmlHelper::createXmlFromList<DeviceInfo>(QList<DeviceInfo>);
template QDomDocument XmlHelper::createXmlFromList<VenderInfo>(QList<VenderInfo>);
template QDomDocument XmlHelper::createXmlFromList<ServiceInfo>(QList<ServiceInfo>);
template QDomDocument XmlHelper::createXmlFromList<Relationship>(QList<Relationship>);


template <typename T>
QDomDocument XmlHelper::createInfoListXml(
    T info,
    QList<Relationship> relationList)
{
  QDomElement createdInfoList = doc.createElement("createdRelationshipList");
  body.appendChild(createdInfoList);
  createdInfoList.appendChild(this->_setXmlInfo(info));
  for (auto relation : relationList){
    createdInfoList.appendChild(this->_setXmlInfo(relation));
  }
  return doc;
}

template QDomDocument XmlHelper::createInfoListXml<DeviceInfo>(DeviceInfo, QList<Relationship>);
template QDomDocument XmlHelper::createInfoListXml<ServiceInfo>(ServiceInfo, QList<Relationship>);


QDomElement XmlHelper::_setXmlInfo(CustomerInfo info){
  QDomElement elementCustomerInfo;
  elementCustomerInfo = doc.createElement("customerInfo");
  std::vector<std::pair<QString, QString>> elementPairList;
  elementPairList.push_back(std::make_pair("id", QString::number(info.id())));
  elementPairList.push_back(std::make_pair("lId", QString::number(info.lId())));
  elementPairList.push_back(std::make_pair("lastName", info.lastName()));
  elementPairList.push_back(std::make_pair("firstName", info.firstName()));
  elementPairList.push_back(std::make_pair("birthday", info.birthday().toString()));
  elementPairList.push_back(std::make_pair("eMailAddr", info.eMailAddr()));
  elementPairList.push_back(std::make_pair("phonNum", info.phoneNum()));

  for(std::pair<QString, QString> elementPair : elementPairList){
    elementCustomerInfo.appendChild(this->_createXmlElement(elementPair.first, elementPair.second));
  }
  return elementCustomerInfo;
}


QDomElement XmlHelper::_setXmlInfo(DeviceInfo info){
  QDomElement elementDeviceInfo;
  elementDeviceInfo = doc.createElement("deviceInfo");
  std::vector<std::pair<QString, QString>> elementPairList;
  elementPairList.push_back(std::make_pair("id", QString::number(info.id())));
  elementPairList.push_back(std::make_pair("cId", QString::number(info.cId())));
  elementPairList.push_back(std::make_pair("deviceName", info.deviceName()));
  elementPairList.push_back(std::make_pair("defaultPrivacyStandard", QString::number(info.defaultPrivacyStandard())));
  elementPairList.push_back(std::make_pair("deviceType", QString::number(info.deviceType())));
  elementPairList.push_back(std::make_pair("dataType", QString::number(info.dataType())));
  elementPairList.push_back(std::make_pair("interval", QString::number(info.interval())));
  elementPairList.push_back(std::make_pair("location", info.location()));

  for(std::pair<QString, QString> elementPair : elementPairList){
    elementDeviceInfo.appendChild(this->_createXmlElement(elementPair.first, elementPair.second));
  }
  return elementDeviceInfo;
}


QDomElement XmlHelper::_setXmlInfo(VenderInfo info){
  QDomElement elementVenderInfo;
  elementVenderInfo = doc.createElement("venderInfo");
  std::vector<std::pair<QString, QString>> elementPairList;
  elementPairList.push_back(std::make_pair("id", QString::number(info.id())));
  elementPairList.push_back(std::make_pair("lId", QString::number(info.lId())));
  elementPairList.push_back(std::make_pair("name", info.name()));
  elementPairList.push_back(std::make_pair("eMailAddr", info.eMailAddr()));
  elementPairList.push_back(std::make_pair("phonNum", info.phoneNum()));

  for(std::pair<QString, QString> elementPair : elementPairList){
    elementVenderInfo.appendChild(this->_createXmlElement(elementPair.first, elementPair.second));
  }
  return elementVenderInfo;
}


QDomElement XmlHelper::_setXmlInfo(ServiceInfo info){
  QDomElement elementServiceInfo;
  elementServiceInfo = doc.createElement("serviceInfo");
  std::vector<std::pair<QString, QString>> elementPairList;
  elementPairList.push_back(std::make_pair("id", QString::number(info.id())));
  elementPairList.push_back(std::make_pair("vId", QString::number(info.vId())));
  elementPairList.push_back(std::make_pair("serviceName", info.serviceName()));
  elementPairList.push_back(std::make_pair("requiredPrivacyStandard", QString::number(info.requiredPrivacyStandard())));
  elementPairList.push_back(std::make_pair("dataType", QString::number(info.dataType())));
  elementPairList.push_back(std::make_pair("interval", QString::number(info.interval())));

  for(std::pair<QString, QString> elementPair : elementPairList){
    elementServiceInfo.appendChild(this->_createXmlElement(elementPair.first, elementPair.second));
  }
  return elementServiceInfo;
}


QDomElement XmlHelper::_setXmlInfo(Relationship info){
  QDomElement elementRelationhsip;
  elementRelationhsip = doc.createElement("relationship");
  std::vector<std::pair<QString, QString>> elementPairList;
  elementPairList.push_back(std::make_pair("id", QString::number(info.id())));
  elementPairList.push_back(std::make_pair("dId", QString::number(info.dId())));
  elementPairList.push_back(std::make_pair("deviceName", info.deviceName()));
  elementPairList.push_back(std::make_pair("sId", QString::number(info.sId())));
  elementPairList.push_back(std::make_pair("serviceName", info.serviceName()));
  elementPairList.push_back(std::make_pair("anonymityMethod", QString::number(info.anonymityMethod())));
  elementPairList.push_back(std::make_pair("privacyStandard", QString::number(info.privacyStandard())));
  elementPairList.push_back(std::make_pair("interval", QString::number(info.interval())));
  elementPairList.push_back(std::make_pair("location", info.location()));

  for(std::pair<QString, QString> elementPair : elementPairList){
    elementRelationhsip.appendChild(this->_createXmlElement(elementPair.first, elementPair.second));
  }
  return elementRelationhsip;
}


QDomElement XmlHelper::_createXmlElement(QString elementName, QString elementText)
{
  QDomElement element = doc.createElement(elementName);
  QDomText text = doc.createTextNode(elementText);
  element.appendChild(text);
  return element;
}


QDomDocument XmlHelper::createXmlForDist(QList<Relationship> relationList)
{
  for (auto relation : relationList){
    body.appendChild(this->_setXmlRelation(relation));
  }

  return doc;
}


QDomElement XmlHelper::_setXmlRelation(Relationship info){
  QDomElement elementRelationhsip;
  elementRelationhsip = doc.createElement("relationship");
  std::vector<std::pair<QString, QString>> elementPairList;
  elementPairList.push_back(std::make_pair("id", QString::number(info.id())));
  elementPairList.push_back(std::make_pair("createdAt", info.createdAt().toString()));
  elementPairList.push_back(std::make_pair("updatedAt", info.updatedAt().toString()));
  elementPairList.push_back(std::make_pair("dId", QString::number(info.dId())));
  elementPairList.push_back(std::make_pair("deviceName", info.deviceName()));
  elementPairList.push_back(std::make_pair("sId", QString::number(info.sId())));
  elementPairList.push_back(std::make_pair("serviceName", info.serviceName()));
  elementPairList.push_back(std::make_pair("anonymityMethod", QString::number(info.anonymityMethod())));
  elementPairList.push_back(std::make_pair("privacyStandard", QString::number(info.privacyStandard())));
  elementPairList.push_back(std::make_pair("interval", QString::number(info.interval())));
  elementPairList.push_back(std::make_pair("location", info.location()));

  for(std::pair<QString, QString> elementPair : elementPairList){
    elementRelationhsip.appendChild(this->_createXmlElement(elementPair.first, elementPair.second));
  }
  return elementRelationhsip;
}


QList<QVariantMap> XmlHelper::parseXml(QString infoName, QString rawXml){
  tDebug("%s", rawXml.toStdString().c_str());
  if (! rawXml.isEmpty()) {
    QDomDocument xmlDocument;
    if (xmlDocument.setContent(rawXml)) {
      if (infoName == "customerInfo") {
        QDomNodeList infoList = xmlDocument.elementsByTagName("customerInfo");
        if (infoList.isEmpty()) {
          return QList<QVariantMap>();//プロパティが入ってない
        }
        int infoNum = infoList.length();
        QList<QVariantMap> infoMapList;
        for (int i = 0; i < infoNum; ++i) {
          QDomNode infoNode = infoList.at(i);
          QDomNodeList nodeList = infoNode.childNodes();
          int nodeCount = nodeList.length();
          QVariantMap infoMap;
          bool flags[7] = {};
          for (int j = 0; j < nodeCount; ++j) {
            QDomElement element = nodeList.at(j).toElement();
            QString tagName = element.tagName();
            if ( tagName == "id" ) {
              infoMap.insert("id", element.text());
              flags[0] = true;
            } else if ( tagName == "lId" ) {
              infoMap.insert("lId", element.text());
              flags[1] = true;
            } else if ( tagName == "lastName" ) {
              infoMap.insert("lastName", element.text());
              flags[2] = true;
            } else if ( tagName == "firstName" ) {
              infoMap.insert("firstName", element.text());
              flags[3] = true;
            } else if ( tagName == "birthday" ) {
              infoMap.insert("birthday", element.text());
              flags[4] = true;
            } else if ( tagName == "eMailAddr" ) {
              infoMap.insert("eMailAddr", element.text());
              flags[5] = true;
            } else if ( tagName == "phoneNum" ) {
              infoMap.insert("phoneNum", element.text());
              flags[6] = true;
            } else {
              return QList<QVariantMap>();//タグ名が間違っている
            }
          }
          if (flags[1] && flags[2] && flags[3]
            && flags[4] && flags[5] && flags[6]){
            //id以外がある場合のみプロパティを返す
            infoMapList.append(infoMap);
          } else {
            return QList<QVariantMap>();//要素不足
          }
        }
        return infoMapList;
      } else if (infoName == "deviceInfo"){
        QDomNodeList infoList = xmlDocument.elementsByTagName("deviceInfo");
        if (infoList.isEmpty()) {
          return QList<QVariantMap>();
        }
        int infoNum = infoList.length();
        QList<QVariantMap> infoMapList;
        for (int i = 0; i < infoNum; ++i) {
          QDomNode infoNode = infoList.at(i);
          QDomNodeList nodeList = infoNode.childNodes();
          int nodeCount = nodeList.length();
          QVariantMap infoMap;
          bool flags[8] = {};
          for (int j = 0; j < nodeCount ; ++j) {
            QDomElement element = nodeList.at(j).toElement();
            QString tagName = element.tagName();
            if ( tagName == "id" ) {
              infoMap.insert("id", element.text());
              flags[0] = true;
            } else if ( tagName == "cId" ) {
              infoMap.insert("cId", element.text());
              flags[1] = true;
            } else if ( tagName == "deviceName" ) {
              infoMap.insert("deviceName", element.text());
              flags[2] = true;
            } else if ( tagName == "defaultPrivacyStandard" ) {
              infoMap.insert("defaultPrivacyStandard", element.text());
              flags[3] = true;
            } else if ( tagName == "deviceType" ) {
              infoMap.insert("deviceType", element.text());
              flags[4] = true;
            } else if ( tagName == "dataType" ) {
              infoMap.insert("dataType", element.text());
              flags[5] = true;
            } else if ( tagName == "interval" ) {
              infoMap.insert("interval", element.text());
              flags[6] = true;
            } else if ( tagName == "location" ) {
              infoMap.insert("location", element.text());
              flags[7] = true;
            }
          }
          if (flags[1] && flags[2] && flags[3]
            && flags[4] && flags[5] && flags[6] && flags[7]){
            //id以外がある場合のみプロパティを返す
            infoMapList.append(infoMap);
          } else {
            return QList<QVariantMap>();//要素不足
          }
        }
        return infoMapList;
      } else if (infoName == "venderInfo"){
        QDomNodeList infoList = xmlDocument.elementsByTagName("venderInfo");
        if (infoList.isEmpty()) {
          return QList<QVariantMap>();
        }
        int infoNum = infoList.length();
        QList<QVariantMap> infoMapList;
        for (int i = 0; i < infoNum; ++i) {
          QDomNode infoNode = infoList.at(i);
          QDomNodeList nodeList = infoNode.childNodes();
          int nodeCount = nodeList.length();
          QVariantMap infoMap;
          bool flags[4] = {};
          for (int j = 0; j < nodeCount ; ++j) {
            QDomElement element = nodeList.at(j).toElement();
            QString tagName = element.tagName();
            if ( tagName == "id" ) {
              infoMap.insert("id", element.text());
            } else if ( tagName == "lId" ) {
              infoMap.insert("lId", element.text());
              flags[0] = true;
            } else if ( tagName == "name" ) {
              infoMap.insert("name", element.text());
              flags[1] = true;
            } else if ( tagName == "eMailAddr" ) {
              infoMap.insert("eMailAddr", element.text());
              flags[2] = true;
            } else if ( tagName == "phoneNum" ) {
              infoMap.insert("phoneNum", element.text());
              flags[3] = true;
            }
          }
          if (flags[1] && flags[2] && flags[3]){
            //id以外がある場合のみプロパティを返す
            infoMapList.append(infoMap);
          } else {
            return QList<QVariantMap>();//要素不足
          }
        }
        return infoMapList;
      } else if (infoName == "serviceInfo"){
        QDomNodeList infoList = xmlDocument.elementsByTagName("serviceInfo");
        if (infoList.isEmpty()) {
          return QList<QVariantMap>();
        }
        int infoNum = infoList.length();
        QList<QVariantMap> infoMapList;
        for (int i = 0; i < infoNum; ++i) {
          QDomNode infoNode = infoList.at(i);
          QDomNodeList nodeList = infoNode.childNodes();
          int nodeCount = nodeList.length();
          QVariantMap infoMap;
          bool flags[6] = {};
          for (int j = 0; j < nodeCount ; ++j) {
            QDomElement element = nodeList.at(j).toElement();
            QString tagName = element.tagName();
            if ( tagName == "id" ) {
              infoMap.insert(tagName, element.text());
              flags[0] = true;
            } else if ( tagName == "vId" ) {
              infoMap.insert(tagName, element.text());
              flags[1] = true;
            } else if ( tagName == "serviceName" ) {
              infoMap.insert(tagName, element.text());
              flags[2] = true;
            } else if ( tagName == "requiredPrivacyStandard" ) {
              infoMap.insert(tagName, element.text());
              flags[3] = true;
            } else if ( tagName == "dataType" ) {
              infoMap.insert(tagName, element.text());
              flags[4] = true;
            } else if ( tagName == "interval" ) {
              infoMap.insert(tagName, element.text());
              flags[5] = true;
            }
          }
          if (flags[1] && flags[2] && flags[3]
            && flags[4] && flags[5]){
            //id以外がある場合のみプロパティを返す
            infoMapList.append(infoMap);
          } else {
            return QList<QVariantMap>();//要素不足
          }
        }
        return infoMapList;
      } else if (infoName == "relationship"){
        QDomNodeList infoList = xmlDocument.elementsByTagName("relationship");
        if (infoList.isEmpty()) {
          return QList<QVariantMap>();
        }
        int infoNum = infoList.length();
        QList<QVariantMap> infoMapList;
        for (int i = 0; i < infoNum; ++i) {
          QDomNode infoNode = infoList.at(i);
          QDomNodeList nodeList = infoNode.childNodes();
          int nodeCount = nodeList.length();
          QVariantMap infoMap;
          bool flags[9] = {};
          for (int j = 0; j < nodeCount ; ++j) {
            QDomElement element = nodeList.at(j).toElement();
            QString tagName = element.tagName();
            if ( tagName == "id" ) {
              infoMap.insert("id", element.text());
              flags[0] = true;
            } else if ( tagName == "createdAt" ) {
              infoMap.insert("createdAt", element.text());
              flags[1] = true;
            } else if ( tagName == "updatedAt" ) {
              infoMap.insert("updatedAt", element.text());
              flags[2] = true;
            } else if ( tagName == "dId" ) {
              infoMap.insert("dId", element.text());
              flags[3] = true;
            } else if ( tagName == "deviceName" ) {
              infoMap.insert("deviceName", element.text());
              flags[4] = true;
            } else if ( tagName == "sId" ) {
              infoMap.insert("sId", element.text());
              flags[5] = true;
            } else if ( tagName == "serviceName" ) {
              infoMap.insert("serviceName", element.text());
              flags[6] = true;
            } else if ( tagName == "anonymityMethod" ) {
              infoMap.insert("anonymityMethod", element.text());
              flags[7] = true;
            } else if ( tagName == "privacyStandard" ) {
              infoMap.insert("privacyStandard", element.text());
              flags[8] = true;
            } else if ( tagName == "interval" ) {
              infoMap.insert("interval", element.text());
              flags[9] = true;
            } else if ( tagName == "location" ) {
              infoMap.insert("location", element.text());
              flags[10] = true;
            }
          }
          if (flags[1] && flags[2] && flags[3] && flags[4]
            && flags[5] && flags[6] && flags[7] && flags[8] && flags[9] && flags[10]){
            //id以外がある場合のみプロパティを返す
            infoMapList.append(infoMap);
          } else {
            return QList<QVariantMap>();//要素不足
          }
        }
        return infoMapList;
      } else if (infoName == "loginInfo"){//一応作成
        QDomNodeList infoList = xmlDocument.elementsByTagName("loginInfo");
        if (infoList.isEmpty()) {
          return QList<QVariantMap>();
        }
        int infoNum = infoList.length();
        QList<QVariantMap> infoMapList;
        for (int i = 0; i < infoNum; ++i) {
          QDomNode infoNode = infoList.at(i);
          QDomNodeList nodeList = infoNode.childNodes();
          int nodeCount = nodeList.length();
          QVariantMap infoMap;
          bool flags[6] = {};
          for (int j = 0; j < nodeCount ; ++j) {
            QDomElement element = nodeList.at(j).toElement();
            QString tagName = element.tagName();
            if ( tagName == "id" ) {
              infoMap.insert("id", element.text());
              flags[0] = true;
            } else if ( tagName == "login" ) {
              infoMap.insert("login", element.text());
              flags[1] = true;
            } else if ( tagName == "passwd" ) {
              infoMap.insert("passwd", element.text());
              flags[2] = true;
            } else if ( tagName == "salt" ) {
              infoMap.insert(tagName, element.text());
              flags[3] = true;
            } else if ( tagName == "salt" ) {
              infoMap.insert(tagName, element.text());
              flags[4] = true;
            } else if ( tagName == "userType" ) {
              infoMap.insert("userType", element.text());
              flags[5] = true;
            }
          }
          if (flags[1] && flags[2]
            && flags[3] && flags[4] && flags[5]){
            //id以外がある場合のみプロパティを返す
            infoMapList.append(infoMap);
          } else {
            return QList<QVariantMap>();//要素不足
          }
        }
        return infoMapList;
      } else {
        tError("Error: the xml does not have info/relation");
        return QList<QVariantMap>();
      }
    } else {
      tError("Error: the xml is not valid");
      return QList<QVariantMap>();
    }
  } else {
    tError("Error: the request has no body");
    return QList<QVariantMap>();
  }
}
