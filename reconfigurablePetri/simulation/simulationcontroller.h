#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H
#include <QThread>
#include "plot.h"
#include"event.h"
#include"mineventheap.h"
#include"rulemanager.h"
#include"disjsets.h"
class SimulationController: public QThread
{
    Q_OBJECT

public:
    /**
     * @brief SimulationController 构造函数
     * @param m_gui
     * @param start
     * @param end
     * @param step
     */
    SimulationController(ComponentList*,RuleManager&, Plot *m_gui,double start,double end,double step);
    /**
     * @brief run 重写虚函数，在线程内进行仿真操作
     * 主要行为包括：组件优先级排序，构造最小事件堆，仿真计算与调度，数据可视化
     */
    void  run();
    /**
     * @brief sort 对组件进行优先级排序，主要使用Trajan算法和拓扑排序
     * @return bool true为没有代数环
     */
    bool sort();
    /**
     * @brief tarjan 使用tarjan方法求解组件拓扑图中的强连通分量
     */
    void tarjan(int);
    /**
     * @brief drawCompData 将组件的数据发送到ui上
     * @param Component* component组件
     * @param double time 对应的时间戳
     */
    bool drawCompData(Component*,double);
    /**
     * @brief initCompGraph 初始化组件的曲线：生成曲线和初始点
     * @param component
     * @param double
     */
    void initCompGraph(Component*,double);
    /**
     * @brief connectData 实现一个组件相关的connector数据交流
     * @param component组件
     * @param 时间戳
     */
    void connectData(Component*,double);
    /**
     * @brief initConnectData 连接瞬间使得connector两端的库所同步token信息
     * 要求将被连接上的库所的token值为0；不为0则被覆盖
     */
    void initConnect();
    /**
     * @brief updateConnect 网结构发生变化后，连接器可能发生变化
     */
    void updateConnect();
//    /**
//     * @brief findConnectedPlace
//     */
//    void findConnectedPlace(QString);

signals:
    /**
     * @brief updateui 更新仿真进度条
     * @param x        进度
     * @param y        仿真运行时间
     */
    void updateui(double,QString);
    /**
     * @brief addgraph 在图中增加一条曲线
     * @param string   曲线名字
     */
    void addgraph(string);
    /**
     * @brief adddata 在曲线上增加数据
     * @param i       曲线编号
     * @param t1      x坐标集合
     * @param t2      y坐标集合
     */
    void adddata(unsigned,QVector<double>,QVector<double>);
public slots:
    void slotUpdateUi(double,QString);
    /**
     * @brief slotAddGraph 在图中增加一条曲线
     * @param s            曲线名字
     */
    void slotAddGraph(string);
    /**
     * @brief slotAddData      向曲线增加数据
     * @param i                曲线编号
     * @param t1               x坐标集合
     * @param t2               y坐标集合
     */
    void slotAddData(unsigned,QVector<double>,QVector<double>);
private:
    /**主线程对象指针*/
    Plot *m_gui;
    /**组件管理*/
    ComponentList*m_compList;
    /**规则管理*/
    RuleManager m_ruleManager;
    /**不相交集*/
    DisjSets *m_disjSets;
    /**仿真开始时间*/
    double m_start;
    /**仿真结束时间*/
    double m_end;
    /**规则判断间隔*/
    double m_step;

};

#endif // SIMULATIONCONTROLLER_H
