#ifndef CompoundComponent_H
#define CompoundComponent_H
//已废弃
#include <QObject>
#include"component.h"
#include"QList"
//存储包含在该复合组件中的组件列表
class CompoundComponent: public QObject
{
public:
    CompoundComponent();


    //返回当前复合组内所有组件id——list
    QStringList getAllComponentID();

    void updataID();

    //删除复合组内指定组件,成功删除返回true
    bool deleteCertainComponent(QString ComponentID);

    QString getCompoundComponentID();
    void setCompoundComponentID(QString id);

    Component* getCertainComponet(QString ComponentID);

    //将指定组件添加进该复合组中,返回添加之后的复合组ID
    QString push_back_Component(Component*com);

    //根据传入ID获取Place，包括普通端口，复合端口，普通节点
    Place* getCertainPlace(QString PlaceID);

    //将端口ID进行拆分
    QStringList seperatePortID(QString CompoundPort);


    bool isEmpty();

    QList<Component*> getComponent_list();




private:
    //复合组件的复合id,组件用+连接
    QString CompoundComponentID;

    //原计划采取QVector，这里做出了调整
    QList<Component*>component_list;

};

#endif // CompoundComponent_H
