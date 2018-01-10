#ifndef DEVICEINFOCONTROLLER_H
#define DEVICEINFOCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT DeviceInfoController : public ApplicationController
{
    Q_OBJECT
public:
    DeviceInfoController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // DEVICEINFOCONTROLLER_H
