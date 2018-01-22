#include <QtCore>
#include <TreeFrogView>
#include "logininfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT logininfo_createView : public TActionView
{
  Q_OBJECT
public:
  logininfo_createView() : TActionView() { }
  QString toString();
};

QString logininfo_createView::toString()
{
  responsebody.reserve(1648);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, loginInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>New Login Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("create"), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>Login<br /><input name=\"loginInfo[login]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["login"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Passwd<br /><input name=\"loginInfo[passwd]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["passwd"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Salt<br /><input name=\"loginInfo[salt]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["salt"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>User Type<br /><input name=\"loginInfo[userType]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["userType"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Create\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(logininfo_createView)

#include "logininfo_createView.moc"
