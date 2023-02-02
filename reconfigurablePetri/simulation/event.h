#ifndef EVENT_H
#define EVENT_H
#include"component.h"

#define MAX_PRIOR 0

class Event
{
public:
    /**
     * @brief Event 构造仿真执行类型的事件
     * @param component
     * @param time
     * @param prior
     */
    Event(Component*component,double time,int prior);
    /**
     * @brief Event 构造规则类型的事件
     * @param step
     * @param time
     */
    Event(double step,double time);
    /**
     * @brief setTime
     * @param time
     */
    void setTime(double time);
    /**
     * @brief update 更新下一次事件进行完成的时间戳
     */
    void update();
    /**
     * @brief setPrior
     * @param prior
     */
    void setPrior(int prior);
    /**
     * @brief showCompId
     * @return 注意：规则类型的事件返回QString("rule")
     */
    QString showCompId();
    /**
     * @brief getPrior
     * @return
     */
    int getPrior();
    /**
     * @brief getTime
     * @return
     */
    double getTime();
    /**
     * @brief occur 进行事件：运行一次组件的仿真或规则判断
     * @return 规则类型事件返回是否触发规则运行规则；仿真执行类型事件返回仿真是否成功
     */
    bool occur();
    /**
     * @brief getStep
     * @return
     */
    double getStep();
    /**
     * @brief getComponent
     * @return
     */
    Component*getComponent();
private:
    enum type{rule,execution};   /**事件类型:规则类型和仿真执行类型*/
    int m_prior;                 /**事件优先级：规则类型的优先级最高，数值为0；数值越小，优先级越高*/
    type m_type;
    double m_time;               /**完成该事件时的时间戳*/
    double m_step;               /**该事件的步长*/
    /**仿真执行类型对应的组件，由于规则类型事件较少，因此规则类型事件类中此变量的空间浪费能够接受*/
    Component*m_component;

};

#endif // EVENT_H
