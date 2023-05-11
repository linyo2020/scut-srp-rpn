#include "componentlist.h"

#include<time.h>

ComponentList::ComponentList()
{
    m_Scene=new PTNscene();
    m_View=nullptr;
    comController=new ComponentController();

}

//double ComponentList::getCertainPlaceToken(QString PlaceID)
//{
//    QString comID=(PlaceID.split("+")[0].split("&")[0]+"&"+PlaceID.split("+")[0].split("&")[1]);
//    if(com_list.size()==0)
//    {
//        qDebug()<<"use getCertainPlace,but com_list.size()==0";
//        return 0;
//    }
//    else
//    {
//        for(int i=0;i<com_list.size();i++)
//        {
//            if(com_list[i]->getID()==comID)
//            {
//                for(int y=0;y<com_list[i]->getPlace_ATTRList().size();y++)
//                {
//                    if(com_list[i]->getPlace_ATTRList()[y].id==PlaceID)
//                    {
//                        return com_list[i]->getPlace_ATTRList()[y].initmark;
//                    }
//                }
//            }
//        }
//    }
//}



//Component *ComponentList::getCertainComponent(QString ComID)
//{
//    for(int i=0;i<com_list.size();i++)
//    {
//        if(com_list[i]->getID()==ComID)
//        {
//            return com_list[i];
//        }
//    }
//    return nullptr;
//}


Place *ComponentList::getCertainPlace(QString PlaceID)
{
////    QString comID=(PlaceID.split("+")[0].split("&")[0]+"&"+PlaceID.split("+")[0].split("&")[1]);
////    for(int i=0;i<com_list.size();i++)
////    {
////        if(com_list[i]->getID()==comID)
////        {
////            for(int i=0;i<com_list[i]->getPlaceList().size();i++)
////            {
////                if(com_list[i]->getPlaceList()[i]->getId()==PlaceID)
////                {
////                    return com_list[i]->getPlaceList()[i];
////                }
////            }
////        }
////    }
//    //2
    QString comID=(PlaceID.split("+")[0].split("&")[0]+"&"+PlaceID.split("+")[0].split("&")[1]);
    if(com_list.size()==0)
    {
        qDebug()<<"use getCertainPlace,but com_list.size()==0";
        return nullptr;
    }
    else
    {
        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID)
            {
                for(int y=0;y<com_list[i]->mynet->PlaceList.size();y++)
                {
                    if(com_list[i]->mynet->PlaceList[y]->getId()==PlaceID)
                    {
                        return com_list[i]->mynet->PlaceList[y];
                    }
                }
            }
        }
    }



}

QList<double> ComponentList::getCertainPlaceToken(QString PlaceID)
{
    QList<double>result;
    if(com_list.size()==0)
        return result;
    QStringList id=PlaceID.split("&");
    //如果id为组件名+编号+元素
    if(id.size()==3)
    {
        QString comId=id[0]+"&"+id[1];
        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comId)
            {
                QList<PLACE_ATTR>l_placeAttrList=com_list[i]->getPlace_ATTRList();
                for(int j=0;j<l_placeAttrList.size();j++)
                {
                    if(l_placeAttrList[i].id==PlaceID)
                    {
                        result.push_back(l_placeAttrList[i].initmark);
                        return result;
                    }
                }
            }
        }
        return result;
    }
    if(id.size()==2)
    {
        //如果id名为组件名+元素
        for(int i=0;i<com_list.size();i++)
        {
            QString placeInnerId;
            QStringList id1=com_list[i]->getID().split("&");
            QString targetString=com_list[i]->getID();
            if(id[0]==id1[0])
            {
                QList<PLACE_ATTR>l_placeAttrList=com_list[i]->getPlace_ATTRList();
                 for(int j=0;j<l_placeAttrList.size();j++)
                 {
                     if(l_placeAttrList[j].id.split("&")[2]==id[1])
                     {
                         result.push_back(l_placeAttrList[j].initmark);
                         qDebug()<<l_placeAttrList[j].initmark;
                     }
                 }
            }
        }
        return result;
    }
    else {
        return result;
    }
}

//double ComponentList::getCertainPlaceToken(QString PlaceID)
//{
//    QString comID=(PlaceID.split("+")[0].split("&")[0]+"&"+PlaceID.split("+")[0].split("&")[1]);
//    if(com_list.size()==0)
//    {
//        qDebug()<<"use getCertainPlace,but com_list.size()==0";
//        return -1.0;
//    }
//    else
//    {
//        for(int i=0;i<com_list.size();i++)
//        {
//            if(com_list[i]->getID()==comID)
//            {
//                for(int y=0;y<com_list[i]->mynet->PlaceList.size();y++)
//                {
//                    if(com_list[i]->mynet->PlaceList[y]->getId()==PlaceID)
//                    {
//                        return com_list[i]->mynet->PlaceList[y]->getTokens();
//                    }
//                }
//            }
//        }
//        return -1.0;
//    }
//}

QList<Place *> ComponentList::getPortinComponent(QString ComponentID)
{
//    QList<Place*>P;
//    for(int i=0;i<com_list.size();i++)
//    {
//        if(com_list[i]->getID()==ComponentID)
//        {
//            for(int i=0;com_list[i]->getPlaceList().size();i++)
//            {
//                if(com_list[i]->getPlaceList()[i]->isNormalPort())
//                {
//                   P.push_back(com_list[i]->getPlaceList()[i]);
//                }
//            }
//        }
//    }
//    return P;

    QList<Place*>l;
    foreach(Component* com,this->com_list)
    {
        if(com->getID()==ComponentID)
        {
            foreach(Place* pl,com->mynet->PlaceList)
            {
                Place*p=pl;
                QStringList cID=p->getComponentID();
                if(cID.size()==1&&cID[0]==ComponentID)
                {
                    l.push_back(p);
                }
            }

        }
    }
    return l;
}


