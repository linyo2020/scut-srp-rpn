#include "graphedge.h"
#include <qmath.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
static double headSize = 10.0;
static double headAngle = 1.18;//Pi/3;

GraphEdge::GraphEdge(QGraphicsItem * start,
    QGraphicsItem * target, const QString &text,
              QPainterPath & p, const QPointF &lxy, int indx)
    :QGraphicsPathItem()
{
  sourceNode  = start;
  targetNode = target;
  index = indx;

  setZValue(-1000.0);
  setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

  label = new QGraphicsSimpleTextItem(this);
  label->setFlags(QGraphicsItem::ItemIsMovable|
        QGraphicsItem::ItemIsSelectable);
  label->setText(text);
  label->setPos(mapFromScene(lxy));// - QPointF(5, 0));
  setPath(p);
}

GraphEdge::~GraphEdge()
{
  delete label;
}

/* get index */
int GraphEdge::getIndex()
{
  return index;
}

/* update Position */
void GraphEdge::updatePosition()
{
/*QPainterPath pth = path();
  QPointF p1 = mapFromItem(sourceNode, sourceNode->boundingRect().center());
  pth.setElementPositionAt(0, p1.x(), p1.y());
  QPointF p2 = mapFromItem(targetNode, targetNode->boundingRect().center());
  pth.setElementPositionAt(pth.elementCount()-1, p2.x(), p2.y());
  setPath(pth);*/
}

/* Get sourceNode */
QGraphicsItem * GraphEdge::getSourceNode()
{
  return sourceNode;
}

/* Get targetNode */
QGraphicsItem * GraphEdge::getTargetNode()
{
  return targetNode;
}

/* type */
int GraphEdge::type () const
{
  return Type;
}

/* boundingRect */
QRectF GraphEdge::boundingRect() const
{
  qreal a = (pen().width())/2 + headSize/2;
  return path().boundingRect()
        .normalized()
        .adjusted(-a, -a, a, a);
}

/* shape */
QPainterPath GraphEdge::shape () const
{
  QPainterPath path = QGraphicsPathItem::shape();
  path.addPolygon(edgeHead);
  return path;
}

/* paint */
void GraphEdge::paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget )
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

  QPainterPath pth = path();
  QLineF edgeLine(pth.elementAt(pth.elementCount()-2), pth.pointAtPercent(1));
  QPointF p0 = intersectionPoint(edgeLine);

 //construct the edge head
 double angle = qAcos(edgeLine.dx() / edgeLine.length());

 if (edgeLine.dy() >= 0)
        angle = TwoPi - angle;

 QPointF p1 = p0 + QPointF(qSin(angle - headAngle) * headSize,
        qCos(angle - headAngle) * headSize);
 QPointF p3 = p0 + QPointF(qSin(angle - Pi + headAngle) * headSize,
        qCos(angle - Pi + headAngle) * headSize);

 QLineF l(p0.x(), p0.y(), edgeLine.x1(), edgeLine.y1());
 QPointF p2 = l.pointAt(5/l.length());
 edgeHead.clear();
 edgeHead << p0 << p1 << p2 << p3;

  label->setBrush(Qt::black);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(QPen(Qt::black, 1, Qt::SolidLine,
        Qt::RoundCap, Qt::MiterJoin));
  painter->setBrush(Qt::NoBrush);
  painter->drawPath(path());

  painter->setBrush(Qt::black);
  painter->drawPolygon(edgeHead);
}

/* intersection edge-node */
QPointF GraphEdge::intersectionPoint(const QLineF &line) const
{
    QPointF point, intersectPoint;
    QList<QLineF> list;

    QPainterPath shape = targetNode->mapToScene(targetNode->shape());
    QLineF line5(shape.elementAt(0).x, shape.elementAt(0).y,
            shape.elementAt(1).x, shape.elementAt(1).y);
    QLineF line6(shape.elementAt(1).x, shape.elementAt(1).y,
            shape.elementAt(2).x, shape.elementAt(2).y);
    QLineF line7(shape.elementAt(2).x, shape.elementAt(2).y,
            shape.elementAt(3).x, shape.elementAt(3).y);
    QLineF line8(shape.elementAt(3).x, shape.elementAt(3).y,
            shape.elementAt(4).x, shape.elementAt(4).y);

    list<<line5<<line6<<line7<<line8;

    foreach(QLineF l,list)
    if(line.intersect(l, &intersectPoint ) == QLineF::BoundedIntersection)
        point = intersectPoint;

 return point;
}
