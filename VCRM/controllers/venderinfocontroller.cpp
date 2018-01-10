#include "venderinfocontroller.h"
#include "venderinfo.h"


void VenderInfoController::index()
{
    auto venderInfoList = VenderInfo::getAll();
    texport(venderInfoList);
    render();
}

void VenderInfoController::show(const QString &id)
{
    auto venderInfo = VenderInfo::get(id.toInt());
    texport(venderInfo);
    render();
}

void VenderInfoController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        auto venderInfo = httpRequest().formItems("venderInfo");
        auto model = VenderInfo::create(venderInfo);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(venderInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void VenderInfoController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = VenderInfo::get(id.toInt());
        if (!model.isNull()) {
            auto venderInfo = model.toVariantMap();
            texport(venderInfo);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = VenderInfo::get(id.toInt());
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto venderInfo = httpRequest().formItems("venderInfo");
        model.setProperties(venderInfo);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(venderInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void VenderInfoController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto venderInfo = VenderInfo::get(id.toInt());
    venderInfo.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(VenderInfoController)
