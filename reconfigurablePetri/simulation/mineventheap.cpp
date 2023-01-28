#include "mineventheap.h"

MinEventHeap::MinEventHeap()
{

}
MinEventHeap::MinEventHeap(QVector<Event*>vEvent,int number)
{
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
        if (l_sonIndex + 1 < m_vEvent.size() && m_vEvent[l_sonIndex] > m_vEvent[l_sonIndex + 1])
        {
            l_sonIndex++; //取值两个子节点 值更小的节点下标
        }
        //若子节点小，交换
        if (m_vEvent[i] > m_vEvent[l_sonIndex])
        {
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
            if (i > 0 && m_vEvent[i] < m_vEvent[l_fatherIndex])
            {
                swap(i, l_fatherIndex);
                up(l_fatherIndex);
            }
}
