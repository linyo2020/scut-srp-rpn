#include "simulationcontroller.h"
//允许的组件最大数量
#define COMP_NUM_MAX 100

//用于组件优先级排序的一些结构和变量
//---------------------------------------------------------------------------------
static int s_DFN[COMP_NUM_MAX];
static int s_low[COMP_NUM_MAX];
static int s_counts=1;
static int s_stack[COMP_NUM_MAX];
static int s_top=1;
static int s_flag[COMP_NUM_MAX];
static int s_number=0;
static int s_j;
static int s_matrix[COMP_NUM_MAX][COMP_NUM_MAX];
static int s_length;
static QList<int>s_priorList;//下标表示优先级大小，数值越小优先级越小；数组内容为组件的标号
//---------------------------------------------------------------------------------

//记录所有出现过的组件以及组件中第一个库所对应的曲线编号
static QMap<QString,int>s_mPlaceId2GraphIndex;
static int s_graphIndex=0;
//存储仿真数据,更新时机为组件更新绘图数据时
static QMap<QString,double>s_placeId2Value;
//记录组件id对应的组件列表下标
static QMap<QString,int>s_comId2ListIndex;
QString findCompId(QString const s)
{
    QStringList l_stringList=s.split("&");
    return l_stringList[0]+"&"+l_stringList[1];
}

SimulationController::SimulationController(ComponentList*list,RuleManager&ruleManager,Plot*gui,
                                           double start,double end,double step)
{

    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<string>("string");
    m_compList=new ComponentList(list);
    m_ruleManager=ruleManager;
    m_gui=gui;
    m_step = step;
    m_start = start;
    m_end = end;
    //test
    qDebug()<<"the step from plot is :"<<m_step;
    qDebug()<<"the start from plot is :"<<m_start;
    qDebug()<<"the end from plot is :"<<m_end;
    connect(this, &SimulationController::updateui, this, &SimulationController::slotUpdateUi);
    connect(this, &SimulationController::addgraph,this,&SimulationController::slotAddGraph);
    connect(this, &SimulationController::adddata,this,&SimulationController::slotAddData);
}

