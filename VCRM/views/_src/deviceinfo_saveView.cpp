#include <QtCore>
#include <TreeFrogView>
#include "deviceinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT deviceinfo_saveView : public TActionView
{
  Q_OBJECT
public:
  deviceinfo_saveView() : TActionView() { }
  QString toString();
};

QString deviceinfo_saveView::toString()
{
  responsebody.reserve(2809);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, deviceInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Editing Device Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("save", deviceInfo["id"]), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>ID<br /><input type=\"text\" name=\"deviceInfo[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["id"]);
  responsebody += QLatin1String("\" readonly=\"readonly\" /></label>\n  </p>\n  <p>\n    <label>C ID<br /><input type=\"text\" name=\"deviceInfo[cId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["cId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Device Name<br /><input type=\"text\" name=\"deviceInfo[deviceName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["deviceName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Default Privacy Standard<br /><input type=\"text\" name=\"deviceInfo[defaultPrivacyStandard]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["defaultPrivacyStandard"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Device Type<br /><input type=\"text\" name=\"deviceInfo[deviceType]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["deviceType"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Data Type<br /><input type=\"text\" name=\"deviceInfo[dataType]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["dataType"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Interval<br /><input type=\"text\" name=\"deviceInfo[interval]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["interval"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Location<br /><input type=\"text\" name=\"deviceInfo[location]\" value=\"");
  responsebody += THttpUtility::htmlEscape(deviceInfo["location"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Save\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Show", urla("show", deviceInfo["id"]))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(deviceinfo_saveView)

#include "deviceinfo_saveView.moc"
