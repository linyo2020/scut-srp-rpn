#ifndef COMPONENTCONTROLLER_H
#define COMPONENTCONTROLLER_H
#include <QTreeWidget>
#include <QDebug>

class componentController
{
public:
    componentController();
    void componentTreeInitial(QTreeWidget *newTree);
    void addComponentTreeNode(QTreeWidget *newTree,QString component_type,QString component_name);
    void deleteComponentTreeNode();

    QList<QTreeWidgetItem *> TreeWiditems;
private slots:
    void on_treeWidget_Dev_itemChanged(QTreeWidgetItem *item); //通过右键菜单添加槽函数
    void slotCustomContextMenu(const QPoint &);

};



#endif // COMPONENTCONTROLLER_H