void SimulationController::run()
{
//测试数据-----------------------------------------------------------------------------------------------------------------------
//    bool suc = true;
//    qDebug()<<"simulation is in thread: "<<QThread::currentThreadId();

//    /***
//     * *测试获取的com_list信息
//     */
//    if(m_compList!=nullptr)
//        qDebug()<<"get not null ptr : com_list";
//    Component*l_Component=nullptr;
//    QList<PLACE_ATTR> l_placeList;
//    QVector<Component*>l_vComponent = m_compList->getComponentList();
//    for( int i = 0; i<l_vComponent.size();i++)
//    {
//        l_Component=l_vComponent[i];
//        ///目前无法获得步长数据！！！
//        l_vComponent[i]->setStep(0.5);
//        qDebug()<<"this is the "<<i<<"component :"<<l_vComponent[i]->getID()<<", and step is "<<l_vComponent[i]->getStep();
//        l_placeList=l_vComponent[i]->getPlace_ATTRList();
//        for( int j = 0; j<l_placeList.size();j++)
//        {
//             qDebug()<<"place name: "<<l_placeList[j].name<<"and token : "<<l_placeList[j].initmark;
//             //测试changeTokens函数
//             l_vComponent[i]->changeTokens(l_placeList[j].id,10);
//             qDebug()<<"changeTokens result: "<<l_vComponent[i]->getCertainPlaceToken(l_placeList[j].id);

//        }
//        //测试：速率函数的生成
//        l_vComponent[i]->makeFunction();
//        //测试：单步仿真与数据可视化
////        l_vComponent[i]->tick(1,true);
//          Event *l_event=new Event(l_vComponent[i],0,i+1);
//          initCompGraph(l_vComponent[i],0);
//          l_event->occur();
//          drawCompData(l_event->getComponent(),0.5);
//        //获取更新后的数据并打印
////        l_vComponent = m_compList->getComponentList();
////        l_placeList=l_vComponent[i]->getPlace_ATTRList();
//          l_placeList=l_event->getComponent()->getPlace_ATTRList();
//        for( int i = 0; i<l_placeList.size();i++)
//        {
//             qDebug()<<"place name: "<<l_placeList[i].name<<"and token after one step: "<<l_placeList[i].initmark;
//        }
//    }
//    //测试获取的connector信息
//    QList<CONNECTOR_ATTR>l_connectorList=m_compList->getConnectorAttrList();
//    for( int i = 0; i < l_connectorList.size();i++)
//    {
//        qDebug()<<"connector "<<i<<" is from "<<l_connectorList[i].source<<" to "<<l_connectorList[i].source;
//    }
//    //测试数据可视化
//    datavv[0].clear();
//    double l_x=0,l_y1=0,l_y2=0;
//    string l_s1 = "test1";
//    string l_s2 = "test2";
//    emit addgraph(l_s1);
//    emit addgraph(l_s2);
//    for(int i = 0; i<10;i++)
//    {
//        l_x+=1;
//        l_y1+=0.5;
//        l_y2+=1;

//        QVector<double>temp1,temp2,temp3,temp;
//        temp1.push_back(l_x);
//        temp2.push_back(l_y1);
//        temp3.push_back(l_y2);
//        temp.push_back(l_y1);
//        temp.push_back(l_y2);
//        datavv[0].push_back(temp);
//        emit adddata(0,temp1,temp2);
//        emit adddata(1,temp1,temp3);
//    }
//    //测试componentlist的获取token函数
//    QList<double>l_tokensList=m_compList->getCertainPlaceToken(QString("C3&p1"),1);
//    if(!l_tokensList.empty())
//    {
//        qDebug()<<"the token list of C3&p1 : ";
//        qDebug()<<l_tokensList;
//    }
//    else qDebug()<<"the token list is empty";
//-------------------------------------------------------------------------------------------------------------------------

//    QVector<Component*> l_vComponent=m_compList->getComponentList();
//    int l_length=l_vComponent.size();
////    qDebug()<<"仿真步长模拟";
//    for(int i = 0;i<l_length;i++)
//    {
//        //记录组件id对应的组件列表下标
//        s_comId2ListIndex[l_vComponent[i]->getID()]=i;
//        //记录各库所的token值
//        QList<PLACE_ATTR>l_placeAttrList=l_vComponent[i]->getPlace_ATTRList();
//        for(int i=0;i<l_placeAttrList.size();i++)
//        {
//            s_placeId2Value[l_placeAttrList[i].id]=l_placeAttrList[i].initmark;
//        }
//        //设置模拟步长
//        qDebug()<<l_vComponent[i]->getID()<<" ' step : "<<l_vComponent[i]->getStep();
//        l_vComponent[i]->setStep(0.1*i+0.1);
//        //qDebug()<<l_vComponent[i]->getID()<<" : "<<l_vComponent[i]->getStep();
//    }
//    //1.对组件进行优先级排序
//    if(sort())
//        qDebug()<<"components have been sorted";
//    //2.生成事件树
//    QVector<Event*>l_vEvent;
//    QMap<QString,int>l_compId2Index;
//    Event*l_EventPtr1=nullptr;
//    Event*l_EventPtr2=nullptr;
//    if(s_priorList.size()!=l_length)
//        qDebug()<<"warning: the size of priorList is not the same as compVector's !";
//    MinEventHeap*l_MinHeap=new MinEventHeap();
//    //connector数据同步
//    initConnect();
//    //遍历s_priorList
//    for(int i = 0; i<s_length;i++)
//    {
////        qDebug()<<l_vComponent[s_priorList[i]]->getID()<<" 's priority is "<<i;
//        l_EventPtr1=new Event(l_vComponent[s_priorList[i]],m_start,l_length+1-i);
//        l_vComponent[s_priorList[i]]->makeFunction();//易漏
//        l_MinHeap->push(l_EventPtr1);
//        //初始化曲线
//        initCompGraph(l_vComponent[s_priorList[i]],m_start);
//    }
//    //3.规则库初始化
//    //3.1初始化规则库控制器
//    m_ruleManager.initRule(m_compList);
//    //3.2初始化规则判断事件
//    l_EventPtr1=new Event(m_step,m_start);
//    l_MinHeap->push(l_EventPtr1);
//    l_EventPtr1=nullptr;
//    l_MinHeap->show();
//    //4.进行仿真
//    while(!l_MinHeap->empty())
//    {
//        l_EventPtr1=l_MinHeap->pop();
//        //记录时间戳
//        double l_tempTime = l_EventPtr1->getTime();
//        if(l_tempTime>m_end)
//            break;
//        if(l_EventPtr1->getPrior()==0)
//        {
//            l_EventPtr1->occur();
//            RULE_RUNTIME_INFOMATION l_ruleRunTimeInfo{l_tempTime};
//               if(m_ruleManager.applyRule(l_ruleRunTimeInfo))
//               {
//                   //如果事件为规则类型，发生重构,需要重新分析组件拓扑图和修改事件堆
//                       //模拟重构操作：删除一个组件以及相应的连接件
//       //                if(m_compList->simulateStructChanged())
//       //                m_compList->show();

//                       //计算组件优先级
//                       if(sort())
//                           qDebug()<<"components have been sorted";
//                       //获取新的组件信息
//                       l_vComponent=m_compList->getComponentList();
//                       l_length=l_vComponent.size();//l_length好像可以用length替换
//                       //更新组件在组件容器里的位置以及库所与其token值的映射
//                       //s_comId2ListIndex和s_placeId2Value可能需要清空
//                       for(int i = 0;i<l_length;i++)
//                       {
//                           //记录组件id对应的组件列表下标
//                           s_comId2ListIndex[l_vComponent[i]->getID()]=i;
//                           //记录各库所的token值
//                           QList<PLACE_ATTR>l_placeAttrList=l_vComponent[i]->getPlace_ATTRList();
//                           for(int i=0;i<l_placeAttrList.size();i++)
//                           {
//                               s_placeId2Value[l_placeAttrList[i].id]=l_placeAttrList[i].initmark;
//                           };
//                       }
//                       //更新connector的同步token值
//                       updateConnect();

//                       l_vEvent=l_MinHeap->getVector();
//                       l_MinHeap->clear();
//                       for(int i =0;i<l_vEvent.size();i++)
//                       {
//                           l_compId2Index[l_vEvent[i]->showCompId()]=i;
//                       }
//                       //以优先级的顺序遍历每个组件
//                       for(int i =0;i<s_length;i++)
//                       {
//                           QString l_tempId=l_vComponent[s_priorList[i]]->getID();
//                           //重构后的组件分为两种情况：旧组件（将对应事件的优先级更新）；新组件（创建对应事件）
//                           if(l_compId2Index.contains( l_tempId))
//                           {
//                               l_EventPtr2=l_vEvent[l_compId2Index[l_tempId]];
//                               l_EventPtr2->setPrior(s_length+1-i);
//                           }
//                           else
//                           {
//                               qDebug()<<l_vComponent[s_priorList[i]]->getID()<<" is new added";
//                               //ui仿真步长暂时无法修改
//                               //---------------------------------------------------
//                               l_vComponent[s_priorList[i]]->setStep(0.5);
//                               //---------------------------------------------------
//                               l_EventPtr2=new Event(l_vComponent[s_priorList[i]],l_tempTime,s_length+1-i);
//                               initCompGraph(l_vComponent[s_priorList[i]],l_tempTime);
//                           }
//                           l_MinHeap->push(l_EventPtr2);
//                       }
//                       l_MinHeap->show();
//               }

//        }
//        else{
////                Component*l_compTemp = l_EventPtr1->getComponent();
////                QList<PLACE_ATTR>l_placeList=l_compTemp->getPlace_ATTRList();
////                        for( int i = 0; i<l_placeList.size();i++)
////                        {
////                             qDebug()<<"place name: "<<l_placeList[i].name<<"and token after one step: "<<l_placeList[i].initmark;
////                        }
//                if(l_EventPtr1->occur())
//                {
//                    connectData(l_EventPtr1->getComponent(),l_tempTime);
//                    drawCompData(l_EventPtr1->getComponent(),l_tempTime);
//                }
//             }
//        l_MinHeap->push(l_EventPtr1);
//    }

//-----------------------------------------------------------------------------------------------------------------------------------
//新测试
    //m_compList为仿真控制类从mainwindow.tabwidget的com_list中拷贝的componentList对象
    //m_rulemanage为仿真控制类从mainwindow中传入的RuleManager

        QVector<Component*> l_vComponent=m_compList->getComponentList();
        int l_length=l_vComponent.size();

        for(int i = 0;i<l_length;i++)
        {
            //输出组件id
            qDebug()<<l_vComponent[i]->getID();
            //输出库所和token值
            QList<PLACE_ATTR>l_placeAttrList=l_vComponent[i]->getPlace_ATTRList();
            for(int i=0;i<l_placeAttrList.size();i++)
            {
                qDebug()<<l_placeAttrList[i].id<<" : "<<l_placeAttrList[i].initmark;
            }
        }


    //测试m_compList的addNewComponent
        //addNewComponent有问题
    qDebug()<<"add "<<m_compList->addNewComponent(QString("C3"));
    //再次输出组件信息
    l_vComponent=m_compList->getComponentList();
    l_length=l_vComponent.size();
    for(int i = 0;i<l_length;i++)
    {
        //输出组件id
        qDebug()<<l_vComponent[i]->getID();
        //输出库所和token值
        QList<PLACE_ATTR>l_placeAttrList=l_vComponent[i]->getPlace_ATTRList();
        for(int i=0;i<l_placeAttrList.size();i++)
        {
            qDebug()<<l_placeAttrList[i].id<<" : "<<l_placeAttrList[i].initmark;
        }
    }

    //初始化规则管理器
    m_ruleManager.initRule(m_compList);
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
void SimulationController::tarjan(int u)
{
    s_DFN[u]=s_low[u]=s_counts++;
    s_stack[++s_top]=u;
    s_flag[u]=1;

    for(int v=0;v<s_length;v++)
    {
        if(s_matrix[u][v])
        {
            if(!s_DFN[v])
            {
                tarjan(v);
                if(s_low[v]<s_low[u])
                    s_low[u]=s_low[v];
            }
            else{
                if(s_DFN[v]<s_low[u]&&s_flag[v])
                    s_low[u]=s_DFN[v];
            }
        }
    }

    if(s_DFN[u]==s_low[u])
    {
        s_number++;
        do{
            s_j=s_stack[s_top--];
            s_priorList.push_back(s_j);
//            qDebug()<<j;
            s_flag[s_j]=0;
        }while(s_j!=u);
    }
}
bool SimulationController::sort()
{
    QList<CONNECTOR_ATTR> l_ConnectorAttrList=m_compList->getConnectorAttrList();
    QVector<Component*> l_vComponent=m_compList->getComponentList();
    QMap<QString,int>l_mCompId2Order;
    s_length=l_vComponent.size();
    if(s_length>COMP_NUM_MAX)
    {
        qDebug()<<"warning : the number of component is out of range !";
        return false;
    }
    //数组初始化
    memset(s_DFN,0,sizeof (s_DFN));
    memset(s_low,0,sizeof (s_low));
    memset(s_flag,0,sizeof (s_flag));
    s_priorList.clear();
    for(int i =0;i<s_length;i++)
    {
        for(int j =0;j<s_length;j++)
            s_matrix[i][j]=0;
    }
    //用数字标记数组
    for(int i=0;i<s_length;i++)
    {
        l_mCompId2Order[l_vComponent[i]->getID()]=i;
    }
    QString source,target;
    //将有向图转化为矩阵
    for(int i=0;i<l_ConnectorAttrList.size();i++)
    {
        source=findCompId(l_ConnectorAttrList[i].source);
        target=findCompId(l_ConnectorAttrList[i].target);
        if(!l_mCompId2Order.contains(source))
        {
            qDebug()<<l_ConnectorAttrList[i].id<<" has invalid source"<<l_ConnectorAttrList[i].source;
        }
        if(!l_mCompId2Order.contains(target))
        {
            qDebug()<<l_ConnectorAttrList[i].id<<" has invalid source"<<l_ConnectorAttrList[i].target;
        }
        qDebug()<<"the "<<i<<" connector is from "<<source<<" to "<<target;
        s_matrix[l_mCompId2Order[source]][l_mCompId2Order[target]]=1;
    }
    //tarjan算法排序(！！！注意：targan一遍可能不能搜完所有点，因为可能存在孤立点或者其它)
    for(int i = 0;i < s_length;i++)
    {
        if(!s_DFN[i])
        {
            tarjan(i);
        }
    }
    for(int i = 0; i<s_priorList.size();i++)
    {
        qDebug()<<l_vComponent[s_priorList[i]]->getID()<<" 's priority is "<<i;
    }
    return true;
}
void SimulationController::initCompGraph(Component* component,double start)
{
    QList<PLACE_ATTR>l_placeList=component->getPlace_ATTRList();
    QString l_compName=component->getID().split("&")[0]+"&"+component->getID().split("&")[1];
    QString l_graphName;
    for(int i =0;i<l_placeList.size();i++)
    {
        s_mPlaceId2GraphIndex[l_placeList[i].id]=s_graphIndex;
        l_graphName="("+l_compName+")"+l_placeList[i].name;
        emit addgraph(l_graphName.toStdString());
        QVector <double>l_tempX;
        QVector <double> l_tempY;
        l_tempX.push_back(start);
        l_tempY.push_back(l_placeList[i].initmark);
        emit adddata(s_graphIndex,l_tempX,l_tempY);
        qDebug()<<component->getID()<<"init data : ("<<start<<" ,"<<l_placeList[i].initmark<<")";
        s_graphIndex++;
    }
}

bool SimulationController::drawCompData(Component*component,double time)
{
    QString l_compID=component->getID();
    QList<PLACE_ATTR>l_placeList=component->getPlace_ATTRList();
    int l_index;
    for(int i=0;i<l_placeList.size();i++)
    {
        if(s_mPlaceId2GraphIndex.contains(l_placeList[i].id))
            l_index =s_mPlaceId2GraphIndex.value(l_placeList[i].id);
        else break;
        QVector <double>l_tempX;
        QVector <double> l_tempY;
        l_tempX.push_back(time);
        l_tempY.push_back(l_placeList[i].initmark);
        emit adddata(l_index,l_tempX,l_tempY);
//      qDebug()<<l_placeList[i].name<<" adddata("<<l_index<<","<<time<<","<<l_placeList[i].initmark<<")";
        s_placeId2Value[l_placeList[i].id]=l_placeList[i].initmark;
        }
    return true;
}

void SimulationController::connectData(Component *component,double time)
{
    //如果没有connector
      if(m_disjSets->isEmpty())
      {
          qDebug()<<"m_disjSets is empty";
          return;
      }
      QList<QString>l_placeIDList=m_disjSets->getPlaceIDInDisjSets();
      QVector<Component*>l_vComponent=m_compList->getComponentList();
      QString l_compID=component->getID();
      int l_length=l_placeIDList.size();
//      int l_visit[l_length];
//      memset(l_visit,0,sizeof(l_visit));
      QString l_placeID_1,l_placeID_2;
      //遍历不相交集合里的库所id
      for(int i=0;i<l_length;i++)
      {
          //目前没有考虑组件内端口自连的情况

          l_placeID_1=l_placeIDList[i];
          //如果connector的某个库所属于该组件
          if(l_placeID_1.contains(l_compID,Qt::CaseSensitive))
          {
              double updateData=component->getCertainPlaceToken(l_placeID_1);
              int l_set=m_disjSets->find(l_placeID_1);
              for(int j=0;j<l_length;j++)
              {
                  if(j==i)
                      continue;
                  l_placeID_2=l_placeIDList[j];
                  if(l_set==m_disjSets->find(l_placeID_2))
                  {
                      QString l_compID=l_placeID_2.split("&")[0]+"&"+l_placeIDList[j].split("&")[1];
                      l_vComponent[s_comId2ListIndex[l_compID]]->changeTokens(l_placeID_2,updateData);
                      //在曲线上增加同步数据
                      QVector <double>l_tempX;
                      QVector <double> l_tempY;
                      l_tempX.push_back(time);
                      l_tempY.push_back(updateData);
                      emit adddata(s_mPlaceId2GraphIndex[l_placeID_2],l_tempX,l_tempY);
                  }
              }
          }
      }
}

//void SimulationController::findConnectedPlace(QString compID)
//{
//    //采用的算法性能不高
//    QList<CONNECTOR_ATTR>connectorAttrList=m_compList->getConnectorAttrList();
//    for(int i=0;i<connectorAttrList.size();i++)
//    {

//    }
//}

static QVector<QString>s_vConnectorID;
void SimulationController::initConnect()
{
    QList<CONNECTOR_ATTR>l_connectorAttrList=m_compList->getConnectorAttrList();
    QVector<Component*>l_vComponent=m_compList->getComponentList();
    for(int i =0;i<l_connectorAttrList.size();i++)
    {
        s_vConnectorID.push_back(l_connectorAttrList[i].id);
        QString l_source=l_connectorAttrList[i].source;
        QString l_target=l_connectorAttrList[i].target;
        QString l_targetCompID=l_target.split("&")[0]+"&"+l_target.split("&")[1];
        if(s_placeId2Value.contains(l_source)&&s_comId2ListIndex.contains(l_targetCompID))
        {
            double l_value=s_placeId2Value[l_source];
            l_vComponent[s_mPlaceId2GraphIndex[l_targetCompID]]->changeTokens(l_target,l_value);
        }

    }
    //将连接件的库所分进不相交集中
    m_disjSets=new DisjSets(l_connectorAttrList);
}

void SimulationController::updateConnect()
{
    QList<CONNECTOR_ATTR>l_connectorAttrList=m_compList->getConnectorAttrList();
    QVector<Component*>l_vComponent=m_compList->getComponentList();
    for(int i =0;i<l_connectorAttrList.size();i++)
    {
        if(!s_vConnectorID.contains(l_connectorAttrList[i].id))
        {
            s_vConnectorID.push_back(l_connectorAttrList[i].id);
            QString l_source=l_connectorAttrList[i].source;
            QString l_target=l_connectorAttrList[i].target;
            QString l_targetCompID=l_target.split("&")[0]+"&"+l_target.split("&")[1];
            //前提保证：结构发生改变时数据需要保存在s_placeId2Value
            if(s_placeId2Value.contains(l_source)&&s_comId2ListIndex.contains(l_targetCompID))
            {
                double l_value=s_placeId2Value[l_source];
                l_vComponent[s_mPlaceId2GraphIndex[l_targetCompID]]->changeTokens(l_target,l_value);
            }
        }
    }
    //重新将连接件的库所分进不相交集中
    if(m_disjSets!=nullptr)
    {
        DisjSets*l_pDisjSets=m_disjSets;
        delete l_pDisjSets;
        m_disjSets=new DisjSets(l_connectorAttrList);
    }
}
