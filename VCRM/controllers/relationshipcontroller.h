#ifndef RELATIONSHIPCONTROLLER_H
#define RELATIONSHIPCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT RelationshipController : public ApplicationController
{
    Q_OBJECT
public:
    RelationshipController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void insert();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // RELATIONSHIPCONTROLLER_H
