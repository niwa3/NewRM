#ifndef SERVICEINFOCONTROLLER_H
#define SERVICEINFOCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT ServiceInfoController : public ApplicationController
{
    Q_OBJECT
public:
    ServiceInfoController() : ApplicationController() {}

public slots:
    //void index();
    void show();
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // SERVICEINFOCONTROLLER_H
