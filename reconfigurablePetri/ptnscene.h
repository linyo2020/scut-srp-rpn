#ifndef PTNSCENE_H
#define PTNSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "place.h"
#include "transition.h"
#include "arcus.h"
#include "connector.h"
#include "sceneselectionrectangle.h"

class PTNscene : public QGraphicsScene
{
    Q_OBJECT

public:

    explicit PTNscene(QObject * parent = 0);
    ~PTNscene(){}

    void setMode (int mode);
    void removeItems();
    void enableSelection (bool selectable);
    void trakInitialMarking ();
    void resetInitialMarking();

    void setisComponent(bool Component);

    void from_Xml (const QList<PAGE_ATTR> &pages);
    void addXML_places (const QList <PLACE_ATTR> &places);
    void addXML_transitions (const QList <TRANSITION_ATTR> &transitions);
    void addXML_arcs (const QList <ARC_ATTR> &arcs);
    void addXML_connectors(const QList <CONNECTOR_ATTR> &connectors);

    //组件
    void from_Xml_Component (const COMPONENT_ATTR &componentAttr);
    void from_Xml_Component (const COMPONENT_ATTR &componentAttr,int count);
    void addXML_placesOfComp (const QList <PLACE_ATTR> &places,int count);
    void addXML_transitionsOfComp (const QList <TRANSITION_ATTR> &transitions,int count);
    void addXML_arcsOfComp (const QList <ARC_ATTR> &arcs,int count);
    void unbindComponent();
    void bindComponent();




    Marking getInitialMarking () const;
    QMap<QString, QString> getPlacesNames ();
    QMap<QString, int> getPlacesCapacities ();
//    QList<TRANS_RELATION> getRelations ();

signals:

    void nodeInserted(const QPointF &itemPos, const QString &id);
    void arcInserted(QGraphicsItem * source, QGraphicsItem * target,
    const QPainterPath &arc_path, const QString &id, PTNscene * scene,double w=1.0);
    void connectorInserted(QGraphicsItem * source, QGraphicsItem * target,
    const QPainterPath &connector_path, const QString &id, PTNscene * scene);
    void itemMoved (QGraphicsItem * movedItem, const QPointF &oldPosition);
    void nodeRemoved (QGraphicsItem * item, PTNscene * scene);
    void arcRemoved (QGraphicsItem * item, PTNscene * scene);
    void nodesInserted (const QStringList &names);


    void itemDoubleClicked(QGraphicsItem * item);

protected:

    void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    void keyPressEvent ( QKeyEvent * keyEvent );
    //void drawBackground ( QPainter * painter, const QRectF & rect);

private:
    int places_indexs;
    int transitions_indexs;
    int arcs_indexs;
    int connector_indexs;
    int mode;
    QTransform transform;
    bool isComponent=false;

    QGraphicsItem     * currentItem;
    QGraphicsPathItem * pathitem;



    SceneSelectionRectangle * selectionRect;

    QList<QPointF> points;
    QPointF origin, oldPos, currentPos;

    Marking initial_marking;

};

#endif // PTNSCENE_H
