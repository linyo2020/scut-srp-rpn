#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QUrl>
#include <QTextStream>

#include "petritabwidgt.h"

class TabWidget : public QTabWidget
{
     Q_OBJECT
public:
    TabWidget();
    /*
     * QTabWidget是带标签页的窗口，可以存储多个子窗口，
     * 每个子窗口的显示可以通过对应的标签index进行切换。
     */
    //槽函数
    void closeTab(int index);//关闭子窗口
    void removeItems ();
    void undo ();
    void redo ();
    void zoom (int val);
    //新建窗口
    void createNew ();
    //更新窗口名
    void updateTitle (bool changed);

    void save ();
    void saveAs ();
    void exportNet ();
    void print();
signals:
    void canRedoChange (bool canRedo);
    void canUndoChange (bool canUndo);
    void tabChanged (int index);
    void errorMessage (const QString &msg);

protected:
    //连接具体页面的信号和槽，用于传递Undo，Redo，netChanged，error信息
    void connectSignalAndSlot(PetriTabwidgt * tab);

private:
    int nets_indexes;
    QStringList fileNames;

};

#endif // TABWIDGET_H
