#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QWidget>
#include "messagehandler.h"
/*
 * 可拖拉界面的部件
 */
class DockWidget : public QDockWidget
{
     Q_OBJECT
public:
    explicit DockWidget(QWidget * parent = 0);
    ~DockWidget();;

    MessageHandler& getMessageHandler ();

    void displayMessage();
    void clearMessage();
    void showMessage (const QString &msg);

private:
    QTextEdit  * textDisplay;
    MessageHandler messageHandler;
};

#endif // DOCKWIDGET_H
