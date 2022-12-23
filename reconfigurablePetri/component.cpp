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

QString Component::getLabel() const
{
    return label;
}

void Component::setID(QString id)
{
    this->Component_id=id;
}

QString Component::getID()
{
    return this->Component_id;
}

void Component::setLabel(const QString &value)
{
    label = value;
}

QString Component::getComponent_id()
{
    return this->Component_id;
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
