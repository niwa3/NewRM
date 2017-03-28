//define
#ifndef __INCLUDED_DEFINE_H__
#define __INCLUDED_DEFINE_H__

#include <iostream>

//general

//define of each id
typedef std::string Consumer_id;
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

#endif
