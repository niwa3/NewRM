#include <QtCore>
#include <TreeFrogView>
#include "deviceinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT deviceinfo_showView : public TActionView
{
  Q_OBJECT
public:
  deviceinfo_showView() : TActionView() { }
  QString toString();
};

QString deviceinfo_showView::toString()
{
  responsebody.reserve(2213);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(DeviceInfo, deviceInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Device Info</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>C ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.cId());
  responsebody += QLatin1String("</dd><br />\n<dt>Device Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.deviceName());
  responsebody += QLatin1String("</dd><br />\n<dt>Default Privacy Standard</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.defaultPrivacyStandard());
  responsebody += QLatin1String("</dd><br />\n<dt>Device Type</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.deviceType());
  responsebody += QLatin1String("</dd><br />\n<dt>Data Type</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.dataType());
  responsebody += QLatin1String("</dd><br />\n<dt>Interval</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.interval());
  responsebody += QLatin1String("</dd><br />\n<dt>Location</dt><dd>");
  responsebody += THttpUtility::htmlEscape(deviceInfo.location());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", deviceInfo.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(deviceinfo_showView)

#include "deviceinfo_showView.moc"
