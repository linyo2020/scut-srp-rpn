#include "simulationcontroller.h"

SimulationController::SimulationController(ComponentList*list)
{
    com_list=list;
}

void SimulationController::run(bool &state)
{
    bool suc = true;
    if(com_list!=nullptr)
        qDebug()<<"get not null ptr : com_list";
    state = true;
}
