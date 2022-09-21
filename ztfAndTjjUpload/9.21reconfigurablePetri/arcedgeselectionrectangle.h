#ifndef __ARCSELECTIONRECTANGLE_H
#define __ARCSELECTIONRECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>

class ArcEdgeSelectionRectangle : public QGraphicsRectItem
{
 public:
    ArcEdgeSelectionRectangle(QGraphicsItem * parent, float shape);
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);

 protected:
    void paint ( QPainter * painter,
        const QStyleOptionGraphicsItem * option, QWidget * widget );

 private:
    float shape_length;
};

#endif
