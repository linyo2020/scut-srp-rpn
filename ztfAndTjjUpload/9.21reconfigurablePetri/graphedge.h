#ifndef __GRAPHEDGE_H
#define __GRAPHEDGE_H

#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsSimpleTextItem>
#include <QPolygonF>

#include "defs.h"

class GraphEdge : public QGraphicsPathItem
{

 public:
    enum { Type = UserType + 7 };
    GraphEdge(QGraphicsItem * start, QGraphicsItem * target,
              const QString &text, QPainterPath & p,
              const QPointF &lxy, int indx);
    ~GraphEdge();

    void updatePosition();
        QPointF intersectionPoint (const QLineF &line) const;
    int getIndex();
    QGraphicsItem * getSourceNode();
    QGraphicsItem * getTargetNode();

    int type () const;
    QRectF boundingRect() const;
    QPainterPath shape () const;

 protected:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option,
        QWidget * widget );

 private:

    QGraphicsSimpleTextItem * label;
    QGraphicsItem * sourceNode;
    QGraphicsItem * targetNode;
    QPolygonF edgeHead;
    int index;
};

#endif
