#include <QtCore>
#include <TreeFrogView>
#include "venderinfo.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT venderinfo_saveView : public TActionView
{
  Q_OBJECT
public:
  venderinfo_saveView() : TActionView() { }
  QString toString();
};

QString venderinfo_saveView::toString()
{
  responsebody.reserve(2087);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(QVariantMap, venderInfo);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Editing Vender Info</h1>\n\n");
  responsebody += QVariant(formTag(urla("save", venderInfo["id"]), Tf::Post)).toString();
  responsebody += QLatin1String("\n  <p>\n    <label>ID<br /><input type=\"text\" name=\"venderInfo[id]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["id"]);
  responsebody += QLatin1String("\" readonly=\"readonly\" /></label>\n  </p>\n  <p>\n    <label>L ID<br /><input type=\"text\" name=\"venderInfo[lId]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["lId"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Name<br /><input type=\"text\" name=\"venderInfo[name]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["name"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>Phone Num<br /><input type=\"text\" name=\"venderInfo[phoneNum]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["phoneNum"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <label>E Mail Addr<br /><input type=\"text\" name=\"venderInfo[eMailAddr]\" value=\"");
  responsebody += THttpUtility::htmlEscape(venderInfo["eMailAddr"]);
  responsebody += QLatin1String("\" /></label>\n  </p>\n  <p>\n    <input type=\"submit\" value=\"Save\" />\n  </p>\n</form>\n\n");
  responsebody += QVariant(linkTo("Show", urla("show", venderInfo["id"]))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(venderinfo_saveView)

#include "venderinfo_saveView.moc"
