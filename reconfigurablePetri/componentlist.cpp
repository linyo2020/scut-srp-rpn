#include "componentlist.h"

ComponentList::ComponentList()
{
    Scene=new PTNscene();
    comController=new componentController();

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
                if(ID.size()==1)
                {
                    list.push_back(ID[0].split("&")[2]);
                }
                //对于复合端口单独处理
                else
                {
                    for(int i=0;i<ID.size();i++)
                    {
                        QString ComID=ID[i].split("&")[0]+ID[i].split("&")[1];
                        if(ComID==ComponentID)
                        {
                            list.push_back(ID[i].split("&")[2]);
                        }

                    }
                }

            }

        }
    }
    return list;
}

//todo
//新增对于复合transition的处理，需要与place一样对ID进行判断，返回ComponentID这一侧的元素name
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
//todo（1.1号之后)
//增加transition与transition直接的连接、transition与place的连接
//已于规则库达成共识，规定前一个传参端口连接到后一个传参端口
//transition与place的连接直接加弧
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

void ComponentList::addNewComponent(Component*newCom)
{
    newCom->setID(setnewComponentIDinSimulation(newCom));
    com_list.push_back(newCom);

    foreach(Place* pl,newCom->getPlaceList())
    {
        Scene->addItem(pl);
    }
    foreach(Transition *tran,newCom->getTransitionList())
    {
        Scene->addItem(tran);
    }
    foreach(Arc* ar,newCom->getTArcList())
    {
        Scene->addItem(ar);
    }

}

QString ComponentList::addNewComponent(QString Filename)
{
    Component*com=this->OriginComponent(Filename);
    com->setID(setnewComponentIDinSimulation(com));
    com_list.push_back(com);

    foreach(Place* pl,com->getPlaceList())
    {
        Scene->addItem(pl);
    }
    foreach(Transition *tran,com->getTransitionList())
    {
        Scene->addItem(tran);
    }
    foreach(Arc* ar,com->getTArcList())
    {
        Scene->addItem(ar);
    }

    return com->getID();
}
Component *ComponentList::OriginComponent(QString Filename)
{

    PTNscene* sce=new PTNscene();
    sce->from_Xml(comController->getXMLpages(Filename));
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
    QStringList id=CompoundPortID.split("+");
    QString ID1=id[0];
    QString comID1=ID1.split("&")[0]+ID1.split("&")[1];
    QString ID2=id[1];
    QString comID2=ID2.split("&")[0]+ID2.split("&")[1];
    Place *p1=new Place();
    Place*p2=new Place();
    p1->setPlaceID(ID1);
    p2->setPlaceID(ID2);
    QString FName1=ID1.split("&")[0];
    QString FName2=ID2.split("&")[0];

    Component*com1=this->OriginComponent(FName1);
    //暂时
    p1->setTokens(com1->getCertainPlaceByName(ID1.split("&")[2])->getTokens());
    p1->setCapacity(com1->getCertainPlaceByName(ID1.split("&")[2])->getCapacity());
    Component*com2=this->OriginComponent(FName2);
    p2->setTokens(com2->getCertainPlaceByName(ID2.split("&")[2])->getTokens());
    p2->setCapacity(com2->getCertainPlaceByName(ID2.split("&")[2])->getCapacity());


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

//todo
//对于新增的transition部分要进行处理。
void ComponentList::deleteComponent(QString ComponentID)
{
    QString Filename=ComponentID.split("&")[0];
    for(int z=0;z<com_list.size();z++)
    {
        if(com_list[z]->getID()==ComponentID)
        {
            Component*com=new Component;
            com=com_list[z];
            PTNscene*s=new PTNscene();

            //断开所有复合端口
            for(int y=0;y<com->mynet->PlaceList.size();y++)
            {
                if(com->mynet->PlaceList[y]->isACompoundPort())
                {
                    this->seperateCompoundPort(com->mynet->PlaceList[y]->getId());
                }
            }

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
            garbage.insert(ComponentID,s);
            com_list.remove(z);
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
            Scene->addItem(place);

        }
        else if(item->type()==Transition::Type)
        {
            Transition * place = qgraphicsitem_cast<Transition*>(item);
            com->mynet->TransitionList.push_back(place);
            Scene->addItem(place);

        }
        else if(item->type()==Arc::Type)
        {
            Arc * place = qgraphicsitem_cast<Arc*>(item);
            com->mynet->ArcList.push_back(place);
            Scene->addItem(place);

        }

    }
    com_list.push_back(com);
}
