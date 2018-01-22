#include <QtCore>
#include <TreeFrogView>
#include "logininfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT logininfo_saveView : public TActionView
{
  Q_OBJECT
public:
  logininfo_saveView() : TActionView() { }
  QString toString();
};

QString logininfo_saveView::toString()
{
  responsebody.reserve(2067);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, loginInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Editing Login Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("save", loginInfo["id"]), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>ID<br /><input type=\"text\" name=\"loginInfo[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["id"]);
  responsebody += QLatin1String("\" readonly=\"readonly\" /></label>\n  </p>\n  <p>\n    <label>Login<br /><input type=\"text\" name=\"loginInfo[login]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["login"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Passwd<br /><input type=\"text\" name=\"loginInfo[passwd]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["passwd"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Salt<br /><input type=\"text\" name=\"loginInfo[salt]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["salt"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>User Type<br /><input type=\"text\" name=\"loginInfo[userType]\" value=\"");
  responsebody += THttpUtility::htmlEscape(loginInfo["userType"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Save\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Show", urla("show", loginInfo["id"]))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(logininfo_saveView)

#include "logininfo_saveView.moc"
