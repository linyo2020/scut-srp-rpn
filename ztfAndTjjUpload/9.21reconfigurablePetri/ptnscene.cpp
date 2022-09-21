#include "ptnscene.h"

PTNscene::PTNscene(QObject * parent)
    :QGraphicsScene (parent)
{
    places_indexs = 0;
    transitions_indexs = 0;
    arcs_indexs = 0;
    mode = normalMode;

    pathitem = 0;
    currentItem = 0;
    selectionRect = 0;

    setSceneRect(0, 0, 5000, 5000);
    setItemIndexMethod(NoIndex);
}

void PTNscene::setMode (int mod)
{
    if((mode == animationMode)&&(mod != mode))
        resetInitialMarking();

    mode = mod;

    if(mode == animationMode)
    {
       enableSelection(false);
       trakInitialMarking ();
    }
    else
       enableSelection(true);

    if((mode == animationMode) || (mode == normalMode))
    {
        foreach(QGraphicsItem * item, items())
        {
            if(item->type() == Transition::Type)
                qgraphicsitem_cast<Transition*>(item)->setMode (mode);
        }
    }
}

/* save initial marking before animation */
void PTNscene::trakInitialMarking ()
{
    initial_marking.clear();
    foreach (QGraphicsItem * item, items())
    {
        if(item->type() == Place::Type)
        {
            Place * place = qgraphicsitem_cast<Place*>(item);
            initial_marking[place->getId()] = place->getTokens();
        }
    }
}

/* restore initial marking after animation */
void PTNscene::resetInitialMarking()
{
    foreach (QGraphicsItem * item, items())
    {
        if(item->type() == Place::Type)
        {
            Place * place = qgraphicsitem_cast<Place*>(item);
                    place->setTokens(initial_marking.value(place->getId()));
                    //qDebug()<<initial_marking.value(place->getId());
        }
    }
}

/* enable/disable items selection */
void PTNscene::enableSelection (bool selectable)
{
    foreach(QGraphicsItem * item, items())
        item->setFlag(QGraphicsItem::ItemIsSelectable, selectable);
}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* @@@@ handle items delete @@@@ */
/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* remove selected items */
void PTNscene::removeItems()
{
    if(selectedItems().isEmpty())
        return;

    foreach(QGraphicsItem * item, selectedItems())
       if(item->type() == QGraphicsSimpleTextItem::Type
            || item->type() == ArcEdgeSelectionRectangle::Type)
           item->setSelected(false);

    /* remove arcs before */
    foreach(QGraphicsItem * item, selectedItems())
    {
        if(item->type() == Arc::Type)
        {
            emit arcRemoved(item, this);
        }
    }

    /* remove places and transitions items */
    foreach(QGraphicsItem * item, selectedItems())
    {
        emit nodeRemoved(item, this);
    }
}

/* @@@@@@@@@à@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
/* @@@@ Protected functions re-implementation @@@@ */
/* @@@@@@@@@à@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/* mouse double-click */
void PTNscene::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if(mode != normalMode)
      return;

    currentItem = itemAt(mouseEvent->scenePos(),transform);

    if(!currentItem)
      return;

    emit itemDoubleClicked (currentItem);
}

/* mouse-press */
void PTNscene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if(mouseEvent->button() != Qt::LeftButton)
        return;

    int type;
    QVariant v;

    switch(mode)
     {
       case addPlaceMode:

            v.setValue(places_indexs);
            currentPos = QPointF(mouseEvent->scenePos().x() -15 , mouseEvent->scenePos().y() -15);
            emit nodeInserted(currentPos, QString("p%1").arg(v.toString()));
            places_indexs++;

        break;
       case addTransMode:

            v.setValue(transitions_indexs);
            emit nodeInserted(mouseEvent->scenePos(), QString("t%1").arg(v.toString()));
            transitions_indexs++;

        break;
       case drawArcMode:

            currentItem = itemAt(mouseEvent->scenePos(),transform);
            if(currentItem == 0)
                return;

            type = currentItem->type();

            if(( type == Place::Type) || (type == Transition::Type) )
            {
              if(pathitem == 0)
               {
                    pathitem = new QGraphicsPathItem;
                    pathitem->setZValue(-1000.0);
                    pathitem->setPen(QPen(Qt::black, 1,
                    Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin));
                    points << mouseEvent->scenePos();
                    addItem(pathitem);
               }
            }

        break;
       case normalMode:

        currentItem = itemAt(mouseEvent->scenePos(),transform);

        if((currentItem == 0)||(currentItem->type() == Arc::Type))
        {
           origin = mouseEvent->scenePos();
           selectionRect = new SceneSelectionRectangle;
           addItem(selectionRect);
        }
        else
            //oldPos = mouseEvent->scenePos();
            oldPos=currentItem->pos();

        break;
       case addToken:
        currentItem = itemAt(mouseEvent->scenePos(),transform);
        if(currentItem == 0)
            return;
        if(currentItem->type() == Place::Type)
            qgraphicsitem_cast<Place*>(currentItem)->updateTokens(1);
        break;
       case subToken:
        currentItem = itemAt(mouseEvent->scenePos(),transform);
        if(currentItem == 0)
            return;
        if(currentItem->type() == Place::Type)
            qgraphicsitem_cast<Place*>(currentItem)->updateTokens(-1);
        break;
       case animationMode:

        currentItem = itemAt(mouseEvent->scenePos(),transform);

        if(currentItem == 0)
          return;

        if(currentItem->type() == Transition::Type)
         {
            Transition * transition = qgraphicsitem_cast<Transition*>(currentItem);
            if((transition->isFirable()))
            {
                transition->fire();
            }
         }

        break;
       default:
     ;
     }

    QGraphicsScene::mousePressEvent(mouseEvent);
    emit sceneRectChanged (itemsBoundingRect() );
    update(itemsBoundingRect() );
}

