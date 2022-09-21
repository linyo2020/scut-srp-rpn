#ifndef __GRAPHNODE_H
#define __GRAPHNODE_H

#include <QGraphicsEllipseItem>

#include "graphedge.h"
#include "defs.h"

struct NODELABEL{QString name; int mark;};

class GraphNode : public QGraphicsEllipseItem
{

 public:
    enum { Type = UserType + 6 };
    GraphNode(int node_index, const QList<NODELABEL> &M, float width, float height);
    ~GraphNode();

    int getIndex();
    void createLabelText();
    void addInEdge(GraphEdge * edge);
    void addOutEdge(GraphEdge * edge);
    void removeInEdge(int index);
    void removeOutEdge(int index);

    int type () const;
    QRectF boundingRect() const;
    QPainterPath shape () const;
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);

 protected:
    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget );

 private:

    int index;
    QList<NODELABEL> marking;
    QGraphicsSimpleTextItem * label;
    QList<GraphEdge*> inedges;
    QList<GraphEdge*> outedges;
    QColor color;
    float wd, ht;
};

#endif
