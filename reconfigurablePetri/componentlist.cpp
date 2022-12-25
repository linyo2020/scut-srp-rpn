#include "componentlist.h"

ComponentList::ComponentList(QObject *parent) : QObject(parent)
{

}

ComponentList::ComponentList(QVector<Component *> com_list, QVector<Component *> OriginComponent_List, PTNscene *Scene, componentController *comController)
{
    this->com_list=com_list;
    this->OriginComponent_List=OriginComponent_List;
    this->Scene=Scene;
    this->comController=comController;
}


Component *ComponentList::getCertainComponent(QString ComID)
{
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComID)
        {
            return com_list[i];
        }
    }
    return nullptr;
}

Place *ComponentList::getCertainPlace(QString PlaceID)
{
    QString comID=(PlaceID.split("+")[0].split("&")[0]+PlaceID.split("+")[0].split("&")[1]);
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==comID)
        {
            for(int i=0;i<com_list[i]->getPlaceList().size();i++)
            {
                if(com_list[i]->getPlaceList()[i]->getId()==PlaceID)
                {
                    return com_list[i]->getPlaceList()[i];
                }
            }
        }
    }
}

//仅返回普通端口
QList<Place *> ComponentList::getPortinComponent(QString ComponentID)
{
    QList<Place*>P;
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            for(int i=0;com_list[i]->getPlaceList().size();i++)
            {
                if(com_list[i]->getPlaceList()[i]->isNormalPort())
                {
                   P.push_back(com_list[i]->getPlaceList()[i]);
                }
            }
        }
    }
    return P;
}

QList<QString> ComponentList::getCertainPlaceName(QString ComponentID)
{
    QList<QString>list;
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            for(int i=0;i<com_list[i]->getPlaceList().size();i++)
            {
                Place*p=com_list[i]->getPlaceList()[i];
                QStringList ID=p->getId().split("+");
                for(int i=0;i<ID.size();i++)
                {
                    list.push_back(ID[i].split("&")[2]);
                }
            }

        }
    }
    return list;
}

QList<QString> ComponentList::getCertainTransitionName(QString ComponentID)
{
    QList<QString>list;
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            for(int i=0;i<com_list[i]->getTransitionList().size();i++)
            {
                Transition*p=com_list[i]->getTransitionList()[i];
                QString name=p->getId().split("&")[2];
                list.push_back(name);
            }

        }
    }
    return list;
}

QString ComponentList::setnewComponentIDinSimulation(Component *newComponent)
{
    int count=0;
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getComponentFileName()==newComponent->getComponentFileName())
        {
            count++;
        }
    }

    QMapIterator<QString,PTNscene*>it(this->garbage);
    Component*com=new Component();
    PTNscene*s=new PTNscene;
    while (it.hasNext()) {
        it.next();
        if(it.key().split("&")[0]==newComponent->getComponentFileName())
        {
            count++;
        }
    }

    newComponent->setID(newComponent->getComponentFileName()+QString::number(count));
    return (newComponent->getComponentFileName()+QString::number(count));
}

//对象不存在则无法合并
void ComponentList::addComponentPort(QString portID1, QString portID2)
{
    QString placeID=portID1+portID2;
    Place *P=new Place();
    P->setName(placeID);
    P->setCapacity(getCertainPlace(portID1)->getCapacity()+getCertainPlace(portID2)->getCapacity());
    P->setTokens(getCertainPlace(portID1)->getTokens()+getCertainPlace(portID2)->getTokens());
    P->setInputPort(true);
    P->setOutputPort(true);
    P->setCompoundPort(true);
    P->setcontain_portNum(P->getcontain_portNum()+1);
    QString comID1=portID1.split("&")[0]+portID1.split("&")[1];
    QString comID2=portID2.split("&")[0]+portID2.split("&")[1];
    foreach(Arc* a,getCertainPlace(portID1)->getinput())
    {
        a->setTargetId(placeID);
        a->setTargetItem(P);
    }
    foreach(Arc* a,getCertainPlace(portID1)->getoutput())
    {
        a->setsourceId(placeID);
        a->setSourceItem(P);
    }
    foreach(Arc* a,getCertainPlace(portID2)->getinput())
    {
        a->setTargetId(placeID);
        a->setTargetItem(P);
    }
    foreach(Arc* a,getCertainPlace(portID2)->getoutput())
    {
        a->setsourceId(placeID);
        a->setSourceItem(P);
    }

    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==comID1||com_list[i]->getID()==comID2)
        {
            com_list[i]->mynet->PlaceList.push_back(P);
        }
    }
    this->Scene->addItem(P);

    this->Scene->removeItem(getCertainPlace(portID1));
    this->Scene->removeItem(getCertainPlace(portID2));
}