QList<QString> ComponentList::getCertainPlaceName(QString ComponentID)
{
//    QList<QString>list;
//    for(int i=0;i<com_list.size();i++)
//    {
//        if(com_list[i]->getID()==ComponentID)
//        {
//            for(int i=0;i<com_list[i]->getPlaceList().size();i++)
//            {
//                Place*p=com_list[i]->getPlaceList()[i];
//                QStringList ID=p->getId().split("+");
//                if(ID.size()==1)
//                {
//                    list.push_back(ID[0].split("&")[2]);
//                }
//                //对于复合端口单独处理
//                else
//                {
//                    for(int i=0;i<ID.size();i++)
//                    {
//                        QString ComID=ID[i].split("&")[0]+"&"+ID[i].split("&")[1];
//                        if(ComID==ComponentID)
//                        {
//                            list.push_back(ID[i].split("&")[2]);
//                        }

//                    }
//                }

//            }

//        }
//    }
//    return list;
    //2
//    QList<QString>l;
//    foreach(QGraphicsItem*item,this->Scene->items())
//    {
//        if(item->type()==Place::Type)
//        {
//            Place*p=qgraphicsitem_cast<Place*>(item);
//            QStringList cID=p->getComponentID();
//            if(cID.contains(ComponentID))
//            {
//                l.push_back(p->getName(ComponentID));
//            }
//        }
//    }
//    return l;

    QList<QString>l;
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            for(int y=0;y<com_list[i]->getPlace_ATTRList().size();y++)
            {
                l.push_back(com_list[i]->getPlace_ATTRList()[i].id.split("&")[2]);
            }
        }
    }
    return l;
}

QList<QString> ComponentList::getCertainTransitionName(QString ComponentID)
{
//    QList<QString>list;
//    for(int i=0;i<com_list.size();i++)
//    {
//        if(com_list[i]->getID()==ComponentID)
//        {
//            for(int i=0;i<com_list[i]->getTransitionList().size();i++)
//            {
//                Transition*p=com_list[i]->getTransitionList()[i];
//                QStringList id=p->getId().split("+");
//                if((id[0].split("&")[0]+"&"+id[0].split("&")[1])==ComponentID)
//                {
//                    list.push_back(id[0].split("&")[2]);
//                }
//                else
//                {
//                    list.push_back(id[1].split("&")[2]);
//                }
//            }

//        }
//    }
//    return list;
    QList<QString>l;
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            for(int y=0;y<com_list[i]->getTransition_ATTRList().size();y++)
            {
                l.push_back(com_list[i]->getTransition_ATTRList()[i].id.split("&")[2]);
            }
        }
    }
    return l;
}

void ComponentList::deleteConnect(QString PlaceID1, QString PlaceID2)
{
    for(int i=0;i<connectList.size();i++)
    {
        if((connectList[i]->getSourceId()==PlaceID1&&connectList[i]->getTargetId()==PlaceID2)||(connectList[i]->getSourceId()==PlaceID2&&connectList[i]->getTargetId()==PlaceID1))
        {
            connectList.removeAt(i);
            m_lConnector.removeAt(i);
        }
    }
}

//todo
//遍历当前scene与garbage
void ComponentList::setnewComponentIDinSimulation(Component *newComponent)
{
//    int count=0;
//    for(int i=0;i<com_list.size();i++)
//    {
//        if(com_list[i]->getComponentFileName()==newComponent->getComponentFileName())
//        {
//            count++;
//        }
//    }

//    QMapIterator<QString,PTNscene*>it(this->garbage);
//    while (it.hasNext()) {
//        it.next();
//        if(it.key().split("&")[0]==newComponent->getComponentFileName())
//        {
//            count++;
//        }
//    }

//    newComponent->setID(newComponent->getComponentFileName()+QString::number(count));
//    return (newComponent->getComponentFileName()+QString::number(count));

    //2
//    int maxnum=0;
//    QList<QString> cid;
//    foreach(QGraphicsItem*item,this->Scene->items())
//    {
//        if(item->type()==Place::Type)
//        {
//            Place*p=qgraphicsitem_cast<Place*>(item);
//            QStringList cid=p->getComponentID();
//            if(p->getFileName().contains(newComponent->getFileName()))
//            {
//                if(cid[0]==newComponent->getID())
//                {
//                    if(maxnum<cid[0].split("&")[1].toInt())
//                    {
//                        maxnum=cid[0].split("&")[1].toInt();
//                    }

//                }
//                if(cid.size()==2&&cid[1]==newComponent->getID())
//                {
//                    if(maxnum<cid[1].split("&")[1].toInt())
//                    {
//                        maxnum=cid[1].split("&")[1].toInt();
//                    }

//                }
//            }
//        }
//        if(item->type()==Transition::Type)
//        {
//            Transition*p=qgraphicsitem_cast<Transition*>(item);
//            QStringList cid=p->getComponentID();
//            if(p->getFileName().contains(newComponent->getFileName()))
//            {
//                if(cid[0]==newComponent->getID())
//                {
//                    if(maxnum<cid[0].split("&")[1].toInt())
//                    {
//                        maxnum=cid[0].split("&")[1].toInt();
//                    }

//                }
//                if(cid.size()==2&&cid[1]==newComponent->getID())
//                {
//                    if(maxnum<cid[1].split("&")[1].toInt())
//                    {
//                        maxnum=cid[1].split("&")[1].toInt();
//                    }

//                }
//            }
//        }
//    }

//    QMapIterator<QString,PTNscene*>it(this->garbage);
//    while (it.hasNext()) {
//        it.next();
//        if(it.key().split("&")[0]==newComponent->getComponentFileName())
//        {
//            if(it.key().split("&")[1].toInt()>maxnum)
//            {
//                maxnum=it.key().split("&")[1].toInt();
//            }
//        }
//    }
//    newComponent->setID(newComponent->getComponentFileName()+"&"+QString::number(maxnum));
//    return (newComponent->getComponentFileName()+"&"+QString::number(maxnum));

    int max=1;
    QString filename=newComponent->getID().split("&")[0];
    for(int i=0;i<com_list.size();i++)
    {
        QString fn=com_list[i]->getID().split("&")[0];
        if(fn==filename)
        {
            max++;
        }
    }
    for(int i=0;i<garbage2.size();i++)
    {
        QString fn=garbage2[i]->getID().split("&")[0];
        if(fn==filename)
        {
            max++;
        }
    }
    QString cID=filename+"&"+QString::number(max);
    newComponent->setID(cID,0);



}

