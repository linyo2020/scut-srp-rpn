#ifndef PTNET_H
#define PTNET_H
#include"place.h"
#include"arc.h"
#include"transition.h"

class PTNet
{
public:
    PTNet();
    QList<Place*>PlaceList;
    QList<Transition*>TransitionList;
    //contained in place and transition
    //QList<Arc*>ArcList;

};

#endif // PTNET_H
