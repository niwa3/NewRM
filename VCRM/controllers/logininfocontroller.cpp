#include "logininfocontroller.h"
#include "logininfo.h"


void LoginInfoController::index()
{
    auto loginInfoList = LoginInfo::getAll();
    texport(loginInfoList);
    render();
}

void LoginInfoController::show(const QString &id)
{
    auto loginInfo = LoginInfo::get(id.toInt());
    texport(loginInfo);
    render();
}

void LoginInfoController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto loginInfo = httpRequest().formItems("loginInfo");
        auto model = LoginInfo::create(loginInfo);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(loginInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void LoginInfoController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = LoginInfo::get(id.toInt());
        if (!model.isNull()) {
            auto loginInfo = model.toVariantMap();
            texport(loginInfo);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = LoginInfo::get(id.toInt());
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto loginInfo = httpRequest().formItems("loginInfo");
        model.setProperties(loginInfo);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(loginInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void LoginInfoController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto loginInfo = LoginInfo::get(id.toInt());
    loginInfo.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(LoginInfoController)
