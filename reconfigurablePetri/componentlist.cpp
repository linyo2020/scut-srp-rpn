#include "componentlist.h"

ComponentList::ComponentList()
{
    Scene=new PTNscene();
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
    //端口均为place
//    if(portID1.split("&")[2][0]=="p"&&portID2.split("&")[2][0]=="p")
//    {
//        QString placeID=portID1+"+"+portID2;
//        Place*p1=getCertainPlace(portID1);
//        Place*p2=getCertainPlace(portID2);
//        Place *P=new Place();
//        P->setPlaceID(placeID);
//        //！！设置name
//        P->setName(portID1.split("&")[2]+"+"+portID2.split("&")[2]);
//        P->setCapacity(getCertainPlace(portID1)->getCapacity()+getCertainPlace(portID2)->getCapacity());
//        P->setTokens(getCertainPlace(portID1)->getTokens()+getCertainPlace(portID2)->getTokens());
//        P->setInputPort(true);
//        P->setOutputPort(true);
//        P->setCompoundPort(true);
//        P->setcontain_portNum(P->getcontain_portNum()+1);
//        QString comID1=portID1.split("&")[0]+"&"+portID1.split("&")[1];
//        QString comID2=portID2.split("&")[0]+"&"+portID2.split("&")[1];
//        foreach(Arc* a,p1->getinput())
//        {
//            a->setTargetId(placeID);
//            a->setTargetItem(P);
//        }
//        foreach(Arc* a,p1->getoutput())
//        {
//            a->setsourceId(placeID);
//            a->setSourceItem(P);
//        }
//        foreach(Arc* a,p2->getinput())
//        {
//            a->setTargetId(placeID);
//            a->setTargetItem(P);
//        }
//        foreach(Arc* a,p2->getoutput())
//        {
//            a->setsourceId(placeID);
//            a->setSourceItem(P);
//        }

//        for(int i=0;i<com_list.size();i++)
//        {
//            if(com_list[i]->getID()==comID1||com_list[i]->getID()==comID2)
//            {
//                com_list[i]->mynet->PlaceList.push_back(P);
//            }
//        }

//        for(int i=0;i<com_list.size();i++)
//        {
//            if(com_list[i]->getID()==comID1)
//            {
//                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
//                {
//                    if(com_list[i]->getPlaceList()[y]->getId()==portID1)
//                    {
//                        com_list[i]->mynet->PlaceList.removeAt(y);
//                    }
//                }
//            }
//            else if(com_list[i]->getID()==comID2)
//            {
//                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
//                {
//                    if(com_list[i]->getPlaceList()[y]->getId()==portID2)
//                    {
//                        com_list[i]->mynet->PlaceList.removeAt(y);
//                    }
//                }
//            }
//        }



//        this->Scene->addItem(P);

//        this->Scene->removeItem(p1);
//        this->Scene->removeItem(p2);
//    }
//    //均为transition
//    else if(portID1.split("&")[2][0]=="t"&&portID2.split("&")[2][0]=="t")
//    {
//        Transition*t1=getcertainTransition(portID1);
//        Transition*t2=getcertainTransition(portID2);
//        Transition*newTrans=new Transition();
//        QString transID=t1->getId()+"+"+t2->getId();
//        newTrans->setID(transID);
//        //todo
//        //newTrans->setName();

//        newTrans->setCompoundPort(true);
//        QString comID1=portID1.split("&")[0]+"&"+portID1.split("&")[1];
//        QString comID2=portID2.split("&")[0]+"&"+portID2.split("&")[1];
//        foreach(Arc* a,t1->getinput())
//        {
//            a->setTargetId(transID);
//            a->setTargetItem(newTrans);
//        }
//        foreach(Arc* a,t1->getoutput())
//        {
//            a->setsourceId(transID);
//            a->setSourceItem(newTrans);
//        }
//        foreach(Arc* a,t2->getinput())
//        {
//            a->setTargetId(transID);
//            a->setTargetItem(newTrans);
//        }
//        foreach(Arc* a,t2->getoutput())
//        {
//            a->setsourceId(transID);
//            a->setSourceItem(newTrans);
//        }

//        for(int i=0;i<com_list.size();i++)
//        {
//            if(com_list[i]->getID()==comID1||com_list[i]->getID()==comID2)
//            {
//                com_list[i]->mynet->TransitionList.push_back(newTrans);
//            }
//        }

//        for(int i=0;i<com_list.size();i++)
//        {
//            if(com_list[i]->getID()==comID1)
//            {
//                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
//                {
//                    if(com_list[i]->getTransitionList()[y]->getId()==portID1)
//                    {
//                        com_list[i]->mynet->TransitionList.removeAt(y);
//                    }
//                }
//            }
//            else if(com_list[i]->getID()==comID2)
//            {
//                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
//                {
//                    if(com_list[i]->getTransitionList()[y]->getId()==portID2)
//                    {
//                        com_list[i]->mynet->TransitionList.removeAt(y);
//                    }
//                }
//            }
//        }

//        this->Scene->addItem(newTrans);

//        this->Scene->removeItem(t1);
//        this->Scene->removeItem(t2);

//    }

//    else if(portID1.split("&")[2][0]=="p"&&portID2.split("&")[2][0]=="t")
//    {
//        Place*p=getCertainPlace(portID1);
//        Transition*t=getcertainTransition(portID2);
//        Arc*a=new Arc();
//        a->setID(portID1.split("&")[0]+"&"+portID1.split("&")[1]+"+"+portID2.split("&")[0]+"&"+portID2.split("&")[1]+"+"+"N");
//        a->setTargetId(t->getId());
//        a->setTargetItem(t);
//        //t->merge_input.push_back(a);
//        a->setsourceId(p->getId());
//        a->setSourceItem(p);
//        //p->merge_output.push_back(a);
//        this->Scene->addItem(a);
//    }

//    else if(portID1.split("&")[2][0]=="t"&&portID2.split("&")[2][0]=="p")
//    {
//        Place*p=getCertainPlace(portID2);
//        Transition*t=getcertainTransition(portID1);
//        Arc*a=new Arc();
//        a->setID(portID1.split("&")[0]+"&"+portID1.split("&")[1]+"+"+portID2.split("&")[0]+"&"+portID2.split("&")[1]+"+" + "N");
//        a->setTargetId(p->getId());
//        a->setTargetItem(p);

//        //p->merge_input.push_back(a);
//        a->setsourceId(t->getId());
//        a->setSourceItem(t);
//        //t->merge_output.push_back(a);
//        this->Scene->addItem(a);
//    }

    if(portID1.split("&")[2][0]=="p"&&portID2.split("&")[2][0]=="p")
    {
        QGraphicsItem * sourceItem = 0;
        QGraphicsItem * targetItem = 0;
        foreach(Component* com,com_list)
        {

            foreach(Place * place,com->mynet->PlaceList)
            {
                if(place->getId() == portID1)
                {
                    sourceItem = place;
                    continue;

                }
                if(place->getId() == portID2)
                {
                    targetItem = place;
                    continue;
                }
            }

        }
        Connector* con=new Connector(sourceItem,portID1,targetItem,portID2,portID1+"+"+portID2);
        con->setSourceItem(sourceItem);
        qgraphicsitem_cast<Place*>(sourceItem)->addOutputArc(con);
        qgraphicsitem_cast<Place*>(targetItem)->addInputArc(con);
        connectList.append(con);
//        p->setTokens(p1->getTokens()+p2->getTokens());
//        p->setCapacity(p1->getCapacity()+p2->getCapacity());
//        p->setCompoundPort(true);
//        p->setPlaceID(p1->getId()+"+"+p2->getId());
//        p->input.append(p1->input);
//        p->input.append(p2->input);
//        p->output.append(p1->output);
//        p->output.append(p2->output);
//        this->Scene->removeItem(p1);
//        this->Scene->removeItem(p2);
//        this->Scene->addItem(p);

    }
//    else if(portID1.split("&")[2][0]=="t"&&portID2.split("&")[2][0]=="t")
//    {
//        Transition*p=new Transition();
//        Transition*p1=getcertainTransition(portID1);
//        Transition*p2=getcertainTransition(portID2);
//        p->setCompoundPort(true);
//        p->setID(p1->getId()+"+"+p2->getId());
//        p->input.append(p1->input);
//        p->input.append(p2->input);
//        p->output.append(p1->output);
//        p->output.append(p2->output);
//        this->Scene->removeItem(p1);
//        this->Scene->removeItem(p2);
//        this->Scene->addItem(p);
//    }

//    else
//    {
//        Arc*a=new Arc();
//        if(portID1.split("&")[2][0]=="p")
//        {
//            Place*p=getCertainPlace(portID1);
//            Transition*t=getcertainTransition(portID2);
//            QString id="N+"+p->getId()+"+"+t->getId();
//            a->setID(id);
//            a->setsourceId(p->getId());
//            a->setSourceItem(p);
//            a->setTargetId(t->getId());
//            a->setTargetItem(t);
//            this->Scene->addItem(a);
//        }
//        else
//        {
//            Place*p=getCertainPlace(portID2);
//            Transition*t=getcertainTransition(portID1);
//            QString id="N+"+t->getId()+"+"+p->getId();
//            a->setID(id);
//            a->setsourceId(t->getId());
//            a->setSourceItem(t);
//            a->setTargetId(p->getId());
//            a->setTargetItem(p);
//            this->Scene->addItem(a);
//        }
//    }
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

    foreach(QGraphicsItem*item,this->Scene->items())
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


QString ComponentList::addNewComponent(QString Filename)
{
//    Component*com=this->OriginComponent(Filename);
//    setnewComponentIDinSimulation(com);

//    foreach(Place* pl,com->getPlaceList())
//    {
//        Scene->addItem(pl);
//    }
//    foreach(Transition *tran,com->getTransitionList())
//    {
//        Scene->addItem(tran);
//    }
//    foreach(Arc* ar,com->getTArcList())
//    {
//        Scene->addItem(ar);
//    }

//    return com->getID();
    Component*com=this->OriginComponent(Filename);
    this->setnewComponentIDinSimulation(com);
    this->com_list.push_back(com);

}

const QList<Connector *> ComponentList::getConnectorList()
{
    return  this->connectList;
}

void ComponentList::push_back_connectorList(Connector *c)
{
    this->connectList.push_back(c);
}

void ComponentList::deleteArc(QString placeId, QString transitionID)
{
    foreach(QGraphicsItem*item,this->Scene->items())
    {
        if(item->type()==Arcus::Type)
        {
            Arcus*a=new Arcus();
            if((a->getSourceId()==placeId&&a->getTargetId()==transitionID)||(a->getSourceId()==transitionID&&a->getTargetId()==placeId))
            {
                this->Scene->removeItem(a);
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
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            garbage2.push_back(com_list[i]);
            com_list.remove(i);

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
