#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QWidget>

/*
 * 可拖拉界面的部件
 */
class DockWidget : public QDockWidget
{
     Q_OBJECT
public:
    explicit DockWidget(QWidget * parent = 0);
    ~DockWidget();;

    void displayMessage();
    void clearMessage();
    void showMessage (const QString &msg);

private:
    QTextEdit  * textDisplay;
};

#endif // DOCKWIDGET_H