void ComponentList::addComponentPort(QString portID1, QString portID2)
{
    qDebug()<<"new connector is from"<<portID1<<" to "<<portID2;
    int flag1=0;
    int flag2=0;
    foreach(Component*component,com_list)
    {
        foreach(PLACE_ATTR place,component->getPlace_ATTRList())
        {
            if(place.id==portID1)
                flag1=1;
            else if(place.id==portID2)
                flag2=1;
        }
    }
    if(flag1==1&&flag2==1)
    {
        CONNECTOR_ATTR newConnectorATTR;
        newConnectorATTR.source=portID1;
        newConnectorATTR.target=portID2;
        newConnectorATTR.id=portID1+'&'+portID2;
        m_lConnector.push_back(newConnectorATTR);
    }
}

//useless
//void ComponentList::addNewComponent(Component*newCom)
//{
//    this->setnewComponentIDinSimulation(newCom);

//    foreach(Place* pl,newCom->getPlaceList())
//    {
//        Scene->addItem(pl);
//    }
//    foreach(Transition *tran,newCom->getTransitionList())
//    {
//        Scene->addItem(tran);
//    }
//    foreach(Arc* ar,newCom->getTArcList())
//    {
//        Scene->addItem(ar);
//    }

//}

Transition *ComponentList::getcertainTransition(QString tranID)
{
//    QString comID=(tranID.split("+")[0].split("&")[0]+"&"+tranID.split("+")[0].split("&")[1]);
//    for(int i=0;i<com_list.size();i++)
//    {
//        if(com_list[i]->getID()==comID)
//        {
//            for(int i=0;i<com_list[i]->getTransitionList().size();i++)
//            {
//                if(com_list[i]->getTransitionList()[i]->getId()==tranID)
//                {
//                    return com_list[i]->getTransitionList()[i];
//                }
//            }
//        }
//    }

    foreach(QGraphicsItem*item,this->m_Scene->items())
    {
        if(item->type()==QGraphicsItemGroup::Type)
        {
            foreach(QGraphicsItem*i,item->childItems())
            {
                if(i->type()==Transition::Type)
                {
                    Transition*t=qgraphicsitem_cast<Transition*>(i);
                    if(t->getId()==tranID)
                    {
                        return t;
                    }
                }
            }
        }
        else
        {
            if(item->type()==Transition::Type)
            {
                Transition*t=qgraphicsitem_cast<Transition*>(item);
                if(t->getId()==tranID)
                {
                    return t;
                }
            }
        }
    }
}


//QString ComponentList::addNewComponent(QString Filename)
//{
//      QList<COMPONENT_ATTR> compAttrList= comController->getCompAttrList(Filename);
//      if(compAttrList.isEmpty())
//          return QString("errorName");
//      return addComponent(compAttrList[0]);

////    Component*com=this->OriginComponent(Filename);
////    setnewComponentIDinSimulation(com);

////    foreach(Place* pl,com->getPlaceList())
////    {
////        Scene->addItem(pl);
////    }
////    foreach(Transition *tran,com->getTransitionList())
////    {
////        Scene->addItem(tran);
////    }
////    foreach(Arc* ar,com->getTArcList())
////    {
////        Scene->addItem(ar);
////    }

////    return com->getID();
////    Component*com=this->OriginComponent(Filename);

//    /***
//     * 测试com
//     * 结果：originCompent函数结果不正确
//     */
////    QList<PLACE_ATTR>l_placeAttrList=com->getPlace_ATTRList();
////    for(int i=0;i<l_placeAttrList.size();i++)
////    {
////        qDebug()<<l_placeAttrList[i].id<<" : "<<l_placeAttrList[i].initmark;
////    }


////    this->setnewComponentIDinSimulation(com);
////    this->com_list.push_back(com);
////    foreach(PLACE_ATTR pl,com->getPlace_ATTRList())
////    {
////        Place * place=new Place(pl);
////        com->mynet->AddPlace(place);
////    }
////    foreach(TRANSITION_ATTR tr,com->getTransition_ATTRList())
////    {
////        Transition *trans=new Transition(tr);
////        com->mynet->AddTransition(trans);
////    }
////    foreach(ARC_ATTR a,com->getArc_ATTRList())
////    {
////        QGraphicsItem * sourceItem = 0;
////        QGraphicsItem * targetItem = 0;
////        foreach(Place * place,com->mynet->PlaceList)
////        {
////            if(place->getId() == a.source)
////            {
////                sourceItem = place;
////                continue;

////            }
////            if(place->getId() == a.target)
////            {
////                targetItem = place;
////                continue;
////            }
////        }
////        foreach(Transition * transition,com->mynet->TransitionList)
////        {
////            if(transition->getId() == a.source)
////            {
////                sourceItem = transition;
////                continue;}
////            if(transition->getId() == a.target)
////            {
////                targetItem = transition;
////                continue;
////            }
////        }
////        QPainterPath path(sourceItem->boundingRect().center());

////        foreach(QPointF p, a.points)
////            path.lineTo(p);

////        path.lineTo(targetItem->boundingRect ().center());
////        Arcus * arc = new Arcus(sourceItem, targetItem, path, a);
////        if(sourceItem->type() == Place::Type)
////            qgraphicsitem_cast<Place*>(sourceItem)->addOutputArc(arc);
////        else if(sourceItem->type() == Transition::Type)
////            qgraphicsitem_cast<Transition*>(sourceItem)->addOutputArc(arc);
////        if(targetItem->type() == Place::Type)
////            qgraphicsitem_cast<Place*>(targetItem)->addInputArc(arc);
////        else if(targetItem->type() == Transition::Type)
////            qgraphicsitem_cast<Transition*>(targetItem)->addInputArc(arc);
////        com->mynet->AddArc(arc);


////    return  com->getID();
//}

