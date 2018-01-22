#include <QtCore>
#include <TreeFrogView>
#include "venderinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT venderinfo_showView : public TActionView
{
  Q_OBJECT
public:
  venderinfo_showView() : TActionView() { }
  QString toString();
};

QString venderinfo_showView::toString()
{
  responsebody.reserve(1755);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(VenderInfo, venderInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Vender Info</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>L ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.lId());
  responsebody += QLatin1String("</dd><br />\n<dt>Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.name());
  responsebody += QLatin1String("</dd><br />\n<dt>Phone Num</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.phoneNum());
  responsebody += QLatin1String("</dd><br />\n<dt>E Mail Addr</dt><dd>");
  responsebody += THttpUtility::htmlEscape(venderInfo.eMailAddr());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", venderInfo.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(venderinfo_showView)

#include "venderinfo_showView.moc"
