#ifndef COMPOUNDCOMPONENTLIST_H
#define COMPOUNDCOMPONENTLIST_H

#include <QObject>
#include"compoundcomponent.h"
class CompoundComponentList : public QObject
{
    Q_OBJECT
public:
    explicit CompoundComponentList(QObject *parent = nullptr);
    CompoundComponentList(QVector<Component*>com_arry);

    //如果未找到返回空值
    CompoundComponent* getCertainCompoundComponent( QString ID);

    //针对现有框架设置的参数，该参数在tabwidget中有写过
    void initial(QVector<Component*>com_arry);

    void updataAllID();

    //得到该复合组件
    QList<Component*> parseCompoundComponentID(QString CompoundComponentID);

    //根据传入ID获取Place，包括普通端口，复合端口，普通节点
    Place* getCertainPlace(QString PlaceID);



    //获取指定组件的端口对象（仅返回普通端口）
    QList<Place*> getPortinComponent(QString ComponentID);
    QList<Place*> getPortinComponent(Component*com);






    //todo 欣然
    void addComponentPort(QString portID1,QString portID2);

    //todo 田俊杰
    void seperateCompoundPort(QString CompoundPortID);


private:
    QList<CompoundComponent*>CompoundComponent_List;
    QVector<Component*>old;//在仿真前保存的所有组件信息
signals:

};

#endif // COMPOUNDCOMPONENTLIST_H
