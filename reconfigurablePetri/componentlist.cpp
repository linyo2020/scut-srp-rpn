#include "componentlist.h"

ComponentList::ComponentList(QObject *parent) : QObject(parent)
{

}

ComponentList::ComponentList(QVector<Component *> c_list)
{
    for(int i=0;i<c_list.size();i++)
    {
        this->com_list.push_back(c_list[i]);
    }
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

    for(int i=0;i<garbage.size();i++)
    {
        if(garbage[i]->getComponentFileName()==newComponent->getComponentFileName())
        {
            count++;
        }
    }

    newComponent->setID(newComponent->getComponentFileName()+QString::number(count));
    return (newComponent->getComponentFileName()+QString::number(count));
}
