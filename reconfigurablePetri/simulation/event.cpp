#include "event.h"
Event::Event(Component*component,double time,int prior)
{
    m_component=component;
    m_step=m_component->getStep();
    m_time=time+m_step;
}

void Event::update()
{
    m_time+=m_step;
}
void Event::setPrior(int prior)
{
    m_prior=prior;
}
