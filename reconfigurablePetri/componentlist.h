#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H
//inuse
#include <QObject>
#include"ptnscene.h"
#include<component.h>
#include "componentcontroller.h"

class ComponentList : public QObject
{
    Q_OBJECT
public:
    explicit ComponentList(QObject *parent = nullptr);
    ComponentList(QVector<Component*>com_list,QVector<Component*>OriginComponent_List,PTNscene*Scene,componentController*comController);
    ComponentList();

    //如果未找到返回nullptr
    Component* getCertainComponent( QString ComID);

    //根据传入ID获取Place，包括普通端口，复合端口，普通节点
    Place* getCertainPlace(QString PlaceID);

    //获取指定组件的端口对象（仅返回普通端口）
    QList<Place*> getPortinComponent(QString ComponentID);

    //返回指定组件的Place与Transition的name（ID的第三部分)
    QList<QString> getCertainPlaceName(QString ComponentID);
    QList<QString>getCertainTransitionName(QString ComponentID);

    //!!!一定要在addNewComponent()函数中调用，返回已分配好ID的组件
    QString setnewComponentIDinSimulation(Component *newComponent);


    //todo 欣然
    void addComponentPort(QString portID1,QString portID2);
    void addNewComponent(Component*newCom  );//记得调用setnewComponentIDinSimulation

    //todo 田俊杰
    //注意new place时的细节
    void seperateCompoundPort(QString CompoundPortID);
    void deleteComponent(QString ComponentID);



private:
    QVector<Component*>com_list;
    QList<QString>garbage_comID;
    QVector<Component*>OriginComponent_List;//尚未赋值
    PTNscene*Scene;//尚未赋值
    componentController*comController;//尚未赋值
signals:

};

#endif // COMPONENTLIST_H
