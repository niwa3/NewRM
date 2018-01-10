#ifndef LOGININFOCONTROLLER_H
#define LOGININFOCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT LoginInfoController : public ApplicationController
{
    Q_OBJECT
public:
    LoginInfoController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // LOGININFOCONTROLLER_H
