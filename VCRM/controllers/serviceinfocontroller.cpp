#include "serviceinfocontroller.h"
#include "serviceinfo.h"


void ServiceInfoController::index()
{
  auto serviceInfoList = ServiceInfo::getAll();
  texport(serviceInfoList);
  render();
}


void ServiceInfoController::show()
{
  this->_setParams();
  if (this->_params.size()!=1) {
    renderErrorResponse(404);
  }
  if (this->_params.contains("vId")){
    auto serviceInfo = ServiceInfo::getByVid(_params["vId"].toInt());
    XmlHelper xmlHelp;
    auto serviceXml = xmlHelp.createXmlFromList<ServiceInfo>(serviceInfo);
    renderXml(serviceXml);
  } else if (this->_params.contains("id")){
    auto serviceInfo = ServiceInfo::get(_params["id"].toInt());
    XmlHelper xmlHelp;
    auto serviceXml = xmlHelp.createXml<ServiceInfo>(serviceInfo);
    renderXml(serviceXml);
  } else {
    renderErrorResponse(404);
  }
}

void ServiceInfoController::create()
{
  switch (httpRequest().method()) {
  case Tf::Get:
    //render();
    renderErrorResponse(404);
    break;

  case Tf::Post: {
    this->_setRawBody();
    XmlHelper xmlHelp;
    ApplicationHelper appHelp;
    QList<QVariantMap> serviceInfoMapList =
        xmlHelp.parseXml("serviceInfo", this->_rawBody);
    if (serviceInfoMapList.isEmpty()){//パースできなければエラー
      renderText("Error: invalid xml");
    } else if (serviceInfoMapList.length()==1){//serviceInfoが一つのとき
      ServiceInfo serviceQuery;
      ServiceInfo service = serviceQuery.create(serviceInfoMapList.first());
      if (service.isNull()) {
        //serviceInfoをデータベースに登録できなかった場合
        renderText("Error: failed to create");
        break;
      }
      DeviceInfo deviceQuery;
      QList<DeviceInfo> deviceList = deviceQuery.getForMatch(
          service.dataType(),
          service.requiredPrivacyStandard(),
          service.interval()
      );
      if (deviceList.isEmpty()){
        /*
         * マッチするデバイスがない場合リレーションシップは作られず，
         * サービス情報のみを返す
         */
        renderXml(xmlHelp.createXml(service));
        break;
      }
      QList<QVariantMap> relationshipList =
          appHelp.createRelationMap(service, deviceList);
      Relationship relationQuery;
      //リレーションシップの登録
      QList<Relationship> createdRelations = relationQuery.create(relationshipList);
      //配布用のXMLを作成し，curlを用いて配布を行う
      XmlHelper helpForDist;
      CurlHelper request;
      if (
        !request.sendRelationshipList(
          QUrl("https://slave/relationship/insert/"),
          helpForDist.createXmlForDist(createdRelations)
        )
      ) {
        renderErrorResponse(400);
        break;
      }
      renderXml(
        xmlHelp.createInfoListXml(
          service,
          createdRelations
        )
      );
    } else {//複数の時
      ServiceInfo query;
      QList<ServiceInfo> serviceInfoList = query.create(serviceInfoMapList);
      if (serviceInfoList.isEmpty()) {
        /*
         * 一つでもserviceInfoをデータベースに登録できなかった場合エラーを返す
         */
        renderText("Error: failed to create");
        break;
      }
      for (ServiceInfo service : serviceInfoList) {
        DeviceInfo deviceQuery;
        QList<DeviceInfo> deviceList = deviceQuery.getForMatch(
            service.dataType(),
            service.requiredPrivacyStandard(),
            service.interval()
        );
        if (deviceList.isEmpty()){
          /*
           * マッチするデバイスがない場合は，空のリレーションシップリストを渡し，
           * そのサービスについてのXMLにはサービス情報のみを加える
           */
          xmlHelp.createInfoListXml(
            service,
            QList<Relationship>()
          );
          continue;
        }
        QList<QVariantMap> relationshipList =
            appHelp.createRelationMap(service, deviceList);
        Relationship relationQuery;
        QList<Relationship> createdRelations = relationQuery.create(relationshipList);
        //配布用のXMLを作成し，curlを用いて配布を行う
        XmlHelper helpForDist;
        CurlHelper request;
        if (
          !request.sendRelationshipList(
            QUrl("http://slave:8800/relationship/insert/"),
            helpForDist.createXmlForDist(createdRelations)
          )
        ) {
          renderErrorResponse(400);
          break;
        }
        xmlHelp.createInfoListXml(
          service,
          createdRelations
        );
      }
      renderXml(xmlHelp.getXml());
    }
    break; }

  default:
    renderErrorResponse(404);
    //renderErrorResponse(Tf::NotFound);
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
