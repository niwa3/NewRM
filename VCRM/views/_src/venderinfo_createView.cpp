#include <QtCore>
#include <TreeFrogView>
#include "venderinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT venderinfo_createView : public TActionView
{
  Q_OBJECT
public:
  venderinfo_createView() : TActionView() { }
  QString toString();
};

QString venderinfo_createView::toString()
{
  responsebody.reserve(1664);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, venderInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>New Vender Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("create"), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>L ID<br /><input name=\"venderInfo[lId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["lId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Name<br /><input name=\"venderInfo[name]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["name"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Phone Num<br /><input name=\"venderInfo[phoneNum]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["phoneNum"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>E Mail Addr<br /><input name=\"venderInfo[eMailAddr]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["eMailAddr"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Create\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(venderinfo_createView)

#include "venderinfo_createView.moc"
