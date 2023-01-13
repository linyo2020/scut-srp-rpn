#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>

#include "arcedgeselectionrectangle.h"

#include "defs.h"

class Connector : public QGraphicsPathItem
{
 public:

    enum { Type = UserType + 4 };

    Connector(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
        QString TargetId, QPainterPath arc_path, const QString &ConnectorId);

    ~Connector();

    void createArc();
    CONNECTOR_ATTR toXml() const;

    void updatePosition();
    void showRects(bool show);

    QString getId();
    void setID(QString id);
    void setsourceId(QString id);
    void setTargetId(QString id);
    QString getSourceId();
    QString getTargetId();

    void setLabel();

    QGraphicsItem * getSourceItem() const;
    QGraphicsItem * getTargetItem() const;

    int type () const;
    QPainterPath shape() const;
    QRectF boundingRect() const;

    void setSourceItem(QGraphicsItem*it);
    void setTargetItem(QGraphicsItem*it);

 protected:

    void paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option,
    QWidget * widget );

 private:

    QString id;
    QString source_id;
    QString target_id;

    QColor color;

    QPolygonF ArcHead;
    QGraphicsSimpleTextItem* label;

    QList<ArcEdgeSelectionRectangle *> rects;

    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;


    QPointF intersectionWithPlace(QGraphicsItem * circle, QLineF * line) const;
    QPointF intersectionWithTransition(QGraphicsItem * rectangle, QLineF * line) const;
};


#endif // CONNECTOR_H
