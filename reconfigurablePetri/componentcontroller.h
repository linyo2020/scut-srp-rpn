#ifndef COMPONENTCONTROLLER_H
#define COMPONENTCONTROLLER_H
#include <QTreeWidget>
#include <QDebug>
#include <QDebug>
#include <QFile>
#include<QMap>
#include"component.h"
#include "xmlparser.h"
class componentController
{
public:
    componentController();
    void componentTreeInitial(QTreeWidget *newTree);
    void addComponentTreeNode(QTreeWidget *newTree,QString component_name,QString component_path);
    void removeComponentTreeNode(QTreeWidgetItem *item);

    double getToken(QString filename,QString ID);

    //通过读取文件，读取type数量
    void ReadListFile(QString str="./list.txt");
    void WriteListFile(QString str="./list.txt");
    QString newtype;
    QMap<QString,int>type_list;
    QMap<QString,QString> itemsFile;
    QMap<QTreeWidgetItem *,QString> TreeWiditems;


private slots:
    void on_treeWidget_Dev_itemChanged(QTreeWidgetItem *item); //通过右键菜单添加槽函数
    void slotCustomContextMenu(const QPoint &);


};



#endif // COMPONENTCONTROLLER_H
