#ifndef VENDERINFOCONTROLLER_H
#define VENDERINFOCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT VenderInfoController : public ApplicationController
{
    Q_OBJECT
public:
    VenderInfoController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // VENDERINFOCONTROLLER_H
