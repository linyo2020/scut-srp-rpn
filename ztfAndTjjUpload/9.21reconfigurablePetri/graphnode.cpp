#include "graphnode.h"

GraphNode::GraphNode(int node_index, const QList<NODELABEL> &M, float width, float height)
    :QGraphicsEllipseItem()
{
  index = node_index;
  marking = M;
  ht = height;
  wd = width;

  setPen(Qt::NoPen);
  setZValue(1000.0);
  setFlag(QGraphicsItem::ItemIsMovable, false);
  setFlag(QGraphicsItem::ItemIsSelectable, false);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

  label = new QGraphicsSimpleTextItem(this);
  createLabelText();
}

/* set node label text */
void GraphNode::createLabelText()
{
  QVariant v(index);
  QString text(QString("M%1").arg(v.toString()));
  label->setText(text);
  text.append(" = (");

  foreach(NODELABEL ndlabel, marking)
  {
     if(ndlabel.mark == omega)
        text.append(QObject::trUtf8("\u0277")+",");
     else
      {
        v.setValue(ndlabel.mark);
        text.append(v.toString()+",");
      }
  }

  text.remove(text.count()-1, 2);
  text.append(")\n");

  int l = text.count();
  for(int i=0; i<l+2; i++)
      text.append("--");

  text.append("\n *(");

  for(int i = 0; i <marking.size(); i++)
   {
     text.append(marking[i].name+",");
   }

  text.remove(text.count()-1, 2);
  text.append(")");
  setToolTip(text);

  label->setPos(wd/2 - label->boundingRect().width()/2,
                ht/2 - label->boundingRect().height()/2);
}

GraphNode::~GraphNode()
{
  delete label;
}

/* add in edge */
void GraphNode::addInEdge(GraphEdge * edge)
{
  inedges << edge;
}

/* add out edge */
void GraphNode::addOutEdge(GraphEdge * edge)
{
  outedges << edge;
}

/* remove in edge */
void GraphNode::removeInEdge(int index)
{
  for(int i=0; i < inedges.size(); i++)
     if(inedges[i]->getIndex() == index)
      {
        inedges.removeAt(i);
            return;
      }
}

/* remove out edge */
void GraphNode::removeOutEdge(int index)
{
  for(int i=0; i < outedges.size(); i++)
     if(outedges[i]->getIndex() == index)
      {
        outedges.removeAt(i);
            return;
      }
}

/* return index */
int GraphNode::getIndex()
{
  return index;
}

/* type */
int GraphNode::type () const
{
  return Type;
}

/* bounding rect */
QRectF GraphNode::boundingRect() const
{
    qreal a = (pen().width())/2;
  return QRectF(-1, -1, wd, ht)
     .normalized()
     .adjusted(-a, -a, a, a);
}

/* shape */
QPainterPath GraphNode::shape () const
{
     QPainterPath shape;
     shape.addRect(-1, -1,wd, ht);
     return shape;
}

/* item change */
QVariant GraphNode::itemChange (GraphicsItemChange change, const QVariant &value)
{
  Q_UNUSED(change);
/*
  foreach(GraphEdge * edge, inedges)
    edge->updatePosition();
  foreach(GraphEdge * edge, outedges)
    edge->updatePosition();
*/
  return value;
}

/* paint */
void GraphNode::paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget )
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

    QColor color;
    if(index == 0)
    {
        color = Qt::darkGreen;
        painter->setBrush(QColor(240, 255, 240));
        painter->setPen (QPen(color, 2, Qt::SolidLine,
                              Qt::RoundCap, Qt::MiterJoin));
    }
    else
    {
        color = Qt::black;
        painter->setBrush(Qt::white);
        painter->setPen (QPen(color, 1, Qt::SolidLine,
                              Qt::RoundCap, Qt::MiterJoin));
    }
    if(outedges.isEmpty())
    {
        color = Qt::darkRed;
        painter->setBrush(QColor(255, 240, 240));
        painter->setPen (QPen(color, 2, Qt::SolidLine,
                              Qt::RoundCap, Qt::MiterJoin));
    }

  label->setBrush(color);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawEllipse(0, 0, wd, ht);
}

