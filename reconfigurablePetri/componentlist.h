#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H
//inuse
#include <QObject>
#include<component.h>

class ComponentList : public QObject
{
    Q_OBJECT
public:
    explicit ComponentList(QObject *parent = nullptr);
    ComponentList(QVector<Component*>com_list);


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
    QVector<Component*>garbage;
signals:

};

#endif // COMPONENTLIST_H