QString ComponentList::addNewComponent(QString CompName)
{
    foreach(COMPONENT_ATTR compAttr,m_lComponentAttr)
    {
        if(compAttr.name==CompName)
        {
            QString compID=addComponentInSimulation(compAttr);
            //qDebug()<<"the new component's id is "<<compID;
            return compID;
        }
    }
    return QString();
}

const QList<Connector *> ComponentList::getConnectorList()
{
    return  this->connectList;
}

void ComponentList::push_back_connectorList(Connector *c)
{
    this->connectList.push_back(c);
    this->m_lConnector.push_back(c->toXml());
}

void ComponentList::deleteArc(QString placeId, QString transitionID)
{
    foreach(QGraphicsItem*item,this->m_Scene->items())
    {
        if(item->type()==QGraphicsItemGroup::Type)
        {
            foreach(QGraphicsItem*i,item->childItems())
            {
                Arcus*a=qgraphicsitem_cast<Arcus*>(i);
                if((a->getSourceId()==placeId&&a->getTargetId()==transitionID)||(a->getSourceId()==transitionID&&a->getTargetId()==placeId))
                {
                    this->m_Scene->removeItem(a);
                    break;
                }
            }
        }
        else if(item->type()==Arcus::Type)
        {
            Arcus*a=qgraphicsitem_cast<Arcus*>(item);
            if((a->getSourceId()==placeId&&a->getTargetId()==transitionID)||(a->getSourceId()==transitionID&&a->getTargetId()==placeId))
            {
                this->m_Scene->removeItem(a);
                break;
            }
        }
    }
}

Component *ComponentList::OriginComponent(QString Filename)
{

    //PTNscene* sce=new PTNscene();
    //sce->from_Xml(comController->getXMLpages(Filename));
    //Component *Com=new Component(comController->getPTnet(Filename),sce);
    Component *Com=this->comController->getComponent(Filename);
    return Com;
}

