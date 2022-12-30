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
    //端口的定义，只有入或者仅有出
    ComponentList();




    //根据传入ID获取Place，包括普通端口，复合端口，普通节点
    Place* getCertainPlace(QString PlaceID);

    //获取指定组件的端口对象（仅返回普通端口）
    QList<Place*> getPortinComponent(QString ComponentID);

    //返回指定组件的Place与Transition的name（ID的第三部分)
    QList<QString> getCertainPlaceName(QString ComponentID);
    QList<QString>getCertainTransitionName(QString ComponentID);


    //！
    void seperateCompoundPort(QString CompoundPortID);
    //！
    void deleteComponent(QString ComponentID);
    //！
    void recoverComponent(QString ComponentID);
    void addComponentPort(QString portID1,QString portID2);
    QString addNewComponent(QString Filename);



    void getComponent(componentController *comController){this->comController=comController;}
    void getPTNScene(PTNscene * scene){Scene=scene;}
    void intiCom_list(QVector<Component*>c_list){com_list=c_list;}
private:
    //func
    //如果未找到返回nullptr
    Component* getCertainComponent( QString ComID);
    //!!!一定要在addNewComponent()函数中调用，返回已分配好ID的组件
    QString setnewComponentIDinSimulation(Component *newComponent);
    Component* OriginComponent(QString Filename);
    void addNewComponent(Component*newCom);

    QVector<Component*>com_list;
    QMap<QString,PTNscene*>garbage;
    PTNscene*Scene;
    componentController*comController;


};

#endif // COMPONENTLIST_H
