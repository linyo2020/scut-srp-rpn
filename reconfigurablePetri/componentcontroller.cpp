#include "componentcontroller.h"

ComponentController::ComponentController()
{


}

void ComponentController::componentTreeInitial(QTreeWidget *newTree)
{
    newTree->clear();
    newTree->headerItem()->setText(0,QString());	//设置表头为空
    QStringList hraders;
    hraders<<"name";  //显示的设备列表信息
    newTree->setHeaderLabels(hraders);		//添加树表的表头

}

void ComponentController::addComponentTreeNode(QTreeWidget *newTree,QString component_name,QString component_path)
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
        Item->setText(0,component_name);
        Item->setText(1,component_path);
        Item->setCheckState(0,Qt::Unchecked);//添加复选框，默认未勾选
        Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        //Qt::ItemIsSelectable表示可选的、Qt::ItemIsUserCheckable项目上是否有复选框
    }
}

void ComponentController::removeComponentTreeNode(QTreeWidgetItem *item)
{
    //if(item->checkState(0)==Qt::Checked)

    itemsFile.remove(item->text(0));
    delete item;
}
PTNET_ATTR ComponentController::getPTnet(QString filename)
{
    QMapIterator<QString,QString>iterator(itemsFile);
    PTNET_ATTR net;
    while(iterator.hasNext())
    {
        iterator.next();
        if(filename==iterator.key())
        {
            QFile file(iterator.value());
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            //![3] parse xml file
            file.seek(0);
            QTextStream textstream(&file);
            textstream.setCodec("utf-8");
            QString xmlContent = textstream.readAll();
            file.close();

            XmlParser parser;
            parser.parseXML(xmlContent);

            net = parser.getXML_net ();
        }
    }
    return net;
}
QList<PAGE_ATTR> ComponentController::getXMLpages(QString filename)
{
    QMapIterator<QString,QString>iterator(itemsFile);
    QList<PAGE_ATTR> page;
    while(iterator.hasNext())
    {
        iterator.next();
        if(filename==iterator.key())
        {
            QFile file(iterator.value());
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            //![3] parse xml file
            file.seek(0);
            QTextStream textstream(&file);
            textstream.setCodec("utf-8");
            QString xmlContent = textstream.readAll();
            file.close();

            XmlParser parser;
            parser.parseXML(xmlContent);

            PTNET_ATTR net = parser.getXML_net ();
            page=net.pages;
        }
    }
    return page;
}

Component * ComponentController::getComponent(QString filename)
{
    QMapIterator<QString,QString>iterator(itemsFile);
    Component*com=new Component();
    while(iterator.hasNext())
    {
        iterator.next();
        if(filename==iterator.key())
        {
//            qDebug()<<iterator.key();
            QFile file(iterator.value());
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            //![3] parse xml file
            file.seek(0);
            QTextStream textstream(&file);
            textstream.setCodec("utf-8");
            QString xmlContent = textstream.readAll();
            file.close();

            XmlParser parser;
            parser.parseXML(xmlContent);

            PTNET_ATTR net = parser.getXML_net ();
            QList<PAGE_ATTR> page=net.pages;
            foreach(PAGE_ATTR p,page)
            {
                foreach(COMPONENT_ATTR c,p.componentList)
                {
                    com->setStep(c.step);
                    com->setID(c.id);
                    com->setPlace_ATTRList(c.placeNodes);
                    com->setTransition_ATTRList(c.transitionNodes);
                    com->setArc_ATTRList(c.arcs);
                    foreach(PLACE_ATTR pl,c.placeNodes)
                    {
                        Place * place=new Place(pl);
                        com->mynet->AddPlace(place);
                    }
                    foreach(TRANSITION_ATTR tr,c.transitionNodes)
                    {
                        Transition *trans=new Transition(tr);
                        com->mynet->AddTransition(trans);
                    }
                    foreach(ARC_ATTR a,c.arcs)
                    {
                        QGraphicsItem * sourceItem = 0;
                        QGraphicsItem * targetItem = 0;
                        foreach(Place * place,com->mynet->PlaceList)
                        {
                            if(place->getId() == a.source)
                            {
                                sourceItem = place;
                                continue;

                            }
                            if(place->getId() == a.target)
                            {
                                targetItem = place;
                                continue;
                            }
                        }
                        foreach(Transition * transition,com->mynet->TransitionList)
                        {
                            if(transition->getId() == a.source)
                            {
                                sourceItem = transition;
                                continue;}
                            if(transition->getId() == a.target)
                            {
                                targetItem = transition;
                                continue;
                            }
                        }
                        QPainterPath path(sourceItem->boundingRect().center());

                        foreach(QPointF p, a.points)
                            path.lineTo(p);

                        path.lineTo(targetItem->boundingRect ().center());
                        Arcus * arc = new Arcus(sourceItem, targetItem, path, a);
                        if(sourceItem->type() == Place::Type)
                            qgraphicsitem_cast<Place*>(sourceItem)->addOutputArc(arc);
                        else if(sourceItem->type() == Transition::Type)
                            qgraphicsitem_cast<Transition*>(sourceItem)->addOutputArc(arc);
                        if(targetItem->type() == Place::Type)
                            qgraphicsitem_cast<Place*>(targetItem)->addInputArc(arc);
                        else if(targetItem->type() == Transition::Type)
                            qgraphicsitem_cast<Transition*>(targetItem)->addInputArc(arc);
                        com->mynet->AddArc(arc);

                    }

                }
                            }
        }
    }
    /***
     * 测试com
     * 结果：
     */
    QList<PLACE_ATTR>l_placeAttrList=com->getPlace_ATTRList();
    for(int i=0;i<l_placeAttrList.size();i++)
    {
        qDebug()<<l_placeAttrList[i].id<<" : "<<l_placeAttrList[i].initmark;
    }

    return com;
}

double ComponentController::getToken(QString filename,QString ID)
{
    QMapIterator<QString,QString>iterator(itemsFile);
    double tokenNum;
    double capacityNum;
    while(iterator.hasNext())
    {
        iterator.next();
        if(filename==iterator.key())
        {
            QFile file(iterator.value());
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            //![3] parse xml file
            file.seek(0);
            QTextStream textstream(&file);
            textstream.setCodec("utf-8");
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


void ComponentController::ReadListFile(QString str)
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

void ComponentController::WriteListFile(QString str)
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


void ComponentController::on_treeWidget_Dev_itemChanged(QTreeWidgetItem *item)//勾选复选框
{
    if(Qt::Checked==item->checkState(0)) //应为复选框设置在序号0的位置
    {
        qDebug()<<"checked text"<<item->text(0);//column=0
    }
}

