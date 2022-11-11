#ifndef OUTLINEWIDTH
#define OUTLINEWIDTH 20
#endif

#include "arc.h"

#include <qmath.h>
#include <QMessageBox>
#include <QDebug>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;
static double ArcSize = 10.0;
static double ArcAngle = 1.18;//Pi/3;

const QColor Arc::defalut_brushColor=Qt::white;
const QColor Arc::defalut_penColor=Qt::black;

Arc::Arc(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
         QString TargetId, QPainterPath arc_path, const QString &ArcId,int ArcWeight)
{
    sourceItem = SourceItem;
    targetItem = TargetItem;
    setPath(arc_path);
    source_id = SourceId;
    target_id = TargetId;
    id = ArcId;

    weight = ArcWeight;

    createArc();
}

Arc::Arc(QGraphicsItem * item1, QGraphicsItem * item2,
     QPainterPath paintpath, const ARC_ATTR &arc)
    : QGraphicsPathItem()
{
    sourceItem = item1;
    targetItem = item2;
    setPath(paintpath);
    source_id = arc.source;
    target_id = arc.target;
    weight = arc.weight;
    id = arc.id;
    m_brushColor = arc.brushColor;
    m_penColor = arc.penColor;

    createArc();
    updatePosition();
}

Arc::Arc(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
         QString TargetId, const QString &ArcId,int ArcWeight)
{
    sourceItem = SourceItem;
    targetItem = TargetItem;
    source_id = SourceId;
    target_id = TargetId;
    id = ArcId;
    weight = ArcWeight;

    createArc();
}

void Arc::createArc()
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

/* to XML */
ARC_ATTR Arc::toXml() const
{
    ARC_ATTR arc;
    arc.id = id;
    arc.source = source_id;
    arc.target = target_id;
    arc.weight = weight;
    arc.brushColor = m_brushColor;
    arc.penColor = m_penColor;
//	//this place update for weight from double to QString by syx 8.15

    for(int i = 1; i < path().elementCount()-1; i++ )
        arc.points << path().elementAt(i);

    return arc;
}

Arc::~Arc()
{
    delete label;

    foreach(ArcEdgeSelectionRectangle * rect, rects)
        delete rect;
}

/* get Id */
QString Arc::getId()
{
    return id;
}

/* get weight */
int Arc::getWeight() const
{
    return weight;
}

void Arc::setWeight(int ArcWeight)
{
    weight=ArcWeight;
}

void Arc::setLabel()
{
    QVariant value(weight);
    label->setText( QString("%1").arg(value.toString()) );
}
/* source item */
QGraphicsItem * Arc::getSourceItem() const
{
    return sourceItem;
}

/* target item */
QGraphicsItem * Arc::getTargetItem() const
{
    return targetItem;
}

/* show rects */
void Arc::showRects(bool show)
{
    foreach(ArcEdgeSelectionRectangle * rec, rects)
        rec->setVisible(show);
}

/* update position */
void Arc::updatePosition()
{
    QPointF sourcePoint = mapFromItem(sourceItem, sourceItem->boundingRect().center());
    QPointF targetPoint = mapFromItem(targetItem, targetItem->boundingRect().center());

    QPainterPath ArcPath = path();
    ArcPath.setElementPositionAt (0, sourcePoint.x(), sourcePoint.y());
    ArcPath.setElementPositionAt (ArcPath.elementCount()-1, targetPoint.x(), targetPoint.y());//PointerPath的index从0开始
    setPath(ArcPath);
}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* @@@@@@ reimplemented functions @@@@@@ */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

int Arc::type () const
{
    return Type;
}

QPainterPath Arc::shape() const
{
    QPainterPath arcShapeOutput = path();
    arcShapeOutput.addPolygon(ArcHead);
    QPainterPathStroker painterPathStroker;
    painterPathStroker.setWidth(OUTLINEWIDTH);
    arcShapeOutput = painterPathStroker.createStroke(arcShapeOutput);
    return arcShapeOutput;
}

QRectF Arc::boundingRect() const
{
    qreal a = (pen().width())/2 + ArcSize/2;
    return QRectF( path().controlPointRect() )
           .normalized()
           .adjusted(-a, -a, a, a);
}

