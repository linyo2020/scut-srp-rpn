#include "componentcontroller.h"

componentController::componentController()
{


}

void componentController::componentTreeInitial(QTreeWidget *newTree)
{
    newTree->clear();
    newTree->headerItem()->setText(0,QString());	//设置表头为空
    QStringList hraders;
    hraders<<"name";  //显示的设备列表信息
    newTree->setHeaderLabels(hraders);		//添加树表的表头

}

void componentController::addComponentTreeNode(QTreeWidget *newTree,QString component_name,QString component_path)
{
    bool flag=1;
    //遍历treeWidget
        QTreeWidgetItemIterator it(newTree);
        while (*it) {
             if((*it)->text(1)==component_path||(*it)->text(0)==component_name)
             {
                 flag=0;
             }
            ++it;
        }
        if(flag)
        {
            QTreeWidgetItem *Item = new QTreeWidgetItem(newTree);
            itemsFile[component_name]=component_path;
            //Item->setText(0,component_type);
            Item->setText(0,component_name);
            Item->setText(1,component_path);
            Item->setCheckState(0,Qt::Unchecked);//添加复选框，默认未勾选
            Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            //Qt::ItemIsSelectable表示可选的、Qt::ItemIsUserCheckable项目上是否有复选框
        }
}

void componentController::removeComponentTreeNode(QTreeWidgetItem *item)
{
    //if(item->checkState(0)==Qt::Checked)
        delete item;

}

double componentController::getToken(QString filename,QString ID)
{
    QMapIterator<QString,QString>iterator(itemsFile);
    double tokenNum;
    double capacityNum;
    while(iterator.hasNext())
    {
        if(filename==iterator.key())
        {
            QFile file(iterator.value());
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            //![3] parse xml file
            file.seek(0);
            QTextStream textstream(&file);
            QString xmlContent = textstream.readAll();
            file.close();

            XmlParser parser;
            parser.parseXML(xmlContent);

            PTNET_ATTR net = parser.getXML_net ();
            QList<PAGE_ATTR> page=net.pages;

            foreach(PAGE_ATTR p,page)
            {
                foreach(PLACE_ATTR pl,p.placeNodes)
                {
                    if(ID==pl.id)
                    {
                    tokenNum=pl.initmark;
                    capacityNum=pl.capacity;
                    }
                }
            }

        }
    }
    return tokenNum;
}


void componentController::ReadListFile(QString str)
{
    QFile file(str);
    QMapIterator<QString,int>iter(type_list);
    if (file.open(QIODevice::ReadOnly))
    {


        while (!file.atEnd())
        {
            qDebug()<<"open";
            QByteArray line = file.readLine();
            QString str(line);
            QStringList list=str.split("|");
            qDebug()<<"list[0]"<<list[0];
            qDebug()<<"list[1]"<<list[1].toInt();
            type_list.insert(list[0],list[1].toInt());
        }
        file.close();
    }
}

void componentController::WriteListFile(QString str)
{
//    this->type_list.insert("AB",3);
//    this->type_list.insert("BH",4);
//    this->type_list.insert("r",8);

    QFile file(str);

    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {

        qDebug()<<"success";
        QTextStream out(&file);
        //先做添加组件
        qDebug()<<"type_list.contains(this->newtype) :"<<type_list.contains(this->newtype);
        if(type_list.contains(this->newtype))
        {

            qDebug()<<"<type_list[newtype]+1:"<<type_list[newtype]+1;

            qDebug()<<"if"<<newtype;
            type_list[newtype]=type_list[newtype]+1;
            QMapIterator<QString,int>iter(type_list);
            while(iter.hasNext())
            {
                iter.next();
                out<<iter.key()<<"|"<<iter.value();
                qDebug()<<"write"<<iter.key()<<"|"<<iter.value();
                out<<"\n";
            }

        }

        else
        {
            qDebug()<<"else"<<newtype;

            type_list.insert(newtype,1);
            QMapIterator<QString,int>iter(type_list);
            while(iter.hasNext())
            {
                iter.next();
                out<<iter.key()<<"|"<<iter.value();
                out<<"\n";
            }
        }

        file.flush();
        file.close();
    }

}


void componentController::on_treeWidget_Dev_itemChanged(QTreeWidgetItem *item)//勾选复选框
{
    if(Qt::Checked==item->checkState(0)) //应为复选框设置在序号0的位置
    {
        qDebug()<<"checked text"<<item->text(0);//column=0
    }
}