//分开之后，将原来的place恢复为初始状态//需要讨论
//todo（1.1号之后）
//需要针对transition与transition、transition与place进行单独处理
//transition与transition：删除复合transition，新建两个新的transition，把连接好的相关边进行分配
//transition与place：直接删除相关边即可（判断两种情况——连接方向）
void ComponentList::seperateCompoundPort(QString CompoundPortID)
{

////    QStringList id=CompoundPortID.split("+");
////    //下面认为place作为端口时，input与output应该有一个为空
////    if(id[0].split("&")[2][0]=="p"&&id[1].split("&")[2][0]=="p")
////    {
////        QString ID1=id[0];
////        QString comID1=ID1.split("&")[0]+"&"+ID1.split("&")[1];
////        QString ID2=id[1];
////        QString comID2=ID2.split("&")[0]+"&"+ID2.split("&")[1];
////        Place *p1=new Place();
////        Place*p2=new Place();
////        p1->setPlaceID(ID1);
////        p2->setPlaceID(ID2);
////        QString FName1=ID1.split("&")[0];
////        QString FName2=ID2.split("&")[0];

////        Component*com1=this->OriginComponent(FName1);
////        //暂时
////        p1->setTokens(com1->getCertainPlaceByName(ID1.split("&")[2])->getTokens());
////        p1->setCapacity(com1->getCertainPlaceByName(ID1.split("&")[2])->getCapacity());
////        Component*com2=this->OriginComponent(FName2);
////        p2->setTokens(com2->getCertainPlaceByName(ID2.split("&")[2])->getTokens());
////        p2->setCapacity(com2->getCertainPlaceByName(ID2.split("&")[2])->getCapacity());


////        p1->setcontain_portNum(1);
////        p2->setcontain_portNum(1);
////        p1->setCompoundPort(false);
////        p2->setCompoundPort(false);
////        QList<Arc*>l1;
////        QList<Arc*>l2;
////        Place*compoundPort=this->getCertainPlace(CompoundPortID);

////        for(int i=0;i<compoundPort->getinput().size();i++)
////        {
////            QString arcComID=compoundPort->getinput()[i]->getId().split("&")[0]+"&"+compoundPort->getinput()[i]->getId().split("&")[1];
////            if(arcComID==comID1)
////            {
////                l1.push_back(compoundPort->getoutput()[i]);

////            }
////        }



////        for(int i=0;i<compoundPort->getoutput().size();i++)
////        {
////            QString arcComID=compoundPort->getoutput()[i]->getId().split("&")[0]+"&"+compoundPort->getoutput()[i]->getId().split("&")[1];
////            if(arcComID==comID1)
////            {
////                l2.push_back(compoundPort->getoutput()[i]);
////            }
////        }

////        if(compoundPort->getoutput().size()==0)
////        {
////            p1->setOutputPort(true);
////            p2->setOutputPort(true);

////            p1->setInputPort(false);
////            p2->setInputPort(false);

////            for(int i=0;i<l1.size();i++)
////            {
////                l1[i]->setTargetId(ID1);
////                l1[i]->setTargetItem(p1);
////            }

////            for(int i=0;i<l2.size();i++)
////            {
////                l2[i]->setTargetId(ID2);
////                l2[i]->setTargetItem(p2);
////            }

////        }

////        else if(compoundPort->getinput().size()==0)
////        {
////            p1->setInputPort(true);
////            p2->setInputPort(true);

////            p1->setOutputPort(false);
////            p2->setOutputPort(false);

////            for(int i=0;i<l1.size();i++)
////            {
////                l1[i]->setsourceId(ID1);
////                l1[i]->setSourceItem(p1);
////            }

////            for(int i=0;i<l2.size();i++)
////            {
////                l2[i]->setsourceId(ID2);
////                l2[i]->setSourceItem(p2);
////            }
////        }

////        else
////        {
////            if((compoundPort->getinput()[0]->getId().split("&")[0]+"&"+compoundPort->getinput()[0]->getId().split("&")[1])==comID1)
////            {
////                p1->setOutputPort(true);
////                p2->setInputPort(true);
////                p1->setInputPort(false);
////                p2->setOutputPort(false);
////                for(int i=0;i<l1.size();i++)
////                {
////                    l1[i]->setTargetId(ID1);
////                    l1[i]->setTargetItem(p1);

////                }
////                for(int i=0;i<l2.size();i++)
////                {
////                    l1[i]->setsourceId(ID1);
////                    l1[i]->setSourceItem(p1);
////                }
////            }
////            else
////            {
////                p1->setOutputPort(false);
////                p2->setInputPort(false);
////                p1->setInputPort(true);
////                p2->setOutputPort(true);
////                for(int i=0;i<l1.size();i++)
////                {
////                    l1[i]->setsourceId(ID1);
////                    l1[i]->setSourceItem(p1);

////                }
////                for(int i=0;i<l2.size();i++)
////                {
////                    l1[i]->setTargetId(ID1);
////                    l1[i]->setTargetItem(p1);
////                }
////            }
////        }

////        for(int i=0;i<com_list.size();i++)
////        {
////            if(com_list[i]->getID()==comID1)
////            {
////                com_list[i]->mynet->PlaceList.push_back(p1);
////            }
////            else if(com_list[i]->getID()==comID2)
////            {
////                com_list[i]->mynet->PlaceList.push_back(p2);
////            }
////        }

////        for(int i=0;i<com_list.size();i++)
////        {
////            if(com_list[i]->getID()==comID1)
////            {
////                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
////                {
////                    if(com_list[i]->getPlaceList()[y]->getId()==CompoundPortID)
////                    {
////                        com_list[i]->mynet->PlaceList.removeAt(y);
////                    }
////                }
////            }
////            else if(com_list[i]->getID()==comID2)
////            {
////                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
////                {
////                    if(com_list[i]->getPlaceList()[y]->getId()==CompoundPortID)
////                    {
////                        com_list[i]->mynet->PlaceList.removeAt(y);
////                    }
////                }
////            }
////        }


////        //如何将新创建的place添加到scene中
////        this->Scene->addItem(p1);
////        this->Scene->addItem(p2);
////        this->Scene->removeItem(compoundPort);

////    }

////    else if(id[0].split("&")[2][0]=="t"&&id[1].split("&")[2][0]=="t")
////    {
////        Transition*t1=new Transition();
////        Transition*t2=new Transition();
////        t1->setCompoundPort(false);
////        t2->setCompoundPort(false);
////        QString ID1=id[0];
////        QString comID1=ID1.split("&")[0]+"&"+ID1.split("&")[1];
////        QString ID2=id[1];
////        QString comID2=ID2.split("&")[0]+"&"+ID2.split("&")[1];
////        t1->setID(ID1);
////        t2->setID(ID2);
////        t1->setName(ID1.split("&")[2]);
////        t2->setName(ID2.split("&")[2]);
////        QList<Arc*>t1_in;
////        QList<Arc*>t1_out;
////        QList<Arc*>t2_in;
////        QList<Arc*>t2_out;
////        Transition*t=getcertainTransition(CompoundPortID);
////        for(int i=0;i<t->getinput().size();i++)
////        {
////            QString cID=t->getinput()[i]->getId().split("&")[0]+"&"+t->getinput()[i]->getId().split("&")[1];
////            if(cID==comID1)
////            {
////                t1_in.push_back(t->getinput()[i]);
////            }
////            else if(cID==comID2)
////            {
////                t2_in.push_back(t->getinput()[i]);
////            }
////        }
////        for(int i=0;i<t->getoutput().size();i++)
////        {
////            QString cID=t->getoutput()[i]->getId().split("&")[0]+"&"+t->getoutput()[i]->getId().split("&")[1];
////            if(cID==comID1)
////            {
////                t1_out.push_back(t->getoutput()[i]);
////            }
////            else if(cID==comID2)
////            {
////                t2_out.push_back(t->getoutput()[i]);
////            }
////        }

////        for(int i=0;i<t1_in.size();i++)
////        {
////            t1->pushInput(t1_in[i]);
////        }

////        for(int i=0;i<t1_out.size();i++)
////        {
////            t1->pushOutput(t1_out[i]);
////        }
////        for(int i=0;i<t2_in.size();i++)
////        {
////            t2->pushInput(t2_in[i]);
////        }

////        for(int i=0;i<t2_out.size();i++)
////        {
////            t2->pushOutput(t2_out[i]);
////        }


////        for(int i=0;i<com_list.size();i++)
////        {
////            if(com_list[i]->getID()==comID1)
////            {
////                com_list[i]->mynet->TransitionList.push_back(t1);
////            }
////            else if(com_list[i]->getID()==comID2)
////            {
////                com_list[i]->mynet->TransitionList.push_back(t2);
////            }
////        }

////        for(int i=0;i<com_list.size();i++)
////        {
////            if(com_list[i]->getID()==comID1)
////            {
////                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
////                {
////                    if(com_list[i]->getTransitionList()[y]->getId()==CompoundPortID)
////                    {
////                        com_list[i]->mynet->TransitionList.removeAt(y);
////                    }
////                }
////            }
////            else if(com_list[i]->getID()==comID2)
////            {
////                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
////                {
////                    if(com_list[i]->getTransitionList()[y]->getId()==CompoundPortID)
////                    {
////                        com_list[i]->mynet->TransitionList.removeAt(y);
////                    }
////                }
////            }
////        }

////        this->Scene->addItem(t1);
////        this->Scene->addItem(t2);
////        this->Scene->removeItem(t);

////    }
//    QStringList ids=CompoundPortID.split("+");

//    if(ids[0].split("&")[2]=="p"&&ids[1].split("&")[2]=="p")
//    {
//        Place*p=getCertainPlace(CompoundPortID);
//        Place*p1=new Place();
//        p1->setPlaceID(ids[0]);
//        Place*p2=new Place();
//        p2->setPlaceID(ids[1]);
//        Component*com1=OriginComponent(p1->getFileName()[0]);
//        Component*com2=OriginComponent(p2->getFileName()[0]);

//        foreach(Place*p3,com1->mynet->PlaceList)
//        {
//            if(p3->getId().split("&")[2]==p1->getId().split("&")[2])
//            {
//                p1->setTokens(p3->getTokens());
//                p1->setCapacity(p3->getCapacity());
//                //bug 此处因为输出端口与输入端口的属性对于目前不重要，因此没有设置
//            }
//        }

//        foreach(Place*p3,com2->mynet->PlaceList)
//        {
//            if(p3->getId().split("&")[2]==p2->getId().split("&")[2])
//            {
//                p2->setTokens(p3->getTokens());
//                p2->setCapacity(p3->getCapacity());
//                //bug 此处因为输出端口与输入端口的属性对于目前不重要，因此没有设置
//            }
//        }

//        //bug,没有处理新增的arc
//        for(int i=0;i<p->input.size();i++)
//        {
//            QString arc_cid=p->input[i]->getId().split("&")[0]+"&"+p->input[i]->getId().split("&")[1];
//            if(arc_cid==p1->getComponentID()[0])
//            {
//                p->input[i]->setTargetId(p1->getId());
//                p->input[i]->setTargetItem(p1);
//                p1->input.push_back(p->input[i]);
//            }
//            else if(arc_cid==p2->getComponentID()[0])
//            {
//                p->input[i]->setTargetId(p2->getId());
//                p->input[i]->setTargetItem(p2);
//                p2->input.push_back(p->input[i]);
//            }
//        }

//        for(int i=0;i<p->output.size();i++)
//        {
//            QString arc_cid=p->output[i]->getId().split("&")[0]+"&"+p->output[i]->getId().split("&")[1];
//            if(arc_cid==p1->getComponentID()[0])
//            {
//                p->output[i]->setsourceId(p1->getId());
//                p->output[i]->setSourceItem(p1);
//                p1->output.push_back(p->output[i]);
//            }
//            else if(arc_cid==p2->getComponentID()[0])
//            {
//                p->output[i]->setTargetId(p2->getId());
//                p->output[i]->setTargetItem(p2);
//                p2->output.push_back(p->output[i]);
//            }
//        }
//        this->Scene->addItem(p1);
//        this->Scene->addItem(p2);
//        this->Scene->removeItem(p);

//    }
//    else if(ids[0].split("&")[2]=="t"&&ids[1].split("&")[2]=="t")
//    {
//        Transition*p=getcertainTransition(CompoundPortID);
//        Transition*p1=new Transition();
//        p1->setID(ids[0]);
//        Transition*p2=new Transition();
//        p2->setID(ids[1]);

//        //bug,没有处理新增的arc
//        for(int i=0;i<p->input.size();i++)
//        {
//            QString arc_cid=p->input[i]->getId().split("&")[0]+"&"+p->input[i]->getId().split("&")[1];
//            if(arc_cid==p1->getComponentID()[0])
//            {
//                p->input[i]->setTargetId(p1->getId());
//                p->input[i]->setTargetItem(p1);
//                p1->input.push_back(p->input[i]);
//            }
//            else if(arc_cid==p2->getComponentID()[0])
//            {
//                p->input[i]->setTargetId(p2->getId());
//                p->input[i]->setTargetItem(p2);
//                p2->input.push_back(p->input[i]);
//            }
//        }

//        for(int i=0;i<p->output.size();i++)
//        {
//            QString arc_cid=p->output[i]->getId().split("&")[0]+"&"+p->output[i]->getId().split("&")[1];
//            if(arc_cid==p1->getComponentID()[0])
//            {
//                p->output[i]->setsourceId(p1->getId());
//                p->output[i]->setSourceItem(p1);
//                p1->output.push_back(p->output[i]);
//            }
//            else if(arc_cid==p2->getComponentID()[0])
//            {
//                p->output[i]->setTargetId(p2->getId());
//                p->output[i]->setTargetItem(p2);
//                p2->output.push_back(p->output[i]);
//            }
//        }
//        this->Scene->addItem(p1);
//        this->Scene->addItem(p2);
//        this->Scene->removeItem(p);
//    }
}