QColor Arc::getBrushColor() const
{
    return m_brushColor;
}

QColor Arc::getPenColor() const
{
    return m_penColor;
}

void Arc::setBrushColor(QColor color)
{
    m_brushColor = color;
    update();
}

void Arc::setPenColor(QColor color)
{
    m_penColor = color;
    update();
}

void Arc::paint ( QPainter * painter,
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
    if(targetItem->type() == QGraphicsItem::UserType+1)//目标点为库所
       head_point = intersectionWithPlace(targetItem, &lastLine);
    else if(targetItem->type()==QGraphicsItem::UserType+2)//目标点为变迁
       head_point = intersectionWithTransition(targetItem, &lastLine);

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
      color = m_penColor;
    }

    // drawing Arc line
    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(paintPath);

    // drawing Arc head
    painter->setBrush(color);
    painter->drawPolygon(ArcHead);

    // drawing label
    QVariant v(weight);
    label->setText( QString("%1").arg(v.toString()) );
    label->setPos(paintPath.pointAtPercent(0.5) + QPointF(-10,0));
    label->setBrush(color);

     if(weight == 1.0)
       label->hide();
     else
       label->show();

    setPath(paintPath);
}

/* intersection Arc-circle */
QPointF Arc::intersectionWithPlace(QGraphicsItem * circle, QLineF * line) const
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

/* intersection Arc-Transition */
QPointF Arc::intersectionWithTransition(QGraphicsItem * rectangle, QLineF * line) const
{
    QPointF point, intersectPoint;
    QList<QLineF> list;

    QPainterPath shape = rectangle->mapToScene(rectangle->shape());
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
        if(line->intersect(l, &intersectPoint ) == QLineF::BoundedIntersection)
            point = intersectPoint;

    return point;
}

//zyc
//void Arc::createRuleSet()
//{
//		//m_ruleSet.clearRuleSet();
//	vector<vector<FuzzySet>> vvfuzSet;
//	int variableCount = m_FIS.m_vVariableName.size();
//	for (int i = 0; i < variableCount; i++)
//	{
//		vector<FuzzySet> vtempSet;
//		int linguisticCount = m_FIS.m_vvLinguisticName[i].size();
//		for (int j = 0; j < linguisticCount; j++)
//		{
//			double temp1 = m_FIS.m_vvPara1[i][j];
//			double temp2 = m_FIS.m_vvPara2[i][j];
//			double temp3 = m_FIS.m_vvPara3[i][j];
//			//TriangleMemberFunction temp(temp1, temp2, temp3);
//            FuzzySet tempSet;
//            if(m_FIS.m_vvLinguisticType[i][j]==0)
//            {
//                TriangleMemberFunction *temp = new TriangleMemberFunction(temp1, temp2, temp3);
//                tempSet.setMemberFunction(temp,0);
//            }
//            else
//            {
//                GaussMemberFunction *temp = new GaussMemberFunction(temp1, temp2, temp3);
//                tempSet.setMemberFunction(temp,1);
//            }
//            //FuzzySet tempSet;
//            //tempSet.setMemberFunction(temp);
//			vtempSet.push_back(tempSet);
//		}
//		vvfuzSet.push_back(vtempSet);
//	}
//	int ruleCount = m_FIS.m_vvRules.size();
//	RuleSet tempSet(ruleCount);
//	for (int i = 0; i < ruleCount; i++)
//	{
//		Rule tempRule(variableCount-1);
//		for (int j = 0; j < variableCount - 1; j++)
//		{
//			int tempVariable = m_FIS.m_vNewSortedVariables[j];
//			int tempTerm = m_FIS.m_vvRules[i][tempVariable];
//			tempRule.addCondFuzzySet(vvfuzSet[tempVariable][tempTerm]);
//		}
//		int tempVariable = m_FIS.m_vNewSortedVariables[variableCount - 1];
//		int tempTerm = m_FIS.m_vvRules[i][tempVariable];
//		tempRule.registerResultFuzzySet(vvfuzSet[tempVariable][tempTerm], m_FIS.m_vvLinguisticName[tempVariable][tempTerm]);
//		tempSet.addRule(tempRule);
//	}
//	m_ruleSet.copyObject(tempSet);
//}
