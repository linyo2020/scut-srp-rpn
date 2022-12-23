#include "ptnet.h"

PTNet::PTNet()
{

}

PTNet::PTNet(PTNet &mynet)
{
    for(int i=0;i<mynet.PlaceList.size();i++)
    {
        Place*p=new Place();

    }

}

void PTNet::AddPlace(Place *myplace)
{
    this->PlaceList.push_back(myplace);
}

void PTNet::AddTransition(Transition *mytrans)
{
    this->TransitionList.push_back(mytrans);
}

void PTNet::AddArc(Arc *myarc)
{
    this->ArcList.push_back(myarc);
}

void PTNet::deletePlace(Place *myplace)
{
    for(int i=0;i<PlaceList.size();i++)
    {
        if(PlaceList[i]->getId()==myplace->getId())
        {
            PlaceList.removeOne(PlaceList[i]);
        }
    }
}

void PTNet::deleteTransition(Transition *mytrans)
{
    for(int i=0;i<TransitionList.size();i++)
    {
        if(TransitionList[i]->getId()==mytrans->getId())
        {
            TransitionList.removeOne(TransitionList[i]);
        }
    }
}
