#include "serviceinfocontroller.h"
#include "serviceinfo.h"

/*
    void ServiceInfoController::index()
    {
        auto serviceInfoList = ServiceInfo::getAll();
        texport(serviceInfoList);
        render();
    }
*/

void ServiceInfoController::show()
{
    this->_setParams();
    if (this->_params.size()!=1) {
        renderErrorResponse(404);
    }
    if (this->_params.contains("vId")){
        auto serviceInfo = ServiceInfo::getByVid(_params["vId"].toInt());
        ApplicationHelper help;
        auto serviceXml = help.createXmlFromList<ServiceInfo>(serviceInfo);
        renderXml(serviceXml);
    } else if (this->_params.contains("id")){
        auto serviceInfo = ServiceInfo::get(_params["id"].toInt());
        ApplicationHelper help;
        auto serviceXml = help.createXml<ServiceInfo>(serviceInfo);
        renderXml(serviceXml);
    } else {
        renderErrorResponse(404);
    }
    renderErrorResponse(404);
}

void ServiceInfoController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        render();
        break;

    case Tf::Post: {
        this->_setRawBody();
        if (! this->_rawBody.isEmpty()){
            QDomDocument serviceInfo;
            if (serviceInfo.setContent(this->_rawBody)) {
                renderXml(serviceInfo);
            } else {
              tError("Error: the body is not valid");
            renderText("Error: the body is not valid.\n");
            }
        } else {
            tError("Error: the request has no body");
            renderText("Error: the request has no body.\n");
        }
        //tDebug("serviceInfo:%d", serviceInfo);
        //if (serviceInfo) {
        //  renderText("true");
        //} else {
        //  renderText("false");
        //}
        //auto model = ServiceInfo::create(serviceInfo);

        //if (!model.isNull()) {
        //    QString notice = "Created successfully.";
        //    tflash(notice);
        //    redirect(urla("show", model.id()));
        //} else {
        //    QString error = "Failed to create.";
        //    texport(error);
        //    texport(serviceInfo);
        //    render();
        //}
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void ServiceInfoController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = ServiceInfo::get(id.toInt());
        if (!model.isNull()) {
            auto serviceInfo = model.toVariantMap();
            texport(serviceInfo);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = ServiceInfo::get(id.toInt());
        
        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto serviceInfo = httpRequest().formItems("serviceInfo");
        model.setProperties(serviceInfo);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(serviceInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void ServiceInfoController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto serviceInfo = ServiceInfo::get(id.toInt());
    serviceInfo.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(ServiceInfoController)
