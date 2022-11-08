#ifndef __ARCSELECTIONRECTANGLE_H
#define __ARCSELECTIONRECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>

/*!
 * \brief The ArcEdgeSelectionRectangle class
 * 选中弧时转弯节点的小方块
 */
class ArcEdgeSelectionRectangle : public QGraphicsRectItem
{
 public:
    ArcEdgeSelectionRectangle(QGraphicsItem * parent, double rectSideLength);
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);

 protected:
    void paint ( QPainter * painter,
        const QStyleOptionGraphicsItem * option, QWidget * widget );

 private:
    double sideLength;
};

#endif
