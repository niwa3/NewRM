#include "curlhelper.h"


size_t CurlHelper::_callbackWrite(char *ptr, size_t size, size_t nmemb, std::string *stream)
{
  int dataLength = size * nmemb;
  stream->append(ptr, dataLength);
  return dataLength;
}


bool CurlHelper::sendRelationshipList(QUrl url, QDomDocument relationXml)
{
  CURL *curl;
  CURLcode ret;
  std::string requestBody = relationXml.toString().toStdString();
  curl_off_t length_of_data = requestBody.size();

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  std::string chunk;

  if(curl == NULL){
    tError("curl_easy_init() failed");
    return false;
  }

  curl_easy_setopt(curl, CURLOPT_URL, url.url().toStdString().c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, length_of_data);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
  curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/ssl/certs/server.crt");
  ret = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  if(ret != CURLE_OK){
    tError("curl_easy_perform() failed.");
    return false;
  }

  return true;
}