void ComponentList::deleteComponent(QString ComponentID)
{
    if(ComponentID.split('&').size()==2)
    {
        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==ComponentID)
            {
                garbage2.push_back(com_list[i]);
                com_list.remove(i);

            }
        }
    }
    else if(ComponentID.split('&').size()==1)
    {
        QVector<int>index;
        index.reserve(com_list.size());
        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID().split('&')[0]==ComponentID)
                index.push_back(i);
        }
        if(index.size()==1)
        {
            garbage2.push_back(com_list[index[0]]);
            com_list.remove(index[0]);
        }
        else
        {
            srand(static_cast<unsigned int>(time(0)));
            int remove=rand()%index.size();
            garbage2.push_back(com_list[index[remove]]);
            com_list.remove(index[remove]);
        }
    }
//    QString Filename=ComponentID.split("&")[0];
//    for(int z=0;z<com_list.size();z++)
//    {
//        if(com_list[z]->getID()==ComponentID)
//        {
//            Component*com=new Component;
//            com=com_list[z];
//            PTNscene*s=new PTNscene();

//            //断开所有复合端口
//            for(int y=0;y<com->mynet->PlaceList.size();y++)
//            {
//                if(com->mynet->PlaceList[y]->isACompoundPort())
//                {
//                    this->seperateCompoundPort(com->mynet->PlaceList[y]->getId());
//                }
//            }

//            for(int m=0;m<com->mynet->TransitionList.size();m++)
//            {
//                if(com->mynet->TransitionList[m]->IsCompoundPort())
//                {
//                    this->seperateCompoundPort(com->mynet->TransitionList[m]->getId());
//                }
//            }

//            //删除该组件连向外部的新创建的弧
//            foreach(QGraphicsItem * item, this->Scene->items())
//            {
//                if(item->type() == Arc::Type)
//                {
//                    Arc*a= qgraphicsitem_cast<Arc*>(item);
//                    QStringList id=a->getId().split("+");
//                    if(id.size()==3)
//                    {
//                        for(int b=0;b<2;b++)
//                        {
//                            QString comID=id[b].split("&")[0]+"&"+id[b].split("&")[1];
//                            if(comID==ComponentID)
//                            {
//                                this->Scene->removeItem(a);
//                            }
//                        }
//                    }
//                }
//            }


