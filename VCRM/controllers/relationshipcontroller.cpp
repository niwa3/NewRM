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
        auto relationship = httpRequest().formItems("relationship");
        auto model = Relationship::create(relationship);

        if (!model.isNull()) {
            QString notice = "Created successfully.";
            tflash(notice);
            redirect(urla("show", model.id()));
        } else {
            QString error = "Failed to create.";
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
