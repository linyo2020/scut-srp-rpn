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
    QString comID=(PlaceID.split("+")[0].split("&")[0]+"&"+PlaceID.split("+")[0].split("&")[1]);
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

//针对复合端口的name进行处理
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
                        QString ComID=ID[i].split("&")[0]+"&"+ID[i].split("&")[1];
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
                QStringList id=p->getId().split("+");
                if((id[0].split("&")[0]+"&"+id[0].split("&")[1])==ComponentID)
                {
                    list.push_back(id[0].split("&")[2]);
                }
                else
                {
                    list.push_back(id[1].split("&")[2]);
                }
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
    //端口均为place
    if(portID1.split("&")[2][0]=="p"&&portID2.split("&")[2][0]=="p")
    {
        QString placeID=portID1+"+"+portID2;
        Place*p1=getCertainPlace(portID1);
        Place*p2=getCertainPlace(portID2);
        Place *P=new Place();
        P->setPlaceID(placeID);
        //！！设置name
        P->setName(portID1.split("&")[2]+"+"+portID2.split("&")[2]);
        P->setCapacity(getCertainPlace(portID1)->getCapacity()+getCertainPlace(portID2)->getCapacity());
        P->setTokens(getCertainPlace(portID1)->getTokens()+getCertainPlace(portID2)->getTokens());
        P->setInputPort(true);
        P->setOutputPort(true);
        P->setCompoundPort(true);
        P->setcontain_portNum(P->getcontain_portNum()+1);
        QString comID1=portID1.split("&")[0]+"&"+portID1.split("&")[1];
        QString comID2=portID2.split("&")[0]+"&"+portID2.split("&")[1];
        foreach(Arc* a,p1->getinput())
        {
            a->setTargetId(placeID);
            a->setTargetItem(P);
        }
        foreach(Arc* a,p1->getoutput())
        {
            a->setsourceId(placeID);
            a->setSourceItem(P);
        }
        foreach(Arc* a,p2->getinput())
        {
            a->setTargetId(placeID);
            a->setTargetItem(P);
        }
        foreach(Arc* a,p2->getoutput())
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

        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID1)
            {
                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
                {
                    if(com_list[i]->getPlaceList()[y]->getId()==portID1)
                    {
                        com_list[i]->mynet->PlaceList.removeAt(y);
                    }
                }
            }
            else if(com_list[i]->getID()==comID2)
            {
                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
                {
                    if(com_list[i]->getPlaceList()[y]->getId()==portID2)
                    {
                        com_list[i]->mynet->PlaceList.removeAt(y);
                    }
                }
            }
        }



        this->Scene->addItem(P);

        this->Scene->removeItem(p1);
        this->Scene->removeItem(p2);
    }
    //均为transition
    else if(portID1.split("&")[2][0]=="t"&&portID2.split("&")[2][0]=="t")
    {
        Transition*t1=getcertainTransition(portID1);
        Transition*t2=getcertainTransition(portID2);
        Transition*newTrans=new Transition();
        QString transID=t1->getId()+"+"+t2->getId();
        newTrans->setID(transID);
        //todo
        //newTrans->setName();

        newTrans->setCompoundPort(true);
        QString comID1=portID1.split("&")[0]+"&"+portID1.split("&")[1];
        QString comID2=portID2.split("&")[0]+"&"+portID2.split("&")[1];
        foreach(Arc* a,t1->getinput())
        {
            a->setTargetId(transID);
            a->setTargetItem(newTrans);
        }
        foreach(Arc* a,t1->getoutput())
        {
            a->setsourceId(transID);
            a->setSourceItem(newTrans);
        }
        foreach(Arc* a,t2->getinput())
        {
            a->setTargetId(transID);
            a->setTargetItem(newTrans);
        }
        foreach(Arc* a,t2->getoutput())
        {
            a->setsourceId(transID);
            a->setSourceItem(newTrans);
        }

        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID1||com_list[i]->getID()==comID2)
            {
                com_list[i]->mynet->TransitionList.push_back(newTrans);
            }
        }

        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID1)
            {
                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
                {
                    if(com_list[i]->getTransitionList()[y]->getId()==portID1)
                    {
                        com_list[i]->mynet->TransitionList.removeAt(y);
                    }
                }
            }
            else if(com_list[i]->getID()==comID2)
            {
                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
                {
                    if(com_list[i]->getTransitionList()[y]->getId()==portID2)
                    {
                        com_list[i]->mynet->TransitionList.removeAt(y);
                    }
                }
            }
        }

        this->Scene->addItem(newTrans);

        this->Scene->removeItem(t1);
        this->Scene->removeItem(t2);

    }

    else if(portID1.split("&")[2][0]=="p"&&portID2.split("&")[2][0]=="t")
    {
        Place*p=getCertainPlace(portID1);
        Transition*t=getcertainTransition(portID2);
        Arc*a=new Arc();
        a->setID(portID1.split("&")[0]+"&"+portID1.split("&")[1]+"+"+portID2.split("&")[0]+"&"+portID2.split("&")[1]+"+"+"N");
        a->setTargetId(t->getId());
        a->setTargetItem(t);
        //t->merge_input.push_back(a);
        a->setsourceId(p->getId());
        a->setSourceItem(p);
        //p->merge_output.push_back(a);
        this->Scene->addItem(a);
    }

    else if(portID1.split("&")[2][0]=="t"&&portID2.split("&")[2][0]=="p")
    {
        Place*p=getCertainPlace(portID2);
        Transition*t=getcertainTransition(portID1);
        Arc*a=new Arc();
        a->setID(portID1.split("&")[0]+"&"+portID1.split("&")[1]+"+"+portID2.split("&")[0]+"&"+portID2.split("&")[1]+"+" + "N");
        a->setTargetId(p->getId());
        a->setTargetItem(p);

        //p->merge_input.push_back(a);
        a->setsourceId(t->getId());
        a->setSourceItem(t);
        //t->merge_output.push_back(a);
        this->Scene->addItem(a);
    }
}

