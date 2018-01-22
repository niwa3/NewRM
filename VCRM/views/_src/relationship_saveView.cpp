#include <QtCore>
#include <TreeFrogView>
#include "relationship.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT relationship_saveView : public TActionView
{
  Q_OBJECT
public:
  relationship_saveView() : TActionView() { }
  QString toString();
};

QString relationship_saveView::toString()
{
  responsebody.reserve(3059);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, relationship);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Editing Relationship</h1>\n\n");
  responsebody += QVariant(formTag(urla("save", relationship["id"]), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>ID<br /><input type=\"text\" name=\"relationship[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["id"]);
  responsebody += QLatin1String("\" readonly=\"readonly\" /></label>\n  </p>\n  <p>\n    <label>D ID<br /><input type=\"text\" name=\"relationship[dId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["dId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Device Name<br /><input type=\"text\" name=\"relationship[deviceName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["deviceName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>S ID<br /><input type=\"text\" name=\"relationship[sId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["sId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Service Name<br /><input type=\"text\" name=\"relationship[serviceName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["serviceName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Anonymity Method<br /><input type=\"text\" name=\"relationship[anonymityMethod]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["anonymityMethod"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Privacy Standard<br /><input type=\"text\" name=\"relationship[privacyStandard]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["privacyStandard"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Interval<br /><input type=\"text\" name=\"relationship[interval]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["interval"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Location<br /><input type=\"text\" name=\"relationship[location]\" value=\"");
  responsebody += THttpUtility::htmlEscape(relationship["location"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Save\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Show", urla("show", relationship["id"]))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(relationship_saveView)

#include "relationship_saveView.moc"
