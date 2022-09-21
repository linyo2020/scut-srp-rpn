#include "sceneselectionrectangle.h"

SceneSelectionRectangle::SceneSelectionRectangle()
    :QGraphicsRectItem()
{

  setZValue(2000.0);

}

void SceneSelectionRectangle::paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option, QWidget * widget )
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

  painter->setPen(QPen(Qt::darkBlue, 1,
        Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
  painter->setBrush(QColor(0, 0, 255, 20));
  painter->drawRect(rect());
}