//            for(int i=0;i<com->mynet->PlaceList.size();i++)
//            {

//                s->addItem(com->mynet->PlaceList[i]);
//            }
//            for(int i=0;i<com->mynet->TransitionList.size();i++)
//            {
//                s->addItem(com->mynet->TransitionList[i]);
//            }

//            for(int i=0;i<com->mynet->ArcList.size();i++)
//            {
//                s->addItem(com->mynet->ArcList[i]);
//            }
//            garbage.insert(ComponentID,s);
//            com_list.remove(z);
//        }
//    }
    //遍历所有元素，判断该元素的组号与当前传入的组号是否相等，如果相等就把它移到垃圾站
    //特别注意，如果该元素为复合端口时（判断ID的格式），要先把它断开
    //还有对与弧的处理要注意，遍历所有弧，如果弧ID的第一位为N则直接删除
//    PTNscene*s=new PTNscene();
//    QList<Place*>pl;
//    QList<Transition*>tl;
//    QList<Arc*>al;
//    QList<Place*>compound_pl;
//    QList<Transition*>compound_tl;
//    //断开复合端口
//    //bug,一边遍历一边删除有可能会出现与QList.size()一样的错误
//    foreach(QGraphicsItem*item,this->Scene->items())
//    {
//        if(item->type()==Place::Type)
//        {
//            Place*p=qgraphicsitem_cast<Place*>(item);
//            if(p->getComponentID().size()==2&&p->getComponentID().contains(ComponentID))
//            {
//                this->seperateCompoundPort(p->getId());
//            }
//        }
//        else if(item->type()==Transition::Type)
//        {
//            Transition*t=qgraphicsitem_cast<Transition*>(item);
//            if(t->getComponentID().size()==2&&t->getComponentID().contains(ComponentID))
//            {
//                this->seperateCompoundPort(t->getId());
//            }
//        }
//        else if(item->type()==Arc::Type)
//        {
//            Arc*a=new Arc();
//            if(a->getId()[0]=="N"&&a->getId()[1]=="+")
//            {
//                if(a->getId().split("+")[1].split("&")[0]+"&"+a->getId().split("+")[1].split("&")[1]==ComponentID||a->getId().split("+")[2].split("&")[0]+"&"+a->getId().split("+")[2].split("&")[1]==ComponentID)
//                {
//                    this->Scene->removeItem(a);
//                }
//            }
//        }

//    }

//    //作出修改，不再将元素内的token恢复到初始值
//    foreach(QGraphicsItem*item,this->Scene->items())
//    {
//        if(item->type()==Place::Type)
//        {
//            Place*p=qgraphicsitem_cast<Place*>(item);
//            if(p->getComponentID().contains(ComponentID))
//            {

//                s->addItem(p);
//            }
//        }
//        else if(item->type()==Transition::Type)
//        {
//            Transition*t=qgraphicsitem_cast<Transition*>(item);
//            if(t->getComponentID().contains(ComponentID))
//            {
//                s->addItem(t);
//            }
//        }
//        else if(item->type()==Arc::Type)
//        {
//            Arc*a=new Arc();
//            if(a->getId().split("&")[0]+"&"+a->getId().split("&")[1]==ComponentID)
//            {
//                s->addItem(a);
//            }
//        }

//    }

//    garbage.insert(ComponentID,s);

}

void ComponentList::recoverComponent(QString ComponentID)
{
//    QMapIterator<QString,PTNscene*>it(this->garbage);
//    Component*com=new Component();
//    PTNscene*s=new PTNscene;
//    while (it.hasNext()) {
//        it.next();
//        if(it.key()==ComponentID)
//        {
//            s=it.value();
//        }
//    }

//    foreach(QGraphicsItem*item,s->items())
//    {
//        if(item->type()==Place::Type)
//        {
//            Place * place = qgraphicsitem_cast<Place*>(item);
//            com->mynet->PlaceList.push_back(place);
//            Scene->addItem(place);

//        }
//        else if(item->type()==Transition::Type)
//        {
//            Transition * place = qgraphicsitem_cast<Transition*>(item);
//            com->mynet->TransitionList.push_back(place);
//            Scene->addItem(place);

//        }
//        else if(item->type()==Arc::Type)
//        {
//            Arc * place = qgraphicsitem_cast<Arc*>(item);
//            com->mynet->ArcList.push_back(place);
//            Scene->addItem(place);

//        }

//    }
//    com_list.push_back(com);
    //2
//    QMapIterator<QString,PTNscene*>it(this->garbage);
//    while (it.hasNext()) {
//        it.next();
//        if(it.key()==ComponentID)
//        {
//            Component*com=OriginComponent(ComponentID.split("&")[0]);
//            com->setID(ComponentID);
//            foreach(Place*p,com->mynet->PlaceList)
//            {
//                this->Scene->addItem(p);
//            }
//            foreach(Transition*p,com->mynet->TransitionList)
//            {
//                this->Scene->addItem(p);
//            }
//            foreach(Arc*p,com->mynet->ArcList)
//            {
//                this->Scene->addItem(p);
//            }

//        }
//    }
//    QMap<QString,PTNscene*>::iterator iter;
//    for(iter=garbage.begin();iter!=garbage.end();iter++)
//    {
//        if(iter.key()==ComponentID)
//        {
//            garbage.erase(iter);
//            break;
//        }
//    }
    for(int i=0;i<garbage2.size();i++)
    {
        if(garbage2[i]->getID()==ComponentID)
        {
            com_list.push_back(garbage2[i]);
            garbage2.removeAt(i);
        }
    }

}

QVector<Component*> ComponentList::getComponentList()
{
    return com_list;
}

void ComponentList::setComponentStep(QString ComponentName,double step)
{
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID().split('&')[0]==ComponentName)
        {
            com_list[i]->setStep(step);
        }
    }
}

