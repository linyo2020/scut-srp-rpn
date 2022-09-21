#include "arcedgeselectionrectangle.h"

ArcEdgeSelectionRectangle::ArcEdgeSelectionRectangle(QGraphicsItem * parent, float shape)
    :QGraphicsRectItem(parent)
{
  shape_length = shape;
  setRect(0, 0, shape_length, shape_length);
  setZValue(4000.0);
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QVariant ArcEdgeSelectionRectangle::itemChange (GraphicsItemChange change, const QVariant &value)
{
  if ((change == QGraphicsItem::ItemSelectedHasChanged) && (isSelected()))
    parentItem()->setSelected(true);

  return value;
}

void ArcEdgeSelectionRectangle::paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget )
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setPen(QPen(Qt::black, 1, Qt::SolidLine,
     Qt::RoundCap, Qt::MiterJoin));
  painter->setBrush(Qt::white);
  painter->drawRect(QRectF(0, 0, shape_length, shape_length));
}

