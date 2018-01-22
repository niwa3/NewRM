/**
 * @file customerinfocontroller.h
 * @brief this file is a controller of customerinfo.
 * @author niwa3
 * @data 01/06/2018
 */


#include "customerinfocontroller.h"
#include "customerinfo.h"
#include <iostream>


/*
void CustomerInfoController::index()
{
    auto customerInfoList = CustomerInfo::getAll();
    XmlHelper help;
    auto cusXml = help.createXmlFromList<CustomerInfo>(customerInfoList);
    renderXml(cusXml);
}
*/


/**
 * @fn
 * This function is used for get a customerinf. You can set a condition (id, lId).
 */
void CustomerInfoController::show()
{
    this->_setParams();
    if (this->_params.contains("lId")){
        auto customerInfo = CustomerInfo::getByLid(_params["lId"].toInt());
        XmlHelper help;
        auto cusXml = help.createXml<CustomerInfo>(customerInfo);
        renderXml(cusXml);
    } else if (this->_params.contains("id")){
        auto customerInfo = CustomerInfo::get(_params["id"].toInt());
        XmlHelper help;
        auto cusXml = help.createXml<CustomerInfo>(customerInfo);
        renderXml(cusXml);
    } else {
        renderErrorResponse(404);
    }
}


void CustomerInfoController::create()
{
    switch (httpRequest().method()) {
    case Tf::Get:
        renderErrorResponse(404);
        break;

    case Tf::Post: {
        auto customerInfo = httpRequest().formItems("customerInfo");
        auto model = CustomerInfo::create(customerInfo);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
            texport(error);
            texport(customerInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void CustomerInfoController::save(const QString &id)
{
    switch (httpRequest().method()) {
    case Tf::Get: {
        auto model = CustomerInfo::get(id.toInt());
        if (!model.isNull()) {
            auto customerInfo = model.toVariantMap();
            texport(customerInfo);
            render();
        }
        break; }

    case Tf::Post: {
        QString error;
        auto model = CustomerInfo::get(id.toInt());

        if (model.isNull()) {
            error = "Original data not found. It may have been updated/removed by another transaction.";
            tflash(error);
            redirect(urla("save", id));
            break;
        }

        auto customerInfo = httpRequest().formItems("customerInfo");
        model.setProperties(customerInfo);
        if (model.save()) {
            QString notice = "Updated successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            error = "Failed to update.";
            texport(error);
            texport(customerInfo);
            render();
        }
        break; }

    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

void CustomerInfoController::remove(const QString &id)
{
    if (httpRequest().method() != Tf::Post) {
        renderErrorResponse(Tf::NotFound);
        return;
    }

    auto customerInfo = CustomerInfo::get(id.toInt());
    customerInfo.remove();
    redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(CustomerInfoController)
