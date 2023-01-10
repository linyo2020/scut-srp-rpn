#include "component.h"
#include"QDebug"
Component::Component()
{
    this->mynet=new PTNet();

}

//bug
Component::Component(const PTNET_ATTR& PTnet,PTNscene*scene)
{
    if(PTnet.id[0].isLetter())
    {
        this->Component_type=PTnet.id[0];
        this->Component_id=Component_type+PTnet.id;

        if(scene!=NULL)
        {
            foreach(QGraphicsItem * item, scene->items())
            {
                if(item->type() == Place::Type)
                {
                    mynet->AddPlace(qgraphicsitem_cast<Place*>(item));
                    continue;
                }
                if(item->type() == Transition::Type)
                {

                    mynet->AddTransition(qgraphicsitem_cast<Transition*>(item));
                    continue;
                }
                if(item->type() == Arc::Type)
                {
                    mynet->AddArc(qgraphicsitem_cast<Arc*>(item));
                    continue;
                }
            }
            this->net_att_isEdited=true;
        }


    }
    else
    {
        qDebug()<<"the first letter of id is not letter, but still use construction fuction of Component";
    }

}

Component::Component(QString type, QString label)
{
    this->Component_type=type;
    this->label=label;
     QDateTime time=QDateTime::currentDateTime ();
     this->Component_id=Component_type+time.toString("yy:MM:dd:hh:mm:ss");
}
//临时采取的方法，有一定问题
Component::Component(QString PTnet_ID, PTNscene *scene)
{
    if(PTnet_ID[0].isLetter())
    {
        this->Component_type=PTnet_ID[0];
        this->Component_id=Component_type+PTnet_ID;

        foreach(QGraphicsItem * item, scene->items())
        {
            if(item->type() == Place::Type)
            {
                mynet->AddPlace(qgraphicsitem_cast<Place*>(item));
                continue;
            }
            if(item->type() == Transition::Type)
            {

                mynet->AddTransition(qgraphicsitem_cast<Transition*>(item));
                continue;
            }
            if(item->type() == Arc::Type)
            {
                mynet->AddArc(qgraphicsitem_cast<Arc*>(item));
                continue;
            }
        }
        this->net_att_isEdited=true;
    }
    else
    {
        qDebug()<<"the first letter of id is not letter, but still use construction fuction of Component";
    }
}

QList<Place *> Component::getPlaceList()
{
    return this->mynet->PlaceList;
}

QList<Transition *> Component::getTransitionList()
{
    return this->mynet->TransitionList;
}
QList<Arc*>Component::getTArcList()
{
    return this->mynet->ArcList;
}
QString Component::getComponentFileName()
{
    return (this->getID().split("&")[0]);
}

Place *Component::getCertainPlaceByName(QString p0)
{
    for(int i=0;i<mynet->PlaceList.size();i++)
    {
        if(mynet->PlaceList[i]->getId().split("&")[2]==p0)
        {
            return mynet->PlaceList[i];
        }
    }
}

QList<Place *> Component::getNormalPort()
{
    QList<Place *> p;
    Place*pp=new Place();
    p.push_back(pp);
    for(int i=0;i<mynet->PlaceList.size();i++)
    {
        if(mynet->PlaceList[i]->isNormalPort())
        {
            p.push_back(mynet->PlaceList[i]);
        }
    }
    return p;
}

QList<Place *> Component::getCompoundPort()
{
    QList<Place*>l;
    for(int i=0;i<mynet->PlaceList.size();i++)
    {
        if(mynet->PlaceList[i]->isACompoundPort()==true)
        {
            l.push_back(mynet->PlaceList[i]);
        }
    }
    return l;
}

QString Component::getLabel() const
{
    return label;
}

