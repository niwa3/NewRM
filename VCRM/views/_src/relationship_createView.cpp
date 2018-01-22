#include <QtCore>
#include <TreeFrogView>
#include "relationship.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT relationship_createView : public TActionView
{
  Q_OBJECT
public:
  relationship_createView() : TActionView() { }
  QString toString();
};

QString relationship_createView::toString()
{
  responsebody.reserve(2572);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, relationship);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>New Relationship</h1>\n\n");
  responsebody += QVariant(formTag(urla("create"), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>D ID<br /><input name=\"relationship[dId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["dId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Device Name<br /><input name=\"relationship[deviceName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["deviceName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>S ID<br /><input name=\"relationship[sId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["sId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Service Name<br /><input name=\"relationship[serviceName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["serviceName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Anonymity Method<br /><input name=\"relationship[anonymityMethod]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["anonymityMethod"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Privacy Standard<br /><input name=\"relationship[privacyStandard]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["privacyStandard"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Interval<br /><input name=\"relationship[interval]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["interval"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Location<br /><input name=\"relationship[location]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["location"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Create\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(relationship_createView)

#include "relationship_createView.moc"
