#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H
#include <QThread>
#include "plot.h"

class SimulationController: public QThread
{
    Q_OBJECT

public:
    SimulationController(ComponentList*);
    void  run(bool&);
    /** 主线程对象指针*/
    Plot *m_gui;
    ComponentList*com_list;
};

#endif // SIMULATIONCONTROLLER_H
