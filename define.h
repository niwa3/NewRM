//define
#ifndef __INCLUDED_DEFINE_H__
#define __INCLUDED_DEFINE_H__

#include <iostream>
#include <limits>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>
#include <list>
#include <mutex>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <mutex>
#include <vector>
#include <atomic>
#include "type.h"
//#include "MakeRelation.h"
//#include "xmlcreate.h"
//#include "xmlparse.h"


//general

//define of each id
typedef std::string Customer_id;
typedef std::string Device_id;
typedef std::string Vender_id;
typedef std::string Service_id;
typedef int Relation_id;

//Declare and define of privacy lvl
typedef int Privacy_lvl;
struct PriLvl{
  static const int MAXLVL;
  static const int MINLVL;
  static const int HIGH;
  static const int MID;
  static const int LOW;
  static const int NONE;
};

//Declare and define of device type
typedef int Device_type;
struct DeviceType{
  static const int SENSOR;
  static const int ACTUATOR;
  static const int NONE;
};

//Declare and define of data type
typedef int Data_type;
struct DataType{
  static const int POWER;
  static const int TEMP;
  static const int CO2;
  static const int WIND;
  static const int NONE;
};

//define of interval
typedef int Interval;

//define of location
typedef std::string Address;

class RelationshipManager{
  public:
    RelationshipManager();
    ~RelationshipManager();
    void run();

  private:
    void create();
    void serve();
    void closeSocket(int&);
    void handle(int&);
    std::string socketName_;
    std::mutex mtx;
};


#endif
