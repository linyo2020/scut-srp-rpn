#include "simulationcontroller.h"

SimulationController::SimulationController(ComponentList*list)
{
    com_list=list;
}

void SimulationController::run(bool &state)
{
    bool suc = true;

    /***
     * *测试获取的com_list信息
     */
    if(com_list!=nullptr)
        qDebug()<<"get not null ptr : com_list";
    Component*l_Component=nullptr;
    QList<PLACE_ATTR> l_placeList;
    QVector<Component*>l_vComponentList = com_list->getComponentList();
    for(unsigned int i = 0; i<l_vComponentList.size();i++)
    {
        l_Component=l_vComponentList[i];
        qDebug()<<"this is the "<<i<<"component :"<<l_vComponentList[i]->getID();
        l_placeList=l_vComponentList[i]->getPlace_ATTRList();;
        for(unsigned int i = 0; i<l_placeList.size();i++)
        {
             qDebug()<<"place name: "<<l_placeList[i].name;
        }
        //测试：速率函数的生成
        l_vComponentList[i]->makeFunction();
    }
    state = true;
}


