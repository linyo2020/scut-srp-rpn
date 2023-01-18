#include "connector.h"
#include <qmath.h>
#include <QMessageBox>
#include <QDebug>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
static double ArcSize = 10.0;
static double ArcAngle = 1.18;//Pi/3;
Connector::Connector(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
         QString TargetId, QPainterPath arc_path, const QString &ConnectorId)
{
    sourceItem = SourceItem;
    targetItem = TargetItem;
    setPath(arc_path);
    source_id = SourceId;
    target_id = TargetId;
    id = ConnectorId;
    createArc();
}
Connector::Connector(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
                     QString TargetId, const QString &ConnectorId)
{
    sourceItem = SourceItem;
    targetItem = TargetItem;
    source_id = SourceId;
    target_id = TargetId;
    id = ConnectorId;

    createArc();
}
Connector::Connector(QGraphicsItem * item1, QGraphicsItem * item2,
     QPainterPath paintpath, const CONNECTOR_ATTR &connector)
{
    sourceItem = item1;
    targetItem = item2;
    setPath(paintpath);
    source_id = connector.source;
    target_id = connector.target;
    id = connector.id;

    createArc();
    updatePosition();
}
void Connector::createArc()
{
    setZValue(-1000.0);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setSelected(true);

    for(int counter = 1; counter < path().elementCount()-1; counter++ )
     {
        ArcEdgeSelectionRectangle * rec = new ArcEdgeSelectionRectangle(this,7.0);
        rec->setPos(path().elementAt(counter).x - 7/2, path().elementAt(counter).y - 7/2);
        rects << rec;
     }

    label = new QGraphicsSimpleTextItem(this);
}
void Connector::paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option,
        QWidget * widget=Q_NULLPTR )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(sourceItem->collidesWithItem(targetItem, Qt::IntersectsItemShape))
        return;

    QPainterPath paintPath = path();
    int elements = paintPath.elementCount();
    QPointF head_point;

    QLineF lastLine(paintPath.elementAt(elements-2).x, paintPath.elementAt(elements-2).y,
        paintPath.elementAt(elements-1).x, paintPath.elementAt(elements-1).y);//最后一小段弧

    //！！后续迭代注意更新
       head_point = intersectionWithPlace(targetItem, &lastLine);

    int elementIndexCounter = 1;//此弧中每一小段弧的尾部索引
    foreach(ArcEdgeSelectionRectangle * rec, rects)
    {
       QPointF currentEdgeEndPoint = mapFromItem(rec, rec->boundingRect().center());
       paintPath.setElementPositionAt(elementIndexCounter, currentEdgeEndPoint.x(),
                                      currentEdgeEndPoint.y());
       elementIndexCounter++;
    }

    //construct the Arc head
    double angle = qAcos(lastLine.dx() / lastLine.length());

    if (lastLine.dy() >= 0)
           angle = TwoPi - angle;
    //画端点箭头
    QPointF p1 = head_point +
       QPointF(qSin(angle - ArcAngle) * ArcSize,
           qCos(angle - ArcAngle) * ArcSize);
    QPointF p3 = head_point +
       QPointF(qSin(angle - Pi + ArcAngle) * ArcSize,
           qCos(angle - Pi + ArcAngle) * ArcSize);

    QLineF l(head_point.x(), head_point.y(),
           lastLine.x1(), lastLine.y1());
    QPointF p2 = l.pointAt(5/l.length());
    ArcHead.clear();
    ArcHead << head_point << p1 << p2 << p3;

    if(isSelected())
    {
      showRects(true);
      color = QColor(0, 0, 150);
    }
    else
    {
      showRects(false);
      color = Qt::green;
    }

    // drawing Arc line
    painter->setPen(QPen(color, 5, Qt::DashLine, Qt::RoundCap, Qt::MiterJoin));
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(paintPath);

    // drawing Arc head
    painter->setBrush(color);
    painter->drawPolygon(ArcHead);

    // drawing label
    label->setText( QString("%1").arg(id) );
    label->setPos(paintPath.pointAtPercent(0.5) + QPointF(-10,0));
    label->setBrush(color);
    setPath(paintPath);
}
void Connector::updatePosition()
{
    QPointF sourcePoint = mapFromItem(sourceItem, sourceItem->boundingRect().center());
    QPointF targetPoint = mapFromItem(targetItem, targetItem->boundingRect().center());

    QPainterPath ArcPath = path();
    ArcPath.setElementPositionAt (0, sourcePoint.x(), sourcePoint.y());
    ArcPath.setElementPositionAt (ArcPath.elementCount()-1, targetPoint.x(), targetPoint.y());//PointerPath的index从0开始
    setPath(ArcPath);
}
QPointF Connector::intersectionWithPlace(QGraphicsItem * circle, QLineF * line) const
{
    qreal R = 15;

    qreal x0 = (circle->mapToScene(circle->shape().controlPointRect().center())).x();
    qreal y0 = (circle->mapToScene(circle->shape().controlPointRect().center())).y();

 if(line->x2() != line->x1()) // not vertical
  {
    QPointF yaxis_intersection;
    line->intersect( QLineF(QPointF(0, 10000), QPointF(0, -10000)), &yaxis_intersection);//取得与y轴交点

    qreal a = (line->y2() - line->y1())/(line->x2() - line->x1());
    qreal b = yaxis_intersection.y();

    qreal A = 1 + a*a;
    qreal B = 2*(a*b - a*y0 - x0);
    qreal C = x0 * x0 + y0*y0 + b*b - 2*b*y0 - R*R;

    // Q > 0
    qreal Q = B*B - 4*A*C;
       qreal s1 = (-1)*(B + sqrt(Q))/(2*A);
       qreal s2 = (sqrt(Q) - B)/(2*A);
       QPointF ps1(s1, a*s1 + b);
       QPointF ps2(s2, a*s2 + b);

    if(QLineF(line->p1(), ps1).length()
        <= QLineF(line->p1(), ps2).length())
     return ps1;
    else
     return ps2;
   }
  else
   {
     // y*y - 2*y0*y + (x - x0)*(x - x0) + y0*y0 - R*R = 0
     qreal x = line->x1();
     qreal C = (x - x0)*(x - x0) + y0*y0 - R*R;
     qreal Q = 4*y0*y0 - 4*C;
       qreal s1 = y0 - sqrt(Q)/2;
       qreal s2 = y0 + sqrt(Q)/2 ;
       QPointF ps1(x, s1);
       QPointF ps2(x, s2);

    if(QLineF(line->p1(), ps1).length()
        <= QLineF(line->p1(), ps2).length())
     return ps1;
    else
     return ps2;

   }
}
/* show rects */
void Connector::showRects(bool show)
{
    foreach(ArcEdgeSelectionRectangle * rec, rects)
        rec->setVisible(show);
}
/* get Id */
QString Connector::getId()
{
    return id;
}

