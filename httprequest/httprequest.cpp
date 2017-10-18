#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <tinyxml2.h>

size_t callbackWrite(char *ptr, size_t size, size_t nmemb, std::string *stream)
{
  int dataLength = size * nmemb;
  stream->append(ptr, dataLength);
  return dataLength;
}

int main( int argv, char* argc[] )
{
  CURL *curl;
  CURLcode ret;

  curl = curl_easy_init();
  std::string chunk;

  if(curl == NULL){
    std::cerr << "curl_easy_init() failed" << std::endl;
    return 1;
  }

//  std::ifstream pref_xml("./gnavi_prefsearch.xml");

//  tinyxml2::XMLDocument xml;

  std::string keyid = "00612c8f784426bdb8ce39baa8f6409a";
  std::string url = "https://api.gnavi.co.jp/RestSearchAPI/20150630/?keyid="+keyid+"&name=";
  url += argc[1];
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackWrite);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
  ret = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  if(ret != CURLE_OK){
    std::cerr<<"curl_easy_perform() failed."<<std::endl;
    return 1;
  }

  std::ofstream file("./google.txt");
  file<<chunk<<std::endl;
  file.close();

  return 0;
}
