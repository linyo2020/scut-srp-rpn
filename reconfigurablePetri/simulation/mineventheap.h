#ifndef MINEVENTHEAP_H
#define MINEVENTHEAP_H
#include<QVector>
#include "event.h"
class MinEventHeap
{
public:
    MinEventHeap();
    void update(QVector<Event*>m_vEvent,int number);
    /**
     * @brief push
     */
    void push(Event*);
    /**
     * @brief pop
     * @return
     */
    Event* pop();
    /**
     * @brief down
     * @param i
     */
    void down(int i);
    /**
     * @brief swap
     * @param i
     * @param j
     */
    void swap(int i,int j);
    /**
     * @brief up
     * @param i
     */
    void up(int i);
    /**
     * @brief show
     */
    void show();
    /**
     * @brief clear
     */
    void clear();
    /**
     * @brief empty
     * @return
     */
    bool empty();
    /**
     * @brief getVector
     * @return
     */
    QVector<Event*> getVector();
private:
QVector<Event*>m_vEvent;
};

#endif // MINEVENTHEAP_H