//如果组件中已经存在复合端口，此时调用此函数会导致报错
void Component::setID(QString id)
{
    this->Component_id=id;
    for(int i=0;i<mynet->PlaceList.size();i++)
    {
        Place*p=mynet->PlaceList[i];
        QStringList ids=p->getId().split("+");
        Q_ASSERT_X(ids.size()==1,"id error","use Component::setID while there has been a compound port in this component");
        QString name=p->getId().split("&")[2];
        p->setPlaceID(id+"&"+name);
    }
    for(int i=0;i<mynet->TransitionList.size();i++)
    {
        Transition*p=mynet->TransitionList[i];
        QStringList ids=p->getId().split("+");
        Q_ASSERT_X(ids.size()==1,"id error","use Component::setID while there has been a compound port in this component");
        QString name=p->getId().split("&")[2];
        p->setID(id+"&"+name);
    }

    for(int i=0;i<mynet->ArcList.size();i++)
    {
        Arc*p=mynet->ArcList[i];
        QString name=p->getId().split("&")[2];
        QString sName=p->getSourceId().split("&")[2];
        QString TName=p->getTargetId().split("&")[2];
        p->setTargetId(id+"&"+TName);
        p->setsourceId(id+"&"+sName);
        p->setID(id+"&"+name);
    }
}

QString Component::getID()
{
    return this->Component_id;
}

void Component::setLabel(const QString &value)
{
    label = value;
}

QString Component::getFileName()
{
    return this->getID().split("&")[0];
}



Place *Component::getCertainPlace(QString PlaceID)
{
    for(int i=0;i<mynet->PlaceList.size();i++)
    {
        if(mynet->PlaceList[i]->getId()==PlaceID)
        {
            return mynet->PlaceList[i];
        }
    }
}


QString Component::getComponent_type() const
{
    return Component_type;
}

void Component::setComponent_type(QString value)
{
    Component_type = value;
}


void Component::setStep(double step)
{
    m_step = step;
}

double Component::getStep()
{
    return m_step;
}

