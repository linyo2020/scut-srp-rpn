#ifndef MINEVENTHEAP_H
#define MINEVENTHEAP_H
#include<QVector>
#include "event.h"
class MinEventHeap
{
public:
    MinEventHeap();
    void update(QVector<Event*>m_vEvent,int number);
    void push(Event*);
    Event* pop();
    void down(int i);
    void swap(int i,int j);
    void up(int i);
    void show();
    void clear();
    bool empty();
private:
QVector<Event*>m_vEvent;
};

#endif // MINEVENTHEAP_H
