#include "compoundcomponentlist.h"

CompoundComponentList::CompoundComponentList(QObject *parent) : QObject(parent)
{

}


CompoundComponent *CompoundComponentList::getCertainCompoundComponent(QString ID)
{
    for(int i=0;i<this->CompoundComponent_List.size();i++)
    {
        QStringList s=ID.split("+");
        //传入的ID为port
        if(s[0].split("&").size()>2)
        {
            QStringList b=s[0].split("&");
            QString ID=b[1]+b[2];
            for(int i=0;i<CompoundComponent_List.size();i++)
            {
                QStringList compID=CompoundComponent_List[i]->getAllComponentID();
                for(int i=0;i<compID.size();i++)
                {
                    if(ID==compID[i])
                    {
                        return CompoundComponent_List[i];
                    }
                }
            }
        }
        //组号
        else if(s[0].split("&").size()==2)
        {
            for(int i=0;i<CompoundComponent_List.size();i++)
            {
                QStringList compID=CompoundComponent_List[i]->getAllComponentID();
                for(int i=0;i<compID.size();i++)
                {
                    if(s[0]==compID[i])
                    {
                        return CompoundComponent_List[i];
                    }
                }
            }
        }

    }
    return nullptr;
}



void CompoundComponentList::initial(QVector<Component *> com_arry)
{
    for(int i=0;i<com_arry.size();i++)
    {
        CompoundComponent*comp_com=new CompoundComponent();
        comp_com->push_back_Component(com_arry[i]);
        this->CompoundComponent_List.push_back(comp_com);
    }
}

void CompoundComponentList::updataAllID()
{
    for(int i=0;i<this->CompoundComponent_List.size();i++)
    {
        CompoundComponent_List[i]->updataID();
    }
}

QList<Component *> CompoundComponentList::parseCompoundComponentID(QString CompoundComponentID)
{
    for(int i=0;i<this->CompoundComponent_List.size();i++)
    {
        if(CompoundComponent_List[i]->getCompoundComponentID()==CompoundComponentID)
        {
            return CompoundComponent_List[i]->getComponent_list();
        }
    }
}

Place *CompoundComponentList::getCertainPlace(QString PlaceID)
{
    QStringList s=PlaceID.split("+");
    QString ComID=s[0];
    for(int i=0;i<CompoundComponent_List.size();i++)
    {
        QStringList ComponentID=CompoundComponent_List[i]->getAllComponentID();

        for(int y=0;y<ComponentID.size();i++)
        {
            if(ComponentID[y]==ComID)
            {
                CompoundComponent_List[i]->getComponent_list()[y]->getCertainPlace(PlaceID);
            }
        }
    }
}

//获取指定组件的端口对象（仅返回普通端口）
QList<Place *> CompoundComponentList::getPortinComponent(QString ComponentID)
{
    return getCertainCompoundComponent(ComponentID)->getCertainComponet(ComponentID)->getNormalPort();
}

QList<QString > CompoundComponentList::getCertainPlaceName(QString ComponentID)
{
    //传入指定组件的组件ID，返回该组件内部所有placeID，复合组件返回该ComponentID这一侧的name
    CompoundComponent*comp_com=new CompoundComponent();
    comp_com=this->getCertainCompoundComponent(ComponentID);
    Component*com=new Component;
    com=comp_com->getCertainComponet(ComponentID);
    QList<QString>PlaceName;
    for(int i=0;i<com->getPlaceList().size();i++)
    {
        //先按照+拆分ID，先把复合端口找出来
        QStringList ID=com->getPlaceList()[i]->getId().split("+");
        //如果是复合端口
        for(int i=0;i<ID.size();i++)
        {
            QStringList id=ID[i].split("&");
            QString comID=id[0]+id[1];
            if(comID==ComponentID)
            {
                PlaceName.push_back(id[2]);
            }
        }
    }
    return PlaceName;

}

QList<QString> CompoundComponentList::getCertainTransitionName(QString ComponentID)
{
    //传入指定组件的组件ID，返回该组件内部所有TransitionID
    CompoundComponent*comp_com=new CompoundComponent();
    comp_com=this->getCertainCompoundComponent(ComponentID);
    Component*com=new Component;
    com=comp_com->getCertainComponet(ComponentID);
    QList<QString>TransitionName;
    for(int i=0;i<com->getTransitionList().size();i++)
    {

        QStringList ID=com->getTransitionList()[i]->getId().split("&");
        TransitionName.push_back(ID[2]);

    }
    return TransitionName;
}

QString CompoundComponentList::setnewComponentIDinSimulation(Component *newComponent)
{
    //在addNewComponent()函数中调用
    //为新添加的组件分配ID
    //遍历当前复合组件列表与垃圾桶，数有几个该类型的文件（文件名相同的文件),序列号在此基础上加1
    int count=0;//计数器
    QString filename=newComponent->getID().split("&")[0];
    for(int i=0;i<this->CompoundComponent_List.size();i++)
    {
        QStringList AllComponentID=this->CompoundComponent_List[i]->getAllComponentID();
        for(int i=0;i<AllComponentID.size();i++)
        {
            if(AllComponentID[i]==filename)
            {
                count++;
            }
        }

    }
    for(int i=0;i<garbage.size();i++)
    {
        if(garbage[i]->getID()==filename)
        {
            count++;
        }
    }
    QString num=QString::number(count);
    //bug
    newComponent->setID(filename+"&"+num);
    return (filename+"&"+num);
}

void CompoundComponentList::seperateCompoundPort(QString CompoundPortID)
{
    //
}

