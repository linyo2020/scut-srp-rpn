#include "event.h"
Event::Event(Component*component,double time,int prior)
{
    m_type=execution;
    if(!m_component)
        qDebug()<<"warning :event cannot get the component!";
    m_component=component;
    m_step=m_component->getStep();
    m_time=time+m_step;
    m_prior=prior;
    qDebug()<<m_component->getID()<<"'s time in events is "<<m_time;
}

Event::Event(double step,double time)
{
    m_type=rule;
    m_step=step;
    m_time=time+m_step;
    m_prior=MAX_PRIOR;
    m_component=nullptr;
}

void Event::update()
{
    m_time+=m_step;
}
void Event::setPrior(int prior)
{
    m_prior=prior;
}

QString Event::showCompId()
{
     if(execution==m_type)
        return m_component->getID();
     else {
        return QString("rule");
     }
}

bool Event::occur()
{
     bool strutChanged =false;
     if(execution==m_type)
     {
        //单步仿真
        //模拟
         qDebug()<<m_component->getID()<<" has one simulation finished at time "<<m_time;
     }
     else{
         /***
          * 规则判断
          */
         qDebug()<<"rule has one check at time "<<m_time;
     }
     //更新下一次仿真时间
     update();
     return strutChanged;
}

int Event::getPrior()
{
    return m_prior;
}

double Event::getTime()
{
    return m_time;
}
