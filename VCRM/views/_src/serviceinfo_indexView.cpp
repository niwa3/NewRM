#include <QtCore>
#include <TreeFrogView>
#include "serviceinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT serviceinfo_indexView : public TActionView
{
  Q_OBJECT
public:
  serviceinfo_indexView() : TActionView() { }
  QString toString();
};

QString serviceinfo_indexView::toString()
{
  responsebody.reserve(2076);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n\n<h1>Listing Service Info</h1>\n\n");
  responsebody += QVariant(linkTo("Create a new Service Info", urla("create"))).toString();
  responsebody += QLatin1String("<br />\n<br />\n<table border=\"1\" cellpadding=\"5\" style=\"border: 1px #d0d0d0 solid; border-collapse: collapse;\">\n  <tr>\n    <th>ID</th>\n    <th>V ID</th>\n    <th>Service Name</th>\n    <th>Required Privacy Standard</th>\n    <th>Data Type</th>\n    <th>Interval</th>\n  </tr>\n");
  tfetch(QList<ServiceInfo>, serviceInfoList);
  for (const auto &i : serviceInfoList) {
  responsebody += QLatin1String("  <tr>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.id());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.vId());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.serviceName());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.requiredPrivacyStandard());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.dataType());
  responsebody += QLatin1String("</td>\n    <td>");
  responsebody += THttpUtility::htmlEscape(i.interval());
  responsebody += QLatin1String("</td>\n    <td>\n      ");
  responsebody += QVariant(linkTo("Show", urla("show", i.id()))).toString();
  responsebody += QLatin1String("\n      ");
  responsebody += QVariant(linkTo("Edit", urla("save", i.id()))).toString();
  responsebody += QLatin1String("\n      ");
  responsebody += QVariant(linkTo("Remove", urla("remove", i.id()), Tf::Post, "confirm('Are you sure?')")).toString();
  responsebody += QLatin1String("\n    </td>\n  </tr>\n");
  };
  responsebody += QLatin1String("</table>\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(serviceinfo_indexView)

#include "serviceinfo_indexView.moc"
