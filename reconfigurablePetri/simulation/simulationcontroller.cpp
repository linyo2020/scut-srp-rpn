#include "simulationcontroller.h"

SimulationController::SimulationController(ComponentList*list,Plot*gui,double start,double end,double step)
{

    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<string>("string");
    m_compList=new ComponentList(list);
    m_gui=gui;
    m_step = step;
    m_start = start;
    m_end = end;
    connect(this, &SimulationController::updateui, this, &SimulationController::slotUpdateUi);
    connect(this, &SimulationController::addgraph,this,&SimulationController::slotAddGraph);
    connect(this, &SimulationController::adddata,this,&SimulationController::slotAddData);
}

void SimulationController::run()
{
    bool suc = true;
    qDebug()<<"simulation is in thread: "<<QThread::currentThreadId();

    /***
     * *测试获取的com_list信息
     */
    if(m_compList!=nullptr)
        qDebug()<<"get not null ptr : com_list";
    Component*l_Component=nullptr;
    QList<PLACE_ATTR> l_placeList;
    QVector<Component*>l_vComponent = m_compList->getComponentList();
    for( int i = 0; i<l_vComponent.size();i++)
    {
        l_Component=l_vComponent[i];
        ///目前无法获得步长数据！！！
        l_vComponent[i]->setStep(0.5);
        qDebug()<<"this is the "<<i<<"component :"<<l_vComponent[i]->getID()<<", and step is "<<l_vComponent[i]->getStep();
        l_placeList=l_vComponent[i]->getPlace_ATTRList();
        for( int i = 0; i<l_placeList.size();i++)
        {
             qDebug()<<"place name: "<<l_placeList[i].name<<"and token : "<<l_placeList[i].initmark;
        }
        //测试：速率函数的生成
        l_vComponent[i]->makeFunction();
        //测试：单步仿真
        l_vComponent[i]->tick(1,true);
        //获取更新后的数据并打印
        l_vComponent = m_compList->getComponentList();
        l_placeList=l_vComponent[i]->getPlace_ATTRList();
        for( int i = 0; i<l_placeList.size();i++)
        {
             qDebug()<<"place name: "<<l_placeList[i].name<<"and token after one step: "<<l_placeList[i].initmark;
        }
    }
    //测试获取的connector信息
    QList<Connector*>l_connectorList=m_compList->getConnectorList();
    for( int i = 0; i < l_connectorList.size();i++)
    {
        qDebug()<<"connector "<<i<<" is from "<<l_connectorList[i]->getSourceId()<<" to "<<l_connectorList[i]->getTargetId();
    }
    //测试数据可视化
    datavv[0].clear();
    double l_x=0,l_y1=0,l_y2=0;
    string l_s1 = "test1";
    string l_s2 = "test2";
    emit addgraph(l_s1);
    emit addgraph(l_s2);
    for(int i = 0; i<10;i++)
    {
        l_x+=1;
        l_y1+=0.5;
        l_y2+=1;

        QVector<double>temp1,temp2,temp3,temp;
        temp1.push_back(l_x);
        temp2.push_back(l_y1);
        temp3.push_back(l_y2);
        temp.push_back(l_y1);
        temp.push_back(l_y2);
        datavv[0].push_back(temp);
        emit adddata(0,temp1,temp2);
        emit adddata(1,temp1,temp3);
    }
}

void SimulationController::slotAddGraph(string s)
{
    m_gui->addGraph(s);
}
void SimulationController::slotAddData(unsigned i,QVector<double>t1,QVector<double>t2)
{
    m_gui->addData(i,t1,t2);
}
void SimulationController::slotUpdateUi(double x,QString y)
{
    m_gui->updateUi(x,y);
}

