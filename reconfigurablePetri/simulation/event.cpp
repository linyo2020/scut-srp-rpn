#include "event.h"
#include"QThread"
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
     bool structChanged =false;
     if(execution==m_type)
     {
        //单步仿真
        //模拟
//         qDebug()<<"Event::occur is in thread: "<<QThread::currentThreadId();
         qDebug()<<m_component->getID()<<" has one simulation finished at time "<<m_time;
         m_component->tick(m_time-m_step,true);
//         QList<PLACE_ATTR>l_placeList=m_component->getPlace_ATTRList();
//                 for( int i = 0; i<l_placeList.size();i++)
//                 {
//                      qDebug()<<"place name: "<<l_placeList[i].name<<"and token after one step: "<<l_placeList[i].initmark;
//                 }
         structChanged=true;
     }
     else{
         /***
          * 规则判断
          */
         qDebug()<<"rule has one check at time "<<m_time;
         //模拟0时刻开始，第四十次规则判断时触发规则
         if(abs(m_time-40*m_step)<0.00000000001)
             structChanged=true;
     }
     //更新下一次仿真时间
     update();
     return structChanged;
}

int Event::getPrior()
{
    return m_prior;
}

double Event::getTime()
{
    return m_time;
}

double Event::getStep()
{
    return m_step;
}

Component* Event::getComponent()
{
    return m_component;
}
