#ifndef __SCENESELECTIONRECTANGLE_H
#define __SCENESELECTIONRECTANGLE_H

#include <QPainter>
#include <QGraphicsRectItem>

class SceneSelectionRectangle : public QGraphicsRectItem
{
 public:
    SceneSelectionRectangle();

 protected:
    void paint ( QPainter * painter,
        const QStyleOptionGraphicsItem * option,
              QWidget * widget );

};

#endif

