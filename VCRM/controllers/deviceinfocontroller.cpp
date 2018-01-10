#include "deviceinfocontroller.h"
#include "deviceinfo.h"


void DeviceInfoController::index()
{
    auto deviceInfoList = DeviceInfo::getAll();
    texport(deviceInfoList);
    render();
}

void DeviceInfoController::show(const QString &id)
{
    auto deviceInfo = DeviceInfo::get(id.toInt());
    texport(deviceInfo);
    render();
}

void DeviceInfoController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto deviceInfo = httpRequest().formItems("deviceInfo");
        auto model = DeviceInfo::create(deviceInfo);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(deviceInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void DeviceInfoController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = DeviceInfo::get(id.toInt());
        if (!model.isNull()) {
            auto deviceInfo = model.toVariantMap();
            texport(deviceInfo);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = DeviceInfo::get(id.toInt());
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto deviceInfo = httpRequest().formItems("deviceInfo");
        model.setProperties(deviceInfo);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(deviceInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void DeviceInfoController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto deviceInfo = DeviceInfo::get(id.toInt());
    deviceInfo.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(DeviceInfoController)