/* mouse move event */
void PTNscene::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    if(mode == animationMode)
        return;

    if((mode == drawArcMode)&&(pathitem != 0))
    {
        QPainterPath newpath;
        newpath.moveTo(points[0]);

        foreach(QPointF p, points)
            newpath.lineTo(p);

        newpath.lineTo(event->scenePos());
        pathitem->setPath (newpath);
    }

    if(selectionRect != 0)
    {
        QRectF rec(origin, event->scenePos());
        selectionRect->setRect(rec.normalized());
        QPainterPath path;
        path.addRect(rec);
        setSelectionArea(path, QTransform());
    }

    if(mode == normalMode)
            QGraphicsScene::mouseMoveEvent(event);

    update(itemsBoundingRect() );
}

/* mouse release event */
void PTNscene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if(selectionRect != 0)
     {
        removeItem(selectionRect);
        delete selectionRect;
        selectionRect = 0;
     }

    if((currentItem != 0)&&(!oldPos.isNull()))
    {
        if(itemAt(mouseEvent->scenePos(),transform) == 0)
            return;//MAYBE BUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        emit itemMoved (itemAt(mouseEvent->scenePos(),transform), oldPos);
        oldPos = QPointF(0,0);
    }

    if(((mode == drawArcMode)&&(pathitem != 0))&&(itemAt(mouseEvent->scenePos(),transform) != 0))
     {
       if ((itemAt(mouseEvent->scenePos(),transform)->type() == QGraphicsPathItem::Type )||
           (itemAt(mouseEvent->scenePos(),transform) == 0))
        {
            points << mouseEvent->scenePos();
            return;
        }else
         {

            QPainterPath path = pathitem->path();
            removeItem(pathitem);
            delete pathitem;
            pathitem = 0;

            points.clear();

            QGraphicsItem * sourceItem = itemAt(path.pointAtPercent(0),transform);
            QGraphicsItem * targetItem = itemAt(mouseEvent->scenePos(),transform);

            if((sourceItem != 0) && (targetItem != 0))
            {

                if(!sourceItem->collidesWithItem(targetItem, Qt::IntersectsItemShape))
                {
                    int source_type = sourceItem->type();
                    int target_type = targetItem->type();

            // ** Petri Net rule: no relation allowed between nodes
            //(place or transition) of the same type!
                    if(source_type != target_type)
                    {
                        QVariant v(arcs_indexs);
                        emit arcInserted(sourceItem, targetItem, path, QString("a%1").arg(v.toString()), this);
                        arcs_indexs++;
                    }
                }
            }
        }
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    update(itemsBoundingRect());
}

/* Key Press Event */
void PTNscene::keyPressEvent ( QKeyEvent * keyEvent )
{
  /* to cancel an arc drawing */
  if((keyEvent->key() == Qt::Key_Escape)&&(mode == drawArcMode))
   {
    removeItem(pathitem);
    delete pathitem;
    pathitem = 0;
    points.clear();
  }
}
/*
void PTNscene::drawBackground ( QPainter * painter, const QRectF & rect)
{

}*/

/*****************************/
// X M L
/*****************************/

//void PTNscene::from_Xml (const QList<PAGE_ATTR> &pages)
//{
//    foreach (PAGE_ATTR page, pages)
//    {
//        addXML_places (page.placeNodes);
//        addXML_transitions (page.transitionNodes);
//        addXML_arcs (page.arcs);
//    }
//}

//void PTNscene::addXML_places (const QList <PLACE_ATTR> &places)
//{
//    QStringList names;
//    QList<int> indexes;
//    QRegExp rx("^p[0-9]+$");

//    foreach (PLACE_ATTR place, places)
//    {
//        Place * item = new Place (place);
//        addItem(item);
//        item->setPos (place.x, place.y);
//        names << place.name;

