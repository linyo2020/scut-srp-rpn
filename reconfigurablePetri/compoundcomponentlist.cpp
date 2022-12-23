#include "compoundcomponentlist.h"

CompoundComponentList::CompoundComponentList(QObject *parent) : QObject(parent)
{

}

CompoundComponentList::CompoundComponentList(QVector<Component *> com_arry)
{
    this->old=com_arry;

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
