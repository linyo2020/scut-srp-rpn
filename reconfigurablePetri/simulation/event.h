#ifndef EVENT_H
#define EVENT_H
#include"component.h"

#define MAX_PRIOR 0

class Event
{
public:
    Event(Component*component,double time,int prior);
    Event(double step,double time);
    void setTime(double time);
    void update();
    void setPrior(int prior);
    QString showCompId();
    int getPrior();
    double getTime();
    bool occur();
private:
    int m_prior;
    enum type{rule,execution};
    type m_type;
    Component*m_component;
    double m_time;
    double m_step;

};

#endif // EVENT_H
