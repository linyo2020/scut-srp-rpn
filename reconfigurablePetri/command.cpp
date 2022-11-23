#include "command.h"

//![0]
AddPlaceCommand::AddPlaceCommand(const QPointF &itemPos,
                     const QString &id, PTNscene * scene)
{
    place = new Place(id);
    position = itemPos;
    graphicsscene = scene;

}

void AddPlaceCommand::undo ()
{
    graphicsscene->removeItem(place);
    graphicsscene->update();
}

void AddPlaceCommand::redo ()
{
    graphicsscene->addItem(place);
    place->setPos(position);
    graphicsscene->update();
}

AddPlaceCommand::~AddPlaceCommand()
{
    if(!graphicsscene)
        delete place;
    //emit deletePlace();
}
//![0]

//![1]
AddTransitionCommand::AddTransitionCommand(const QPointF &itemPos,
                   const QString &id, PTNscene * scene)
{
    transition = new Transition(id);
    position   = itemPos;
    graphicsscene = scene;
}

void AddTransitionCommand::undo ()
{
    graphicsscene->removeItem(transition);
    graphicsscene->update();
}

void AddTransitionCommand::redo ()
{
    graphicsscene->addItem(transition);
    transition->setPos(position);
    graphicsscene->update();
}

AddTransitionCommand::~AddTransitionCommand()
{
    if(!graphicsscene)
        delete transition;
}
//![1]

//![2]
AddArcCommand::AddArcCommand(QGraphicsItem * item1, QGraphicsItem * item2,
                           const QPainterPath &arc_path,
                   const QString &id, PTNscene * scene, int ArcWeight)
{
    sourceItem = item1;
    targetItem = item2;
    aid = id;

    QString sid, tid;
    if(sourceItem->type() == Place::Type)
        sid = qgraphicsitem_cast<Place*>(sourceItem)->getId();
    else if(sourceItem->type() == Transition::Type)
        sid = qgraphicsitem_cast<Transition*>(sourceItem)->getId();

    if(targetItem->type() == Place::Type)
        tid = qgraphicsitem_cast<Place*>(targetItem)->getId();
    else if(targetItem->type() == Transition::Type)
        tid = qgraphicsitem_cast<Transition*>(targetItem)->getId();

    arc = new Arc(sourceItem, sid, targetItem, tid, arc_path, aid, ArcWeight);

    graphicsscene = scene;
}

void AddArcCommand::undo ()
{
    graphicsscene->removeItem(arc);
    removeConnections();
    graphicsscene->update();
}

void AddArcCommand::redo ()
{
    addConnections ();
    arc->updatePosition();
    graphicsscene->addItem(arc);
    graphicsscene->update();
}

void AddArcCommand::addConnections ()
{
    if(sourceItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(sourceItem)->addOutputArc(arc);
    else if(sourceItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(sourceItem)->addOutputArc(arc);

    if(targetItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(targetItem)->addInputArc(arc);
    else if(targetItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(targetItem)->addInputArc(arc);
}

void AddArcCommand::removeConnections()
{
    if(sourceItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(sourceItem)->deleteArc(aid);
    else if(sourceItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(sourceItem)->deleteArc(aid);

    if(targetItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(targetItem)->deleteArc(aid);
    else if(targetItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(targetItem)->deleteArc(aid);
}

AddArcCommand::~AddArcCommand()
{
    if(!graphicsscene)
        delete arc;
}
//![2]

//![3]
RemoveArcCommand::RemoveArcCommand(QGraphicsItem * item,
                              PTNscene * scene)
{
    arc = qgraphicsitem_cast<Arc*>(item);
    graphicsscene = scene;
    sourceItem = arc->getSourceItem();
    targetItem = arc->getTargetItem();
    aid = arc->getId();
}

void RemoveArcCommand::undo ()
{
    graphicsscene->addItem(arc);
    addConnections ();
    graphicsscene->update();
}

void RemoveArcCommand::redo ()
{
    graphicsscene->removeItem(arc);
    removeConnections ();
    graphicsscene->update();
}

void RemoveArcCommand::addConnections ()
{
    if(sourceItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(sourceItem)->addOutputArc(arc);
    else if(sourceItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(sourceItem)->addOutputArc(arc);

    if(targetItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(targetItem)->addInputArc(arc);
    else if(targetItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(targetItem)->addInputArc(arc);
}

void RemoveArcCommand::removeConnections ()
{
    if(sourceItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(sourceItem)->deleteArc(aid);
    else if(sourceItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(sourceItem)->deleteArc(aid);

    if(targetItem->type() == Place::Type)
        qgraphicsitem_cast<Place*>(targetItem)->deleteArc(aid);
    else if(targetItem->type() == Transition::Type)
        qgraphicsitem_cast<Transition*>(targetItem)->deleteArc(aid);
}

RemoveArcCommand::~RemoveArcCommand(){}
//![3]

//![4]
RemoveNodeCommand::RemoveNodeCommand(QGraphicsItem * item, PTNscene * scene)
{
    this->item = item;
    position = item->pos();
    graphicsscene = scene;
}

void RemoveNodeCommand::undo ()
{
    graphicsscene->addItem(item);
    item->setPos(position);
    graphicsscene->update();
}

void RemoveNodeCommand::redo ()
{
    graphicsscene->removeItem(item);
    graphicsscene->update();
}

RemoveNodeCommand::~RemoveNodeCommand(){}
//![4]

//![5]
MoveCommand::MoveCommand(QGraphicsItem * movedItem,
                    const QPointF &oldPosition)
{
    item = movedItem;
    oldPos = oldPosition;
    newPos = item->pos();
}

void MoveCommand::undo()
{
    item->setPos(oldPos);
    item->scene()->update();
}

void MoveCommand::redo()
{
    item->setPos(newPos);
}
//![5]
ArcClickCommand::ArcClickCommand(QGraphicsItem * clickitem, PTNscene * scene)
{
    item = clickitem;
    graphicsscene=scene;
}

void ArcClickCommand::undo()
{
}

void ArcClickCommand::redo()
{
}
ArcClickCommand::~ArcClickCommand(){}