Component *ComponentList::OriginComponent(QString Filename)
{

}

//分开之后，将原来的place恢复为初始状态//需要讨论
void ComponentList::seperateCompoundPort(QString CompoundPortID)
{
    QStringList id=CompoundPortID.split("+");
    QString ID1=id[0];
    QString comID1=ID1.split("&")[0]+ID1.split("&")[1];
    QString ID2=id[1];
    QString comID2=ID2.split("&")[0]+ID2.split("&")[1];
    Place *p1=new Place();
    Place*p2=new Place();
    p1->setPlaceID(ID1);
    p2->setPlaceID(ID2);
    double p1Token=0;
    double p2Token=0;
    double p1Capacity=0;
    double p2Capacity=0;
    QString FName1=ID1.split("&")[0];
    QString FName2=ID2.split("&")[0];
    for(int i=0;i<OriginComponent_List.size();i++)
    {
        if(OriginComponent_List[i]->getID().split("&")[0]==FName1)
        {
            p1Token=OriginComponent_List[i]->getCertainPlaceByName(ID1.split("&")[2])->getTokens();
            p1Capacity=OriginComponent_List[i]->getCertainPlaceByName(ID1.split("&")[2])->getCapacity();
        }

        if(OriginComponent_List[i]->getID().split("&")[0]==FName2)
        {
            p1Token=OriginComponent_List[i]->getCertainPlaceByName(ID2.split("&")[2])->getTokens();
            p1Capacity=OriginComponent_List[i]->getCertainPlaceByName(ID2.split("&")[2])->getCapacity();
        }

    }
    p1->setTokens(p1Token);
    p2->setTokens(p2Token);
    p1->setCapacity(p1Capacity);
    p2->setCapacity(p2Capacity);
    p1->setcontain_portNum(1);
    p2->setcontain_portNum(1);
    p1->setCompoundPort(false);
    p2->setCompoundPort(false);
    QList<Arc*>l1;
    QList<Arc*>l2;
    Place*compoundPort=this->getCertainPlace(CompoundPortID);

    for(int i=0;i<compoundPort->getinput().size();i++)
    {
        QString arcComID=compoundPort->getinput()[i]->getId().split("&")[0]+compoundPort->getinput()[i]->getId().split("&")[1];
        if(arcComID==comID1)
        {
            l1.push_back(compoundPort->getoutput()[i]);
        }
    }



    for(int i=0;i<compoundPort->getoutput().size();i++)
    {
        QString arcComID=compoundPort->getoutput()[i]->getId().split("&")[0]+compoundPort->getoutput()[i]->getId().split("&")[1];
        if(arcComID==comID1)
        {
            l2.push_back(compoundPort->getoutput()[i]);
        }
    }

    if(compoundPort->getoutput().size()==0)
    {
        p1->setOutputPort(true);
        p2->setOutputPort(true);

        p1->setInputPort(false);
        p2->setInputPort(false);

        for(int i=0;i<l1.size();i++)
        {
            l1[i]->setTargetId(ID1);
            l1[i]->setTargetItem(p1);
        }

        for(int i=0;i<l2.size();i++)
        {
            l2[i]->setTargetId(ID2);
            l2[i]->setTargetItem(p2);
        }

    }

    else if(compoundPort->getinput().size()==0)
    {
        p1->setInputPort(true);
        p2->setInputPort(true);

        p1->setOutputPort(false);
        p2->setOutputPort(false);

        for(int i=0;i<l1.size();i++)
        {
            l1[i]->setsourceId(ID1);
            l1[i]->setSourceItem(p1);
        }

        for(int i=0;i<l2.size();i++)
        {
            l2[i]->setsourceId(ID2);
            l2[i]->setSourceItem(p2);
        }
    }

    else
    {
        if((compoundPort->getinput()[0]->getId().split("&")[0]+compoundPort->getinput()[0]->getId().split("&")[1])==comID1)
        {
            p1->setOutputPort(true);
            p2->setInputPort(true);
            p1->setInputPort(false);
            p2->setOutputPort(false);
            for(int i=0;i<l1.size();i++)
            {
                l1[i]->setTargetId(ID1);
                l1[i]->setTargetItem(p1);

            }
            for(int i=0;i<l2.size();i++)
            {
                l1[i]->setsourceId(ID1);
                l1[i]->setSourceItem(p1);
            }
        }
        else
        {
            p1->setOutputPort(false);
            p2->setInputPort(false);
            p1->setInputPort(true);
            p2->setOutputPort(true);
            for(int i=0;i<l1.size();i++)
            {
                l1[i]->setsourceId(ID1);
                l1[i]->setSourceItem(p1);

            }
            for(int i=0;i<l2.size();i++)
            {
                l1[i]->setTargetId(ID1);
                l1[i]->setTargetItem(p1);
            }
        }
    }

    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==comID1)
        {
            com_list[i]->mynet->PlaceList.push_back(p1);
        }
        else if(com_list[i]->getID()==comID2)
        {
            com_list[i]->mynet->PlaceList.push_back(p2);
        }
    }

    //如何将新创建的place添加到scene中
    this->Scene->addItem(p1);
    this->Scene->addItem(p2);
    this->Scene->removeItem(compoundPort);

}