//useless
void ComponentList::addNewComponent(Component*newCom)
{
    this->setnewComponentIDinSimulation(newCom);
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

Transition *ComponentList::getcertainTransition(QString tranID)
{
    QString comID=(tranID.split("+")[0].split("&")[0]+"&"+tranID.split("+")[0].split("&")[1]);
    for(int i=0;i<com_list.size();i++)
    {
        if(com_list[i]->getID()==comID)
        {
            for(int i=0;i<com_list[i]->getTransitionList().size();i++)
            {
                if(com_list[i]->getTransitionList()[i]->getId()==tranID)
                {
                    return com_list[i]->getTransitionList()[i];
                }
            }
        }
    }
}

//!!!原始组件内部不要有复合端口
QString ComponentList::addNewComponent(QString Filename)
{
    Component*com=this->OriginComponent(Filename);
    setnewComponentIDinSimulation(com);
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
    //下面认为place作为端口时，input与output应该有一个为空
    if(id[0].split("&")[2][0]=="p"&&id[1].split("&")[2][0]=="p")
    {
        QString ID1=id[0];
        QString comID1=ID1.split("&")[0]+"&"+ID1.split("&")[1];
        QString ID2=id[1];
        QString comID2=ID2.split("&")[0]+"&"+ID2.split("&")[1];
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
            QString arcComID=compoundPort->getinput()[i]->getId().split("&")[0]+"&"+compoundPort->getinput()[i]->getId().split("&")[1];
            if(arcComID==comID1)
            {
                l1.push_back(compoundPort->getoutput()[i]);

            }
        }



        for(int i=0;i<compoundPort->getoutput().size();i++)
        {
            QString arcComID=compoundPort->getoutput()[i]->getId().split("&")[0]+"&"+compoundPort->getoutput()[i]->getId().split("&")[1];
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
            if((compoundPort->getinput()[0]->getId().split("&")[0]+"&"+compoundPort->getinput()[0]->getId().split("&")[1])==comID1)
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

        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID1)
            {
                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
                {
                    if(com_list[i]->getPlaceList()[y]->getId()==CompoundPortID)
                    {
                        com_list[i]->mynet->PlaceList.removeAt(y);
                    }
                }
            }
            else if(com_list[i]->getID()==comID2)
            {
                for(int y=0;y<com_list[i]->getPlaceList().size();i++)
                {
                    if(com_list[i]->getPlaceList()[y]->getId()==CompoundPortID)
                    {
                        com_list[i]->mynet->PlaceList.removeAt(y);
                    }
                }
            }
        }


        //如何将新创建的place添加到scene中
        this->Scene->addItem(p1);
        this->Scene->addItem(p2);
        this->Scene->removeItem(compoundPort);

    }

    else if(id[0].split("&")[2][0]=="t"&&id[1].split("&")[2][0]=="t")
    {
        Transition*t1=new Transition();
        Transition*t2=new Transition();
        t1->setCompoundPort(false);
        t2->setCompoundPort(false);
        QString ID1=id[0];
        QString comID1=ID1.split("&")[0]+"&"+ID1.split("&")[1];
        QString ID2=id[1];
        QString comID2=ID2.split("&")[0]+"&"+ID2.split("&")[1];
        t1->setID(ID1);
        t2->setID(ID2);
        t1->setName(ID1.split("&")[2]);
        t2->setName(ID2.split("&")[2]);
        QList<Arc*>t1_in;
        QList<Arc*>t1_out;
        QList<Arc*>t2_in;
        QList<Arc*>t2_out;
        Transition*t=getcertainTransition(CompoundPortID);
        for(int i=0;i<t->getinput().size();i++)
        {
            QString cID=t->getinput()[i]->getId().split("&")[0]+"&"+t->getinput()[i]->getId().split("&")[1];
            if(cID==comID1)
            {
                t1_in.push_back(t->getinput()[i]);
            }
            else if(cID==comID2)
            {
                t2_in.push_back(t->getinput()[i]);
            }
        }
        for(int i=0;i<t->getoutput().size();i++)
        {
            QString cID=t->getoutput()[i]->getId().split("&")[0]+"&"+t->getoutput()[i]->getId().split("&")[1];
            if(cID==comID1)
            {
                t1_out.push_back(t->getoutput()[i]);
            }
            else if(cID==comID2)
            {
                t2_out.push_back(t->getoutput()[i]);
            }
        }

        for(int i=0;i<t1_in.size();i++)
        {
            t1->pushInput(t1_in[i]);
        }

        for(int i=0;i<t1_out.size();i++)
        {
            t1->pushOutput(t1_out[i]);
        }
        for(int i=0;i<t2_in.size();i++)
        {
            t2->pushInput(t2_in[i]);
        }

        for(int i=0;i<t2_out.size();i++)
        {
            t2->pushOutput(t2_out[i]);
        }


        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID1)
            {
                com_list[i]->mynet->TransitionList.push_back(t1);
            }
            else if(com_list[i]->getID()==comID2)
            {
                com_list[i]->mynet->TransitionList.push_back(t2);
            }
        }

        for(int i=0;i<com_list.size();i++)
        {
            if(com_list[i]->getID()==comID1)
            {
                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
                {
                    if(com_list[i]->getTransitionList()[y]->getId()==CompoundPortID)
                    {
                        com_list[i]->mynet->TransitionList.removeAt(y);
                    }
                }
            }
            else if(com_list[i]->getID()==comID2)
            {
                for(int y=0;y<com_list[i]->getTransitionList().size();i++)
                {
                    if(com_list[i]->getTransitionList()[y]->getId()==CompoundPortID)
                    {
                        com_list[i]->mynet->TransitionList.removeAt(y);
                    }
                }
            }
        }

        this->Scene->addItem(t1);
        this->Scene->addItem(t2);
        this->Scene->removeItem(t);

    }


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

            for(int m=0;m<com->mynet->TransitionList.size();m++)
            {
                if(com->mynet->TransitionList[m]->IsCompoundPort())
                {
                    this->seperateCompoundPort(com->mynet->TransitionList[m]->getId());
                }
            }

            //删除该组件连向外部的新创建的弧
            foreach(QGraphicsItem * item, this->Scene->items())
            {
                if(item->type() == Arc::Type)
                {
                    Arc*a= qgraphicsitem_cast<Arc*>(item);
                    QStringList id=a->getId().split("+");
                    if(id.size()==3)
                    {
                        for(int b=0;b<2;b++)
                        {
                            QString comID=id[b].split("&")[0]+"&"+id[b].split("&")[1];
                            if(comID==ComponentID)
                            {
                                this->Scene->removeItem(a);
                            }
                        }
                    }
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
