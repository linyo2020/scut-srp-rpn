#include "compoundcomponent.h"

CompoundComponent::CompoundComponent()
{

}

QStringList CompoundComponent::getAllComponentID()
{
    QStringList s=this->CompoundComponentID.split("+");
    return s;
}

void CompoundComponent::updataID()
{
    for(int i=0;i<this->getComponent_list().size();i++)
    {
        this->CompoundComponentID+=this->getComponent_list()[i]->getID();
    }
}

bool CompoundComponent::deleteCertainComponent(QString ComponentID)
{
    for(int i=0;i<this->component_list.size();i++)
    {
        if(component_list[i]->Component_id==ComponentID)
        {

            this->component_list.removeOne(component_list[i]);
            return true;
        }

    }
    return false;
}

QString CompoundComponent::getCompoundComponentID()
{
    return this->CompoundComponentID;
}

void CompoundComponent::setCompoundComponentID(QString id)
{
    this->CompoundComponentID=id;
}

Component *CompoundComponent::getCertainComponet(QString ComponentID)
{
    for(int i=0;i<this->getComponent_list().size();i++)
    {
        if(this->component_list[i]->getID()==ComponentID)
        {
            return component_list[i];
        }
    }
}

QString CompoundComponent::push_back_Component(Component *com)
{
    component_list.push_back(com);
    this->CompoundComponentID+=com->getID();
    return this->CompoundComponentID;
}

Place *CompoundComponent::getCertainPlace(QString PlaceID)
{

}

QStringList CompoundComponent::seperatePortID(QString CompoundPort)
{
    QStringList s=CompoundPort.split("+");
    return s;
}

bool CompoundComponent::isEmpty()
{
    return (this->getComponent_list().size()==0);
}

QList<Component *> CompoundComponent::getComponent_list()
{
    return this->component_list;
}