void ComponentList::deleteComponent(QString ComponentID)
{
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==ComponentID)
        {
            Component*com=new Component;
            com=com_list[i];
            PTNscene*s=new PTNscene();
            for(int i=0;i<com->mynet->PlaceList.size();i++)
            {

                s->addItem(com->mynet->PlaceList[i]);
            }
            for(int i=0;i<com->mynet->TransitionList.size();i++)
            {
                s->addItem(com->mynet->TransitionList[i]);
            }

            for(int i=0;i<com->mynet->ArcList.size();i++)
            {
                s->addItem(com->mynet->ArcList[i]);
            }

            //恢复成默认值
            Component*c=this->OriginComponent(ComponentID.split("&")[0]);
            for(int y=0;i<com_list[i]->mynet->PlaceList.size();y++)
            {
                for(int z=0;z<c->mynet->PlaceList.size();z++)
                {
                    if(c->mynet->PlaceList[z]->getName()==com_list[i]->mynet->PlaceList[y]->getName())
                    {
                        com_list[i]->mynet->PlaceList[y]->setTokens(c->mynet->PlaceList[z]->getTokens());
                        com_list[i]->mynet->PlaceList[y]->setCapacity(c->mynet->PlaceList[z]->getCapacity());
                    }
                }
            }

            garbage.insert(ComponentID,s);
            com_list.remove(i);
        }
    }

}

void ComponentList::recoverComponent(QString ComponentID)
{
    QMapIterator<QString,PTNscene*>it(this->garbage);
    Component*com=new Component();
    PTNscene*s=new PTNscene;
    while (it.hasNext()) {
        it.next();
        if(it.key()==ComponentID)
        {
            s=it.value();
        }
    }

    foreach(QGraphicsItem*item,s->items())
    {
        if(item->type()==Place::Type)
        {
            Place * place = qgraphicsitem_cast<Place*>(item);
            com->mynet->PlaceList.push_back(place);

        }
        else if(item->type()==Transition::Type)
        {
            Transition * place = qgraphicsitem_cast<Transition*>(item);
            com->mynet->TransitionList.push_back(place);

        }
        else if(item->type()==Arc::Type)
        {
            Arc * place = qgraphicsitem_cast<Arc*>(item);
            com->mynet->ArcList.push_back(place);

        }

    }
    com_list.push_back(com);
}
