#ifndef CURLHELPER_H
#define CURLHELPER_H

#include <type_traits>
#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>

#include <treefrog/TGlobal>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomElement>
#include <QtXml/QDomText>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QUrl>



class T_HELPER_EXPORT CurlHelper
{
  public:
    bool sendRelationshipList(QUrl url, QDomDocument relationXml);

  private:
    static size_t _callbackWrite(char *ptr, size_t size, size_t nmemb, std::string *stream);
};

#endif // CURLHELPER_H
