#include "applicationcontroller.h"


ApplicationController::ApplicationController()
    : TActionController()
{ }

ApplicationController::~ApplicationController()
{ }

void ApplicationController::staticInitialize()
{ }

void ApplicationController::staticRelease()
{ }

bool ApplicationController::preFilter()
{
    return true;
}

void ApplicationController::_setParams(){
    this->_params = httpRequest().allParameters();
}

void ApplicationController::_setRawBody(){
    auto rawBody = httpRequest().rawBody();
    if (rawBody->open(QIODevice::ReadOnly)) {
        this->_rawBody = QString::fromUtf8(rawBody->readAll());
    } else {
        this->_rawBody = "";
    }
}

// Don't remove below this line
T_DEFINE_CONTROLLER(ApplicationController)
