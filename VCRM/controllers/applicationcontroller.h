#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QtCore/QVariantMap>

#include <treefrog/TActionController>

#include "applicationhelper.h"


//Declare and define of privacy lvl
struct PriLvl{
  static const int MAXLVL;
  static const int MINLVL;
  static const int HIGH;
  static const int MID;
  static const int LOW;
  static const int NONE;
};

//Declare and define of device type
struct DeviceType{
  static const int SENSOR;
  static const int ACTUATOR;
  static const int NONE;
};

//Declare and define of data type
struct DataType{
  static const int POWER;
  static const int TEMP;
  static const int CO2;
  static const int WIND;
  static const int NONE;
};



class T_CONTROLLER_EXPORT ApplicationController : public TActionController
{
    Q_OBJECT
public:
    ApplicationController();
    virtual ~ApplicationController();

public slots:
    void staticInitialize();
    void staticRelease();

protected:
    QVariantMap _params;
    QString _rawBody;

    virtual bool preFilter();
    void _setParams();
    void _setRawBody();
};

#endif // APPLICATIONCONTROLLER_H
