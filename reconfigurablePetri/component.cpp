#include "component.h"
#include"QDebug"
#include<QThread>
#include"defs.h"
Component::Component()
{
    m_step=default_step;
    this->mynet=new PTNet();

}

//bug
Component::Component(const PTNET_ATTR& PTnet,PTNscene*scene)
{
    m_step=default_step;
    if(PTnet.id[0].isLetter())
    {
        Component_type=PTnet.id[0];
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
                if(item->type() == Arcus::Type)
                {
                    mynet->AddArc(qgraphicsitem_cast<Arcus*>(item));
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
    m_step=default_step;
    this->Component_type=type;
    this->label=label;
     QDateTime time=QDateTime::currentDateTime ();
     this->Component_id=Component_type+time.toString("yy:MM:dd:hh:mm:ss");
}
//临时采取的方法，有一定问题
Component::Component(QString PTnet_ID, PTNscene *scene)
{
    m_step=default_step;
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
            if(item->type() == Arcus::Type)
            {
                mynet->AddArc(qgraphicsitem_cast<Arcus*>(item));
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
QList<Arcus*>Component::getTArcList()
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

void Component::setID(QString comID, int i=0)
{
    if(i==0)
    {
        this->Component_id=comID;
        for(int i=0;i<this->placeList.size();i++)
        {
            this->placeList[i].id=comID+"&"+this->placeList[i].id;
        }
        for(int i=0;i<this->transitionList.size();i++)
        {
            this->transitionList[i].id=comID+"&"+this->transitionList[i].id;
        }
        for(int i=0;i<this->arcList.size();i++)
        {
            this->arcList[i].id=comID+"&"+this->arcList[i].id;
        }
    }
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
        Arcus*p=mynet->ArcList[i];
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

double Component::getCertainPlaceToken(QString PlaceID)
{
//    for(int i=0;i<mynet->PlaceList.size();i++)
//    {
//        if(mynet->PlaceList[i]->getId()==PlaceID)
//        {
//            return mynet->PlaceList[i]->getTokens();
//        }
//    }
//    return -1.0;
    for(int i=0;i<placeList.size();i++)
    {
        if(placeList[i].id==PlaceID)
            return placeList[i].initmark;
    }
    return -1.0;
}

QList<PLACE_ATTR> Component::getPlace_ATTRList()
{
    return this->placeList;
}

QList<TRANSITION_ATTR> Component::getTransition_ATTRList()
{
    return this->transitionList;
}

QList<ARC_ATTR> Component::getArc_ATTRList()
{
    return this->arcList;
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

void Component::makeFunction()
{
    /*
    *输出每条边的来源和去向
    for(int i=0;i<arcs.size();i++)
    {
        qDebug()<<"ARC "<<arcs[i].id<<" FROM "<<arcs[i].source<<" TO "<<arcs[i].target<<endl;
    }*/

    //清空原有的初始数据和方程信息
    m_mInputVaraible2Value.clear();
    m_vFunDef.clear();

    //用l_mtemp记录弧和其来源(包含权重信息，完整为(来源库所名字+"^"+权重))
    map<QString,QString>l_mtemp;
    for(int i=0;i<arcList.size();i++)
    {
        //qDebug()<<arcs.size();
        QString l_stemp;
        for(int j=0;j<placeList.size();j++)
        {
            if(placeList[j].id==arcList[i].source)
            {
                l_stemp.append(placeList[j].name);
                //qDebug()<<placeNodes[j].name;
                break;
            }
        }
        //记录ode中前置库所对应的指数
        l_stemp.append("^("+QString::number(arcList[i].weight)+")");
        //保存反应物和系数
        l_mtemp[arcList[i].id]=l_stemp;
    }
    QVector<QString> samename;
    int recordpos;
    //对于每个PLACE
    for(int i=0;i<placeList.size();i++)
    {
        int havesame=0;
        //qDebug()<<"the size of samename is "<<samename.size();
        //检测库所名字是否重复
        for(int j=0;j<samename.size();j++)
        {
            if(samename[j]==placeList[i].name)
            {
                havesame=1;
                break;
            }
        }
        m_mInputVaraible2Value[placeList[i].name.toStdString()]=placeList[i].initmark;
        FUNCTIONDEF l_FunDef;
        if(havesame==0)
        {
            l_FunDef.m_sDifferentialName=placeList[i].name.toStdString();
            l_FunDef.m_sFunctionExp="";
        }
        else
        {
            for(unsigned j=0;j<m_vFunDef.size();j++)
            {
                if(m_vFunDef[j].m_sDifferentialName==placeList[i].name.toStdString())
                {
                    l_FunDef=m_vFunDef[j];
                    recordpos=int(j);
                    break;
                }
            }
        }
        //查找与PLACE相连的N条ARC
        for(int j=0;j<arcList.size();j++)
        {
            //PLACE为该ARC起点
            if(arcList[j].source==placeList[i].id)
            {
                //qDebug()<<placeNodes[i].name<<"is the source of"<<arcs[j].id;
                for(int k=0;k<transitionList.size();k++)
                {
                    //找到该ARC的终点TRANSITION
                    if(transitionList[k].id==arcList[j].target)
                    {
                        //向函数表达式中增加负项因子
                        l_FunDef.m_sFunctionExp.append("-1*(");
                        l_FunDef.m_sFunctionExp.append(QString::number(arcList[j].weight).toStdString());
                        l_FunDef.m_sFunctionExp.append(")*(");
                        //如果变迁（反应）速率符合质量作用定律
                        if(transitionList[k].self_function.contains("MassAction"))
                            {
                                QString temp=(transitionList[k].self_function.split("MassAction"))[1];
                                for(int m=0;m<transitionList.size();m++)
                                {
                                    //？？？同名变迁同步
                                    if(transitionList[m].name==transitionList[k].name&&m!=k)
                                    {
                                        //通过寻找前置弧来寻找该反应（变迁）对应的反应物（消耗的库所）
                                        for(int p=0;p<arcList.size();p++)
                                        {
                                            //找到反应物后继续补充反应速率因子
                                            if(arcList[p].target==transitionList[m].id)
                                            {
                                                temp.append("*(");
                                                temp.append(l_mtemp[arcList[p].id]);
                                                temp.append(")");
                                            }
                                        }
                                    }
                                }
                                //通过寻找前置弧来寻找该反应（变迁）对应的反应物（消耗的库所）
                                for(int m=0;m<arcList.size();m++)
                                {
                                    //找到反应物后继续补充反应速率因子
                                    if(arcList[m].target==transitionList[k].id)
                                    {
                                        temp.append("*(");
                                        temp.append(l_mtemp[arcList[m].id]);
                                        temp.append(")");
                                    }
                                }
                                l_FunDef.m_sFunctionExp.append(temp.toStdString());
                            }
                        //否则反应速率为参数*反应物名字（其余为非法结构,之后在解析表达式时需要对此进行检测）
                        else
                            {
                                l_FunDef.m_sFunctionExp.append(transitionList[k].self_function.toStdString());
                            }
                        l_FunDef.m_sFunctionExp.append(")");
                        break;
                    }
                }
            }
            //PLACE为该ARC终点
            else if(arcList[j].target==placeList[i].id)
            {
                //qDebug()<<placeNodes[i].name<<"is the target of"<<arcs[j].id;
                for(int k=0;k<transitionList.size();k++)
                {
                    //找到该ARC的起点TRANSITION
                    if(transitionList[k].id==arcList[j].source)
                    {
                        {
                            //如果该库所只作为生成物
                            if(l_FunDef.m_sFunctionExp=="")
                                l_FunDef.m_sFunctionExp.append("1*(");
                            //如果该库所为反应物和生成物
                            else
                                l_FunDef.m_sFunctionExp.append("+1*(");
                            l_FunDef.m_sFunctionExp.append(QString::number(arcList[j].weight).toStdString());
                            l_FunDef.m_sFunctionExp.append(")*(");
                            if(transitionList[k].self_function.contains("MassAction"))
                            {
                                QString temp=(transitionList[k].self_function.split("MassAction"))[1];
                                for(int m=0;m<transitionList.size();m++)
                                {
                                    if(transitionList[m].name==transitionList[k].name&&m!=k)
                                    {
                                        for(int p=0;p<arcList.size();p++)
                                        {
                                            if(arcList[p].target==transitionList[m].id)
                                            {
                                                temp.append("*(");
                                                temp.append(l_mtemp[arcList[p].id]);
                                                temp.append(")");
                                            }
                                        }
                                    }
                                }
                                for(int m=0;m<arcList.size();m++)
                                {
                                    if(arcList[m].target==transitionList[k].id)
                                    {
                                        temp.append("*(");
                                        temp.append(l_mtemp[arcList[m].id]);
                                        temp.append(")");
                                    }
                                }
                                l_FunDef.m_sFunctionExp.append(temp.toStdString());
                            }
                            else
                            {
                                l_FunDef.m_sFunctionExp.append(transitionList[k].self_function.toStdString());
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
            samename.push_back(placeList[i].name);
        }
        else
        {
            m_vFunDef[recordpos]=l_FunDef;
        }
    }
    //测试生成的函数表达式
    for(unsigned int i = 0; i<m_vFunDef.size();++i)
    {
        qDebug()<< QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" = "<<QString::fromStdString(m_vFunDef[i].m_sFunctionExp);
    }
}

void Component::transform()
{
    for(int i=0;i<mynet->PlaceList.size();i++)
    {
        PLACE_ATTR p=mynet->PlaceList[i]->toXml();
        this->placeList.push_back(p);
    }
    for(int i=0;i<mynet->TransitionList.size();i++)
    {
         TRANSITION_ATTR t=mynet->TransitionList[i]->toXml();
         this->transitionList.push_back(t);
    }
    for(int i=0;i<mynet->ArcList.size();i++)
    {
         ARC_ATTR a=mynet->ArcList[i]->toXml();
         this->arcList.push_back(a);
    }

}

bool Component::tick(double l_start,bool state = true)
{
//            qDebug()<<"tick() is in thread: "<<QThread::currentThreadId();
            //ode计算器初始化
            ODEsolver l_solver;
            l_solver.setMap(m_mInputVaraible2Value);
            l_solver.setVector(m_vFunDef);
            //解析函数表达式的变量，检查合法性
            bool l_check=l_solver.parser();
            if(l_check==false)
            {
                qDebug()<<"check result: false";
                return false;
            }
            else
            {
                map<string,double> name2value;
                name2value.clear();
                vector<double>receiver;
                //如果仿真需要检查负值
                if(state)
                {
                        //此时l_solver仍为上一步
                        ODEsolver ode1=l_solver;
                        //计算下一步的值
                        receiver=ode1.evaluate(l_start,m_step,true);
                        //记录步长
                        double record_dh=m_step;
                        //检测是否小于0，每个循环将一个零点处的斜率置为0来修正结果
                        while(true)
                        {
                            //flag用来判断是否均为非负
                            int flag=1;
                            //min_step为使所有值均为非负的步长
                            double min_step=record_dh;
                            //二分法中用来记录支点右移前的原位置，等同于左边界
                            double pre_step=0;
                            //对于每一个下一步值
                            for(int i=0;i<receiver.size();i++)
                            {
                                //flag2判断是否有次数用尽但仍未到0
                                int flag2=1;
                                //二分法的支点，初始值设置为中点
                                double step=0.5*record_dh;
                                //二分法左边界
                                double l_wall=0.0;
                                //二分法右边界
                                double r_wall=record_dh;
                                //检测一个receiver若小于0，则重复至求得为0时步长
                                if(receiver[i]<0)
                                {
                                    flag=0;//存在负值
                                    ODEsolver ode4=l_solver;
                                    //不同的步长，计算下一步值
                                    receiver[i]=(ode4.evaluate(l_start,step,true))[i];
                                    int count=0;
                                    //二分法求零点
                                    while(receiver[i]<-0.00000000001||receiver[i]>0.00000000001)
                                    {
                                        ODEsolver ode2=l_solver;
                                        //零点在支点右边
                                        if(receiver[i]>0.00000000001)
                                        {
                                            l_wall=step;
                                            //支点右移
                                            step=(step+r_wall)/2;
                                            pre_step=step;
                                        }
                                        //零点在支点左边
                                        else if(receiver[i]<-0.00000000001)
                                        {
                                            r_wall=step;
                                            //支点左移
                                            step=(l_wall+step)/2;
                                        }
                                        receiver[i]=(ode2.evaluate(l_start,step,true))[i];
                                        count++;
                                        //重复n次，若n次后仍未定位到0，退出循环
                                        if(count==50)
                                        {
                                            flag2=0;
                                            break;
                                        }
                                    }
                                }
                                //若step没定位到零点
                                if(flag2==0)
                                    min_step=min(min_step,pre_step);
                                //若step定位到零点
                                else min_step=min(min_step,step);
                            }
                            //如果值全部为非负
                            if(flag==1)
                            {
                                break;
                            }
                            //按最小步长进行计算，更新映射表，映射表的（值可能）出现最小零点
                            receiver=l_solver.evaluate(l_start,min_step,true);
                            ODEsolver ode3=l_solver;
                            //计算原步长与下一步长的差值
                            record_dh-=min_step;
                            //evaluate通过识别映射表的向下零点，对相应函数表达式清零，得到非负结果
                            receiver=ode3.evaluate(l_start,record_dh,true);
                        }
                        receiver=l_solver.evaluate(l_start,record_dh,true);

                        //qDebug()<<dx<<" RESULT";
                }
                //如果仿真不需要检查负值
                else
                {
                    //计算
                    receiver=l_solver.evaluate(l_start,m_step,false);
                 }
                 /***
                  *将receiver中的数值更新到placeList和m_mInputVaraible2Value中
                  * receiver的数据顺序和m_vFunDef和placeList顺序一致
                  */
                 for(unsigned int i = 0; i < receiver.size();i++)
                 {
                     qDebug()<<receiver[i];
                     m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]=receiver[i];
                     placeList[i].initmark=receiver[i];
                 }
            }

        return true;


}

void Component::setPlace_ATTRList(QList<PLACE_ATTR> p)
{
    this->placeList=p;
}
void Component::setTransition_ATTRList(QList<TRANSITION_ATTR> t)
{
    this->transitionList=t;
}
void Component::setArc_ATTRList(QList<ARC_ATTR> a)
{
    this->arcList=a;
}

bool Component::changeTokens(QString placeID,double tokens)
{
    bool found = false;
    for(int i = 0; i<placeList.size();i++)
    {
        if(placeID == placeList[i].id)
        {
            placeList[i].initmark=tokens;
            //（易漏）仿真是通过map来获取token数据，因此token需要修改时需要修改map的内容，注意key为库所的name而不是id
            m_mInputVaraible2Value[placeList[i].name.toStdString()]=tokens;
            found = true;
            break;
        }
    }
    return found;
}

Component::Component(Component*source)
{
    placeList=source->getPlace_ATTRList();
    transitionList=source->getTransition_ATTRList();
    arcList=source->getArc_ATTRList();
    m_step=source->getStep();
    Component_id=source->Component_id;
    label=source->label;
}

Component::Component(PTNscene*scene,QGraphicsView*view,COMPONENT_ATTR componentAttr,int count)
{
    m_View=view;
    m_Scene=scene;
    placeList.clear();
    transitionList.clear();
    arcList.clear();
    QString l_newID,l_oldID;
    for(int i=0;i<componentAttr.transitionNodes.size();i++)
    {
        l_oldID=componentAttr.transitionNodes[i].id;
        l_newID=l_newID=l_oldID.split('&')[0]+'&'+QString::number(count)+'&'+l_oldID.split('&')[1];
        componentAttr.transitionNodes[i].id=l_newID;
    }
    for(int i=0;i<componentAttr.placeNodes.size();i++)
    {
        l_oldID=componentAttr.placeNodes[i].id;
        l_newID=l_newID=l_oldID.split('&')[0]+'&'+QString::number(count)+'&'+l_oldID.split('&')[1];
        componentAttr.placeNodes[i].id=l_newID;
    }
    for(int i=0;i<componentAttr.arcs.size();i++)
    {
        l_oldID=componentAttr.arcs[i].id;
        l_newID=l_newID=l_oldID.split('&')[0]+'&'+QString::number(count)+'&'+l_oldID.split('&')[1];
        componentAttr.arcs[i].id=l_newID;
        l_oldID=componentAttr.arcs[i].source;
        l_newID=l_newID=l_oldID.split('&')[0]+'&'+QString::number(count)+'&'+l_oldID.split('&')[1];
        componentAttr.arcs[i].source=l_newID;
        l_oldID=componentAttr.arcs[i].target;
        l_newID=l_newID=l_oldID.split('&')[0]+'&'+QString::number(count)+'&'+l_oldID.split('&')[1];
        componentAttr.arcs[i].target=l_newID;
    }
    m_step=componentAttr.step;
    Component_id=componentAttr.id+'&'+QString::number(count);
    placeList=componentAttr.placeNodes;
    transitionList=componentAttr.transitionNodes;
    arcList=componentAttr.arcs;

    m_Scene->from_Xml_Component (componentAttr);
    // 为视图设置场景
    m_View->centerOn(m_Scene->itemsBoundingRect().center());
//    qDebug()<<"component "<<Component_id<<" 's count is "<<count;
}






