ComponentList::ComponentList(ComponentList* source)
{
//    Scene=source->Scene;待处理
    m_Scene=new PTNscene();
    m_View=new QGraphicsView();
    comController=source->comController;
    m_lConnector=source->m_lConnector;
    m_mComp2Count=source->m_mComp2Count;
    m_lComponentAttr=source->m_lComponentAttr;
    Component*p;
    for(int i = 0; i < source->com_list.size();i++)
    {
        p=new Component(source->com_list[i]);
        com_list.push_back(p);
        p=nullptr;
    }
//    for(unsigned int i = 0; i< source->connectList.size();i++)
//    {
//        m_lConnector.push_back(source->connectList[i]->toXml());
//    }
}

QList<CONNECTOR_ATTR> ComponentList::getConnectorAttrList()
{
    return m_lConnector;
}

bool ComponentList::simulateStructChanged()
{
    int l_length=com_list.size();
    if(l_length>=2)
    {
        Component*l_compPtr=com_list[l_length-1];
        QString l_compId=l_compPtr->getID();
        com_list.pop_back();
        QList<CONNECTOR_ATTR>l_lConnectorTemp;
        for(int i = 0;i<m_lConnector.size();i++)
        {
            if(!(m_lConnector[i].source.contains(l_compId,Qt::CaseSensitive))
                    &&!(m_lConnector[i].target.contains( l_compId,Qt::CaseSensitive)))
               l_lConnectorTemp.push_back(m_lConnector[i]);
        }
        m_lConnector=l_lConnectorTemp;
        return true;
    }
    return false;
}

void ComponentList::show()
{
    for(int i =0;i<com_list.size();i++)
    {
        qDebug()<<"the "<<i<<" component's id is"<<com_list[i]->getID();
    }
    for(int i = 0;i<connectList.size();i++)
        qDebug()<<"the "<<i<<" connector is from "<<connectList[i]->getSourceId()<<" to "<<connectList[i]->getTargetId();
}

bool ComponentList::setComponentController(ComponentController*scr)
{
    if(!scr)
        return false;
    comController=scr;
    return true;
}

ComponentList::ComponentList(PTNscene * scene,QGraphicsView * view)
{
   m_Scene=scene;
   m_View=view;
   m_mComp2Count.clear();
}

ComponentList::ComponentList(PTNscene * scene,QGraphicsView * view,QMap<QString,int>Comp2Count)
{
   m_Scene=scene;
   m_View=view;
   m_mComp2Count=Comp2Count;
}

void ComponentList::addComponents(QList<COMPONENT_ATTR>componentlist)
{
    foreach(COMPONENT_ATTR componentAttr,componentlist)
    {
        QString name=componentAttr.name;
        int temp=0;
        //如果为旧组件
        if(m_mComp2Count.contains(name))
        {
            temp=m_mComp2Count.value(componentAttr.name);
        }
        else
        {
            //保存新组件的结构信息
            m_lComponentAttr.push_back(componentAttr);
        }
        com_list.push_back( new Component(m_Scene,m_View,componentAttr,temp));
        //更新组件信息
        temp++;
        m_mComp2Count[name]=temp;
    }
}

QString ComponentList::addComponent(COMPONENT_ATTR componentAttr)
{
        QString name=componentAttr.name;
        int temp=0;
        //如果为旧组件
        if(m_mComp2Count.contains(name))
        {
            temp=m_mComp2Count.value(componentAttr.name);
        }
        else
        {
            //保存新组件的结构信息(拓展：如果需要一个页面对应一个组件库)
//            m_lComponentAttr.push_back(componentAttr);
        }
        com_list.push_back( new Component(m_Scene,m_View,componentAttr,temp));
        //更新组件信息
        temp++;
        m_mComp2Count[name]=temp;
        return name+'&'+QString::number(temp--);
}

QString ComponentList::addComponentInSimulation(COMPONENT_ATTR componentAttr)
{
        QString name=componentAttr.name;
        int temp=0;
        //如果为旧组件
        if(m_mComp2Count.contains(name))
        {
            temp=m_mComp2Count.value(componentAttr.name);
        }
        else
        {
            //保存新组件的结构信息(拓展：如果需要一个页面对应一个组件库)
//            m_lComponentAttr.push_back(componentAttr);
        }
        com_list.push_back( new Component(componentAttr,temp));
        //更新组件信息
        temp++;
        m_mComp2Count[name]=temp;
        return name+'&'+QString::number(--temp);
}

void ComponentList::addComponent(Component* component)
{
    com_list.push_back(component);
}
void ComponentList::editComponentID(QString oldName,QString newName)
{
//    QStringList compID;
//    for(int i=0;i<com_list.size();i++)
//    {
//        compID=com_list[i]->getID().split('&');
//        if(compID[0]==oldID)
//        {
//            com_list[i]->setID(newID+'&'+compID[1]);
//        }
//    }
}

void ComponentList::checkConnectorAttrList()
{
    QList<CONNECTOR_ATTR> result;
    QString sourceCompId,targetCompId;
    for(int i=0;i<m_lConnector.size();i++)
    {
        sourceCompId=m_lConnector[i].source.split('&')[0];
        targetCompId=m_lConnector[i].target.split('&')[0];
        if(m_mComp2Count.contains(sourceCompId)&&m_mComp2Count.contains(targetCompId))
        {
            result<<m_lConnector[i];
        }
        else {
            qDebug()<<"connector from "<<m_lConnector[i].source<<" to "<<m_lConnector[i].target<<" is invalid";
        }
    }
    m_lConnector=result;
}

bool ComponentList::containComponent(QString componentName)
{
    foreach(Component* component,com_list)
    {
        if(component->getFileName()==componentName)
        {
            return true;
        }
    }
    return false;
}

void ComponentList::getComponentAttr(QList<COMPONENT_ATTR>compAttrList)
{
    m_lComponentAttr=compAttrList;
}

bool ComponentList::checkComponent(QString ComponentID)
{
    foreach(Component*component,com_list)
    {
        if(component->getID()==ComponentID)
            return true;
    }
    return false;
}
