#include "mineventheap.h"

MinEventHeap::MinEventHeap()
{

}
void MinEventHeap::update(QVector<Event*>vEvent,int number)
{
    m_vEvent.clear();
    for(int i =0;i<number;i++)
    {
        m_vEvent.push_back(vEvent[i]);
    }
    for(int i = m_vEvent.size()/2-1;i>=0;i--)
    {
        down(i);
    }
}
void MinEventHeap::push(Event*event)
{
    m_vEvent.push_back(event);
    up(m_vEvent.size()-1);
}
Event* MinEventHeap::pop()
{
    Event*l_result=m_vEvent[0];
    swap(0,m_vEvent.size()-1);
    m_vEvent.pop_back();
    down(0);
    return l_result;
}
void MinEventHeap::down(int i)
{
    int l_sonIndex = 2*i + 1;
    if (l_sonIndex < m_vEvent.size())
    {
        if (l_sonIndex + 1 < m_vEvent.size())
        { if(m_vEvent[l_sonIndex]->getTime() > m_vEvent[l_sonIndex + 1]->getTime())
            l_sonIndex++; //取值两个子节点之中值更小的节点下标
          else if(abs(m_vEvent[l_sonIndex]->getTime() - m_vEvent[l_sonIndex + 1]->getTime())<0.00000000001)
            {
                if(m_vEvent[l_sonIndex]->getPrior()>m_vEvent[l_sonIndex+1]->getPrior())
                    l_sonIndex++;
            }
        }
        //若子节点小，交换
        if (m_vEvent[i]->getTime() > m_vEvent[l_sonIndex]->getTime())
        {
            swap(i, l_sonIndex);
        }
        else if(abs(m_vEvent[l_sonIndex]->getTime() - m_vEvent[i]->getTime())<0.00000000001)
        {
            if(m_vEvent[i]->getPrior()>m_vEvent[l_sonIndex]->getPrior())
                swap(i, l_sonIndex);
        }
        down(l_sonIndex);
    }
}
void MinEventHeap::swap(int i,int j)
{
    Event* l_temp=m_vEvent[i];
    m_vEvent[i]=m_vEvent[j];
    m_vEvent[j]=l_temp;
}
void MinEventHeap::up(int i)
{
    int l_fatherIndex = (i - 1) / 2;
     if(i>0)
     {
         if(m_vEvent[i]->getTime()<m_vEvent[l_fatherIndex]->getTime())
         {
             swap(i, l_fatherIndex);
             up(l_fatherIndex);
         }
        else if(abs(m_vEvent[i]->getTime()-m_vEvent[l_fatherIndex]->getTime())<0.00000000001)
         {
             if(m_vEvent[i]->getPrior()<m_vEvent[l_fatherIndex]->getPrior())
             {
                 swap(i, l_fatherIndex);
                 up(l_fatherIndex);
             }

         }
     }
}

void MinEventHeap::show()
{
    qDebug()<<"in MinHeap: ";
    for(int i=0;i<m_vEvent.size();i++)
    {
        qDebug()<<m_vEvent[i]->showCompId()<<" 's priority is"<<m_vEvent[i]->getPrior()<<" and time "<<m_vEvent[i]->getTime();
    }
}

void MinEventHeap::clear()
{
    m_vEvent.clear();
}

bool MinEventHeap::empty()
{
    return m_vEvent.empty();
}

QVector<Event*>MinEventHeap::getVector()
{
    return m_vEvent;
}