bool Component::makeFunction()
{
    QList<ARC_ATTR>arcs;
    QList<TRANSITION_ATTR>transitionNodes;
    QList<PLACE_ATTR>placeNodes;
    /***
     * TODO:将PTNet *mynet转换成结构体数据
     */


    /*
    *输出每条边的来源和去向
    for(int i=0;i<arcs.size();i++)
    {
        qDebug()<<"ARC "<<arcs[i].id<<" FROM "<<arcs[i].source<<" TO "<<arcs[i].target<<endl;
    }*/

    //用l_mtemp记录弧和其来源(包含权重信息，完整为(来源库所名字+"^"+权重))
    map<QString,QString>l_mtemp;
    for(int i=0;i<arcs.size();i++)
    {
        //qDebug()<<arcs.size();
        QString l_stemp;
        for(int j=0;j<placeNodes.size();j++)
        {
            if(placeNodes[j].id==arcs[i].source)
            {
                l_stemp.append(placeNodes[j].name);
                //qDebug()<<placeNodes[j].name;
                break;
            }
        }
        //记录ode中前置库所对应的指数
        l_stemp.append("^("+QString::number(arcs[i].weight)+")");
        //保存反应物和系数
        l_mtemp[arcs[i].id]=l_stemp;
    }
    QVector<QString> samename;
    int recordpos;
    //对于每个PLACE
    for(int i=0;i<placeNodes.size();i++)
    {
        int havesame=0;
        //qDebug()<<"the size of samename is "<<samename.size();
        //检测库所名字是否重复
        for(int j=0;j<samename.size();j++)
        {
            if(samename[j]==placeNodes[i].name)
            {
                havesame=1;
                break;
            }
        }
        m_mInputVaraible2Value[placeNodes[i].name.toStdString()]=placeNodes[i].initmark;
        FUNCTIONDEF l_FunDef;
        if(havesame==0)
        {
            l_FunDef.m_sDifferentialName=placeNodes[i].name.toStdString();
            l_FunDef.m_sFunctionExp="";
        }
        else
        {
            for(unsigned j=0;j<m_vFunDef.size();j++)
            {
                if(m_vFunDef[j].m_sDifferentialName==placeNodes[i].name.toStdString())
                {
                    l_FunDef=m_vFunDef[j];
                    recordpos=int(j);
                    break;
                }
            }
        }
        //查找与PLACE相连的N条ARC
        for(int j=0;j<arcs.size();j++)
        {
            //PLACE为该ARC起点
            if(arcs[j].source==placeNodes[i].id)
            {
                //qDebug()<<placeNodes[i].name<<"is the source of"<<arcs[j].id;
                for(int k=0;k<transitionNodes.size();k++)
                {
                    //找到该ARC的终点TRANSITION
                    if(transitionNodes[k].id==arcs[j].target)
                    {
                        //向函数表达式中增加负项因子
                        l_FunDef.m_sFunctionExp.append("-1*(");
                        l_FunDef.m_sFunctionExp.append(QString::number(arcs[j].weight).toStdString());
                        l_FunDef.m_sFunctionExp.append(")*(");
                        //如果变迁（反应）速率符合质量作用定律
                        if(transitionNodes[k].self_function.contains("MassAction"))
                            {
                                QString temp=(transitionNodes[k].self_function.split("MassAction"))[1];
                                for(int m=0;m<transitionNodes.size();m++)
                                {
                                    //？？？同名变迁同步
                                    if(transitionNodes[m].name==transitionNodes[k].name&&m!=k)
                                    {
                                        //通过寻找前置弧来寻找该反应（变迁）对应的反应物（消耗的库所）
                                        for(int p=0;p<arcs.size();p++)
                                        {
                                            //找到反应物后继续补充反应速率因子
                                            if(arcs[p].target==transitionNodes[m].id)
                                            {
                                                temp.append("*(");
                                                temp.append(l_mtemp[arcs[p].id]);
                                                temp.append(")");
                                            }
                                        }
                                    }
                                }
                                //通过寻找前置弧来寻找该反应（变迁）对应的反应物（消耗的库所）
                                for(int m=0;m<arcs.size();m++)
                                {
                                    //找到反应物后继续补充反应速率因子
                                    if(arcs[m].target==transitionNodes[k].id)
                                    {
                                        temp.append("*(");
                                        temp.append(l_mtemp[arcs[m].id]);
                                        temp.append(")");
                                    }
                                }
                                l_FunDef.m_sFunctionExp.append(temp.toStdString());
                            }
                        //否则反应速率为参数*反应物名字（其余为非法结构,之后在解析表达式时需要对此进行检测）
                        else
                            {
                                l_FunDef.m_sFunctionExp.append(transitionNodes[k].self_function.toStdString());
                            }
                        l_FunDef.m_sFunctionExp.append(")");
                        break;
                    }
                }
            }
            //PLACE为该ARC终点
            else if(arcs[j].target==placeNodes[i].id)
            {
                //qDebug()<<placeNodes[i].name<<"is the target of"<<arcs[j].id;
                for(int k=0;k<transitionNodes.size();k++)
                {
                    //找到该ARC的起点TRANSITION
                    if(transitionNodes[k].id==arcs[j].source)
                    {
                        {
                            //如果该库所只作为生成物
                            if(l_FunDef.m_sFunctionExp=="")
                                l_FunDef.m_sFunctionExp.append("1*(");
                            //如果该库所为反应物和生成物
                            else
                                l_FunDef.m_sFunctionExp.append("+1*(");
                            l_FunDef.m_sFunctionExp.append(QString::number(arcs[j].weight).toStdString());
                            l_FunDef.m_sFunctionExp.append(")*(");
                            if(transitionNodes[k].self_function.contains("MassAction"))
                            {
                                QString temp=(transitionNodes[k].self_function.split("MassAction"))[1];
                                for(int m=0;m<transitionNodes.size();m++)
                                {
                                    if(transitionNodes[m].name==transitionNodes[k].name&&m!=k)
                                    {
                                        for(int p=0;p<arcs.size();p++)
                                        {
                                            if(arcs[p].target==transitionNodes[m].id)
                                            {
                                                temp.append("*(");
                                                temp.append(l_mtemp[arcs[p].id]);
                                                temp.append(")");
                                            }
                                        }
                                    }
                                }
                                for(int m=0;m<arcs.size();m++)
                                {
                                    if(arcs[m].target==transitionNodes[k].id)
                                    {
                                        temp.append("*(");
                                        temp.append(l_mtemp[arcs[m].id]);
                                        temp.append(")");
                                    }
                                }
                                l_FunDef.m_sFunctionExp.append(temp.toStdString());
                            }
                            else
                            {
                                l_FunDef.m_sFunctionExp.append(transitionNodes[k].self_function.toStdString());
                            }
                            l_FunDef.m_sFunctionExp.append(")");
                        }
                    }
                }
            }
        }
        if(l_FunDef.m_sFunctionExp=="")
            l_FunDef.m_sFunctionExp="0";
        if(havesame==0)
        {
            m_vFunDef.push_back(l_FunDef);
            samename.push_back(placeNodes[i].name);
        }
        else
        {
            m_vFunDef[recordpos]=l_FunDef;
        }
    }
}
























