#include <QtCore>
#include <TreeFrogView>
#include "logininfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT logininfo_showView : public TActionView
{
  Q_OBJECT
public:
  logininfo_showView() : TActionView() { }
  QString toString();
};

QString logininfo_showView::toString()
{
  responsebody.reserve(1739);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(LoginInfo, loginInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Login Info</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Login</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.login());
  responsebody += QLatin1String("</dd><br />\n<dt>Passwd</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.passwd());
  responsebody += QLatin1String("</dd><br />\n<dt>Salt</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.salt());
  responsebody += QLatin1String("</dd><br />\n<dt>User Type</dt><dd>");
  responsebody += THttpUtility::htmlEscape(loginInfo.userType());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", loginInfo.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(logininfo_showView)

#include "logininfo_showView.moc"
