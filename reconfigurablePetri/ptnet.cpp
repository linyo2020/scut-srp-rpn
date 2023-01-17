#include "ptnet.h"

PTNet::PTNet()
{

}


void PTNet::AddPlace(Place *myplace)
{
    this->PlaceList.push_back(myplace);
}

void PTNet::AddTransition(Transition *mytrans)
{
    this->TransitionList.push_back(mytrans);
}

void PTNet::AddArc(Arcus *myarc)
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