//        if(place.id.contains(rx))
//        {
//            QString str = place.id.remove(0,1);
//            indexes << str.toInt();
//        }
//    }

//    if(!indexes.isEmpty())
//     {
//       qSort(indexes.begin(), indexes.end());
//       places_indexs = indexes.last() + 1;
//     }

//    emit nodesInserted(names);
//}

//void PTNscene::addXML_transitions (const QList <TRANSITION_ATTR> &transitions)
//{
//    QStringList names;
//    QList<int> indexes;
//    QRegExp rx("^t[0-9]+$");

//    foreach (TRANSITION_ATTR transition, transitions)
//    {
//        Transition * item = new Transition (transition);
//        addItem(item);
//        item->setPos (transition.x, transition.y);
//        item->setRotation(transition.rotation);
//        names << transition.name;

//        if(transition.id.contains(rx))
//        {
//            QString str = transition.id.remove(0,1);
//            indexes << str.toInt();
//        }
//    }

//    if(!indexes.isEmpty())
//     {
//       qSort(indexes.begin(), indexes.end());
//       transitions_indexs = indexes.last() + 1;
//     }

//    emit nodesInserted(names);
//}

//void PTNscene::addXML_arcs (const QList <ARC_ATTR> &arcs)
//{
//    QList<int> indexes;
//    QRegExp rx("^a[0-9]+$");

//    QList<QGraphicsItem *> nodes = items ();
//    QGraphicsItem * sourceItem = 0;
//    QGraphicsItem * targetItem = 0;

//    foreach(ARC_ATTR xmlarc, arcs)
//     {
//        foreach(QGraphicsItem * node, nodes)
//        {
//            if(node->type() == Place::Type)
//            {
//                Place * place = qgraphicsitem_cast<Place*>(node);

//                    if(place->getId() == xmlarc.source)
//                        {sourceItem = place;continue;}
//                    if(place->getId() == xmlarc.target)
//                        {targetItem = place;continue;}
//            }
//            if(node->type() == Transition::Type)
//            {
//                Transition * transition = qgraphicsitem_cast<Transition*>(node);

//                    if(transition->getId() == xmlarc.source)
//                        {sourceItem = transition;continue;}
//                    if(transition->getId() == xmlarc.target)
//                        {targetItem = transition;continue;}
//            }
//        }

//      QPainterPath path(sourceItem->boundingRect ().center());

//      foreach(QPointF p, xmlarc.points)
//          path.lineTo(p);

//      path.lineTo(targetItem->boundingRect ().center());

//      Arc * arc = new Arc(sourceItem, targetItem, path, xmlarc);
//      if(!arc->getFISStruct().m_sFISName.empty())arc->createRuleSet();
//      addItem(arc);

//          if(sourceItem->type() == Place::Type)
//              qgraphicsitem_cast<Place*>(sourceItem)->addOutputArc(arc);
//          else if(sourceItem->type() == Transition::Type)
//              qgraphicsitem_cast<Transition*>(sourceItem)->addOutputArc(arc);
//          if(targetItem->type() == Place::Type)
//              qgraphicsitem_cast<Place*>(targetItem)->addInputArc(arc);
//          else if(targetItem->type() == Transition::Type)
//              qgraphicsitem_cast<Transition*>(targetItem)->addInputArc(arc);

//          if(xmlarc.id.contains(rx))
//          {
//            QString str = xmlarc.id.remove(0,1);
//            indexes << str.toInt();
//          }
//     }

//    if(!indexes.isEmpty())
//     {
//       qSort(indexes.begin(), indexes.end());
//       arcs_indexs = indexes.last() + 1;
//     }

//}
/*********************************/
/* To generate Coverability Grap */
/*********************************/

Marking PTNscene::getInitialMarking () const
{
    return initial_marking;
}

QMap<QString, int> PTNscene::getPlacesCapacities ()
{
    QMap<QString, int> map;

    foreach (QGraphicsItem * item, items())
    {
        if(item->type() == Place::Type)
        {
            Place * place = qgraphicsitem_cast<Place*>(item);
        int c = place->getCapacity();

        if(c == 0)
        c = omega;

            map[place->getId()] = c;
        }
    }

    return map;
}

QMap<QString, QString> PTNscene::getPlacesNames ()
{
    QMap<QString, QString> map;

    foreach (QGraphicsItem * item, items())
    {
        if(item->type() == Place::Type)
        {
            Place * place = qgraphicsitem_cast<Place*>(item);
            map[place->getId()] = place->getName();
        }
    }

    return map;
}

//QList<TRANS_RELATION> PTNscene::getRelations ()
//{
//  QList<TRANS_RELATION> relations;

//  foreach(QGraphicsItem * item, items())
//     if(item->type() == Transition::Type)
//      relations << qgraphicsitem_cast<Transition*>(item)->getTrans_Relations();

//  return relations;
//}
