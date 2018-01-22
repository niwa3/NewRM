#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QtCore/QVariantMap>

#include <treefrog/TActionController>

#include "../helpers/applicationhelper.h"
#include "../helpers/xmlhelper.h"


//Declare and define of privacy lvl
struct PriLvl{
  static const int MAXLVL = 3;
  static const int MINLVL = 0;
  static const int HIGH = 3;
  static const int MID = 2;
  static const int LOW = 1;
  static const int NONE = 0;
};

//Declare and define of device type
struct DeviceType{
  static const int SENSOR = 1;
  static const int ACTUATOR = 2;
  static const int NONE = 0;
};

//Declare and define of data type
struct DataType{
  static const int POWER = 1;
  static const int TEMP = 2;
  static const int CO2 = 3;
  static const int WIND = 4;
  static const int NONE = 0;
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
