#include "componentcontroller.h"

componentController::componentController()
{

}

void componentController::componentTreeInitial(QTreeWidget *newTree)
{
    newTree->clear();
    newTree->headerItem()->setText(0,QString());	//设置表头为空
    QStringList hraders;
    hraders<<"Type"<<"name";  //显示的设备列表信息
    newTree->setHeaderLabels(hraders);		//添加树表的表头

}

void componentController::addComponentTreeNode(QTreeWidget *newTree,QString component_type,QString component_name)
{
    QTreeWidgetItem *Item = new QTreeWidgetItem(newTree);
    Item->setText(0,component_type);
    Item->setText(1,component_name);
    Item->setCheckState(0,Qt::Unchecked);//添加复选框，默认未勾选
    Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    //Qt::ItemIsSelectable表示可选的、Qt::ItemIsUserCheckable项目上是否有复选框

}

void componentController::removeComponentTreeNode(QTreeWidgetItem *item)
{
    //if(item->checkState(0)==Qt::Checked)
        delete item;

}
void componentController::on_treeWidget_Dev_itemChanged(QTreeWidgetItem *item)//勾选复选框
{
    if(Qt::Checked==item->checkState(0)) //应为复选框设置在序号0的位置
    {
        qDebug()<<"checked text"<<item->text(0);//column=0
    }
}