void Connector::setID(QString id)
{
    this->id=id;
}

void Connector::setsourceId(QString id)
{
    this->source_id=id;
}

void Connector::setTargetId(QString id)
{
    this->target_id=id;
}

QString Connector::getSourceId()
{
    return this->source_id;
}

QString Connector::getTargetId()
{
    return this->target_id;
}
void Connector::setLabel()
{
    label->setText( QString("c%1").arg(id));
}
/* source item */
QGraphicsItem * Connector::getSourceItem() const
{
    return sourceItem;
}

/* target item */
QGraphicsItem * Connector::getTargetItem() const
{
    return targetItem;
}
int Connector::type () const
{
    return Type;
}

QPainterPath Connector::shape() const
{
    QPainterPath arcShapeOutput = path();
    arcShapeOutput.addPolygon(ArcHead);
    QPainterPathStroker painterPathStroker;
    painterPathStroker.setWidth(20);
    arcShapeOutput = painterPathStroker.createStroke(arcShapeOutput);
    return arcShapeOutput;
}

QRectF Connector::boundingRect() const
{
    qreal a = (pen().width())/2 + ArcSize/2;
    return QRectF( path().controlPointRect() )
           .normalized()
            .adjusted(-a, -a, a, a);
}
void Connector::setSourceItem(QGraphicsItem *it)
{
    this->sourceItem=it;
}

void Connector::setTargetItem(QGraphicsItem *it)
{
    this->targetItem=it;
}
Connector::~Connector()
{
    delete label;

    foreach(ArcEdgeSelectionRectangle * rect, rects)
        delete rect;
}
/* to XML */
CONNECTOR_ATTR Connector::toXml() const
{
    CONNECTOR_ATTR connector;
    connector.id = id;
    connector.source = source_id;
    connector.target = target_id;
//	//this place update for weight from double to QString by syx 8.15

    for(int i = 1; i < path().elementCount()-1; i++ )
        connector.points << path().elementAt(i);

    return connector;
}
