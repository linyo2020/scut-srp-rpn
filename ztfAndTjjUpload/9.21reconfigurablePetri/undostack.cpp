#include "undostack.h"

UndoStack::UndoStack(QObject * parent):QUndoStack(parent){}
UndoStack::~UndoStack(){}

void UndoStack::arcInserted(QGraphicsItem * item1, QGraphicsItem * item2,
                         const QPainterPath &arc_path,
                  const QString &id, PTNscene * scene, int w)
{
    push(new AddArcCommand(item1, item2, arc_path, id, scene, w));
}

void UndoStack::itemMoved (QGraphicsItem * movedItem, const QPointF &oldPosition)
{
    push(new MoveCommand(movedItem, oldPosition));
}

void UndoStack::nodeRemoved (QGraphicsItem * item, PTNscene * scene)
{
    push(new RemoveNodeCommand(item, scene));
}

void UndoStack::arcRemoved (QGraphicsItem * item, PTNscene * scene)
{
    push(new RemoveArcCommand(item, scene));
}
void UndoStack::arcClicked(QGraphicsItem *item, PTNscene *scene)
{
    push(new ArcClickCommand(item,scene));
}

