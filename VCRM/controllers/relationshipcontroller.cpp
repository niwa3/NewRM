#include "relationshipcontroller.h"
#include "relationship.h"


void RelationshipController::index()
{
  auto relationshipList = Relationship::getAll();
  texport(relationshipList);
  render();
}

void RelationshipController::show(const QString &id)
{
  auto relationship = Relationship::get(id.toInt());
  texport(relationship);
  render();
}

void RelationshipController::create()
{
  switch (httpRequest().method()) {
  case Tf::Get:
    render();
    break;

  case Tf::Post: {
    this->_setRawBody();
    XmlHelper help;
    QList<QVariantMap> relationMapList =
        help.parseXml("relationship", this->_rawBody);
    if (relationMapList.isEmpty()){//パースできなければエラー
      tError("can not parse");
      renderErrorResponse(400);
    } else if (relationMapList.length()==1){//relationが一つのとき
      Relationship relationQuery;
      Relationship relation = relationQuery.create(relationMapList.first());
      if (relation.isNull()) {
        tError("can not insert");
        renderErrorResponse(400);
        break;
      }
      renderXml(help.createXml(relation));
    } else {
      Relationship relationQuery;
      QList<Relationship> relationList = relationQuery.create(relationMapList);
      if (relationList.isEmpty()) {
        renderErrorResponse(400);
        break;
      }
      renderXml(help.createXmlFromList(relationList));
    }
    break; }

  default:
    renderErrorResponse(Tf::NotFound);
    break;
  }
}



void RelationshipController::insert()
{
  switch (httpRequest().method()) {
  case Tf::Get:
    renderText("please use POST");
    break;

  case Tf::Post: {
    this->_setRawBody();
    XmlHelper help;
    QList<QVariantMap> relationMapList =
        help.parseXml("relationship", this->_rawBody);
    if (relationMapList.isEmpty()){//パースできなければエラー
      renderText("Error: invalid xml");
    } else if (relationMapList.length()==1){//relationが一つのとき
      Relationship relationQuery;
      Relationship relation = relationQuery.insert(relationMapList.first());
      if (relation.isNull()) {
        renderErrorResponse(400);
        break;
      }
      renderXml(help.createXml(relation));
    } else {
      Relationship relationQuery;
      QList<Relationship> relationList = relationQuery.insert(relationMapList);
      if (relationList.isEmpty()) {
        renderErrorResponse(400);
        break;
      }
      renderXml(help.createXmlFromList(relationList));
    }
    break; }

  default:
    renderErrorResponse(Tf::NotFound);
    break;
  }
}

void RelationshipController::save(const QString &id)
{
  switch (httpRequest().method()) {
  case Tf::Get: {
    auto model = Relationship::get(id.toInt());
    if (!model.isNull()) {
      auto relationship = model.toVariantMap();
      texport(relationship);
      render();
    }
    break; }

  case Tf::Post: {
    QString error;
    auto model = Relationship::get(id.toInt());
    
    if (model.isNull()) {
      error = "Original data not found. It may have been updated/removed by another transaction.";
      tflash(error);
      redirect(urla("save", id));
      break;
    }

    auto relationship = httpRequest().formItems("relationship");
    model.setProperties(relationship);
    if (model.save()) {
      QString notice = "Updated successfully.";
      tflash(notice);
      redirect(urla("show", model.id()));
    } else {
      error = "Failed to update.";
      texport(error);
      texport(relationship);
      render();
    }
    break; }

  default:
    renderErrorResponse(Tf::NotFound);
    break;
  }
}

void RelationshipController::remove(const QString &id)
{
  if (httpRequest().method() != Tf::Post) {
    renderErrorResponse(Tf::NotFound);
    return;
  }

  auto relationship = Relationship::get(id.toInt());
  relationship.remove();
  redirect(urla("index"));
}


// Don't remove below this line
T_DEFINE_CONTROLLER(RelationshipController)
