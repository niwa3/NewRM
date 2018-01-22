#include <QtCore>
#include <TreeFrogView>
#include "serviceinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT serviceinfo_showView : public TActionView
{
  Q_OBJECT
public:
  serviceinfo_showView() : TActionView() { }
  QString toString();
};

QString serviceinfo_showView::toString()
{
  responsebody.reserve(1948);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(ServiceInfo, serviceInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Service Info</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>V ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.vId());
  responsebody += QLatin1String("</dd><br />\n<dt>Service Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.serviceName());
  responsebody += QLatin1String("</dd><br />\n<dt>Required Privacy Standard</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.requiredPrivacyStandard());
  responsebody += QLatin1String("</dd><br />\n<dt>Data Type</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.dataType());
  responsebody += QLatin1String("</dd><br />\n<dt>Interval</dt><dd>");
  responsebody += THttpUtility::htmlEscape(serviceInfo.interval());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", serviceInfo.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(serviceinfo_showView)

#include "serviceinfo_showView.moc"
