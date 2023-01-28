#ifndef EVENT_H
#define EVENT_H
#include"component.h"

class Event
{
public:
    Event(Component*component,double time,int prior);
    void setTime(double time);
    void update();
    void setPrior(int prior);
private:
    int m_prior;
    enum m_type{rule,execution};
    Component*m_component;
    double m_time;
    double m_step;

};

#endif // EVENT_H
