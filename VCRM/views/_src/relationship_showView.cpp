#include <QtCore>
#include <TreeFrogView>
#include "relationship.h" 
#include "applicationhelper.h"
#include "curlhelper.h"
#include "xmlhelper.h"

class T_VIEW_EXPORT relationship_showView : public TActionView
{
  Q_OBJECT
public:
  relationship_showView() : TActionView() { }
  QString toString();
};

QString relationship_showView::toString()
{
  responsebody.reserve(2372);
  responsebody += QLatin1String("<!DOCTYPE html>\n");
    tfetch(Relationship, relationship);
  responsebody += QLatin1String("<html>\n<head>\n  <meta charset=\"UTF-8\">\n  <title>");
  responsebody += THttpUtility::htmlEscape(controller()->name() + ": " + controller()->activeAction());
  responsebody += QLatin1String("</title>\n</head>\n<body>\n<p style=\"color: red\">");
  tehex(error);
  responsebody += QLatin1String("</p>\n<p style=\"color: green\">");
  tehex(notice);
  responsebody += QLatin1String("</p>\n\n<h1>Showing Relationship</h1>\n<dt>ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.id());
  responsebody += QLatin1String("</dd><br />\n<dt>Created at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.createdAt());
  responsebody += QLatin1String("</dd><br />\n<dt>Updated at</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.updatedAt());
  responsebody += QLatin1String("</dd><br />\n<dt>D ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.dId());
  responsebody += QLatin1String("</dd><br />\n<dt>Device Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.deviceName());
  responsebody += QLatin1String("</dd><br />\n<dt>S ID</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.sId());
  responsebody += QLatin1String("</dd><br />\n<dt>Service Name</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.serviceName());
  responsebody += QLatin1String("</dd><br />\n<dt>Anonymity Method</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.anonymityMethod());
  responsebody += QLatin1String("</dd><br />\n<dt>Privacy Standard</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.privacyStandard());
  responsebody += QLatin1String("</dd><br />\n<dt>Interval</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.interval());
  responsebody += QLatin1String("</dd><br />\n<dt>Location</dt><dd>");
  responsebody += THttpUtility::htmlEscape(relationship.location());
  responsebody += QLatin1String("</dd><br />\n\n");
  responsebody += QVariant(linkTo("Edit", urla("save", relationship.id()))).toString();
  responsebody += QLatin1String(" |\n");
  responsebody += QVariant(linkTo("Back", urla("index"))).toString();
  responsebody += QLatin1String("\n\n</body>\n</html>\n");

  return responsebody;
}

T_DEFINE_VIEW(relationship_showView)

#include "relationship_showView.moc"
