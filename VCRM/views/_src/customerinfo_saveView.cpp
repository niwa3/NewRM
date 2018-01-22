#include <QtCore>
#include <TreeFrogView>
#include "customerinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT customerinfo_saveView : public TActionView
{
  Q_OBJECT
public:
  customerinfo_saveView() : TActionView() { }
  QString toString();
};

QString customerinfo_saveView::toString()
{
  responsebody.reserve(2578);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, customerInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Editing Customer Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("save", customerInfo["id"]), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>ID<br /><input type=\"text\" name=\"customerInfo[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["id"]);
  responsebody += QLatin1String("\" readonly=\"readonly\" /></label>\n  </p>\n  <p>\n    <label>L ID<br /><input type=\"text\" name=\"customerInfo[lId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["lId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Last Name<br /><input type=\"text\" name=\"customerInfo[lastName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["lastName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>First Name<br /><input type=\"text\" name=\"customerInfo[firstName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["firstName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Birthday<br /><input type=\"text\" name=\"customerInfo[birthday]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["birthday"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>E Mail Addr<br /><input type=\"text\" name=\"customerInfo[eMailAddr]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["eMailAddr"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Phone Num<br /><input type=\"text\" name=\"customerInfo[phoneNum]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["phoneNum"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Save\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Show", urla("show", customerInfo["id"]))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(customerinfo_saveView)

#include "customerinfo_saveView.moc"
