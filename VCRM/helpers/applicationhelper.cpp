#include "applicationhelper.h"


/**
 * createXml(T)
 * T = CustomerInfo, DeviceInfo, VenderInfo, ServiceInfo, Relationship
 * return QDomDocument
 */
template <typename T>
QDomDocument ApplicationHelper::createXml(T info){
  QDomDocument doc;
  QDomElement body = doc.createElement("body");
  doc.appendChild(body);

  body.appendChild(this->_setXmlInfo(info));

  return doc;
}

template QDomDocument ApplicationHelper::createXml<CustomerInfo>(CustomerInfo);
template QDomDocument ApplicationHelper::createXml<DeviceInfo>(DeviceInfo);
template QDomDocument ApplicationHelper::createXml<VenderInfo>(VenderInfo);
template QDomDocument ApplicationHelper::createXml<ServiceInfo>(ServiceInfo);
template QDomDocument ApplicationHelper::createXml<Relationship>(Relationship);


template <typename T>
QDomDocument ApplicationHelper::createXmlFromList(QList<T> infoList){
  QDomDocument doc;
  QDomElement body = doc.createElement("body");
  doc.appendChild(body);

  for (auto info : infoList){
    body.appendChild(this->_setXmlInfo(info));
  }

  return doc;
}

template QDomDocument ApplicationHelper::createXmlFromList<CustomerInfo>(QList<CustomerInfo>);
template QDomDocument ApplicationHelper::createXmlFromList<DeviceInfo>(QList<DeviceInfo>);
template QDomDocument ApplicationHelper::createXmlFromList<VenderInfo>(QList<VenderInfo>);
template QDomDocument ApplicationHelper::createXmlFromList<ServiceInfo>(QList<ServiceInfo>);
template QDomDocument ApplicationHelper::createXmlFromList<Relationship>(QList<Relationship>);


QDomElement ApplicationHelper::_setXmlInfo(CustomerInfo info){
  QDomDocument doc;
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


QDomElement ApplicationHelper::_setXmlInfo(DeviceInfo info){
  QDomDocument doc;
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


QDomElement ApplicationHelper::_setXmlInfo(VenderInfo info){
  QDomDocument doc;
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


QDomElement ApplicationHelper::_setXmlInfo(ServiceInfo info){
  QDomDocument doc;
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


QDomElement ApplicationHelper::_setXmlInfo(Relationship info){
  QDomDocument doc;
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


QDomElement ApplicationHelper::_createXmlElement(QString elementName, QString elementText){
  QDomDocument doc;
  QDomElement element = doc.createElement(elementName);
  QDomText text = doc.createTextNode(elementText);
  element.appendChild(text);
  return element;
}
