#ifndef CUSTOMERINFOCONTROLLER_H
#define CUSTOMERINFOCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT CustomerInfoController : public ApplicationController
{
    Q_OBJECT
public:
    CustomerInfoController() : ApplicationController() {}

public slots:
    //void index();
    void show();
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // CUSTOMERINFOCONTROLLER_H
