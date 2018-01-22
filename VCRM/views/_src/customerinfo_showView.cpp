#include <QtCore>
#include <TreeFrogView>
#include "customerinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT customerinfo_showView : public TActionView
{
  Q_OBJECT
public:
  customerinfo_showView() : TActionView() { }
  QString toString();
};

QString customerinfo_showView::toString()
{
  responsebody.reserve(2069);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(CustomerInfo, customerInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Customer Info</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>L ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.lId());
  responsebody += QLatin1String("</dd><br />\n<dt>Last Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.lastName());
  responsebody += QLatin1String("</dd><br />\n<dt>First Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.firstName());
  responsebody += QLatin1String("</dd><br />\n<dt>Birthday</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.birthday());
  responsebody += QLatin1String("</dd><br />\n<dt>E Mail Addr</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.eMailAddr());
  responsebody += QLatin1String("</dd><br />\n<dt>Phone Num</dt><dd>");
  responsebody += THttpUtility::htmlEscape(customerInfo.phoneNum());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", customerInfo.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(customerinfo_showView)

#include "customerinfo_showView.moc"
