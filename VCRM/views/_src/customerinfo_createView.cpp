#include <QtCore>
#include <TreeFrogView>
#include "customerinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT customerinfo_createView : public TActionView
{
  Q_OBJECT
public:
  customerinfo_createView() : TActionView() { }
  QString toString();
};

QString customerinfo_createView::toString()
{
  responsebody.reserve(2119);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, customerInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>New Customer Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("create"), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>L ID<br /><input name=\"customerInfo[lId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["lId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Last Name<br /><input name=\"customerInfo[lastName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["lastName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>First Name<br /><input name=\"customerInfo[firstName]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["firstName"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Birthday<br /><input name=\"customerInfo[birthday]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["birthday"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>E Mail Addr<br /><input name=\"customerInfo[eMailAddr]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["eMailAddr"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Phone Num<br /><input name=\"customerInfo[phoneNum]\" value=\"");
  responsebody += THttpUtility::htmlEscape(customerInfo["phoneNum"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Create\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(customerinfo_createView)

#include "customerinfo_createView.moc"
