#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H
//inuse
#include <QObject>
#include"ptnscene.h"
#include<component.h>
#include "componentcontroller.h"
#include"connector.h"
class ComponentList : public QObject
{
    Q_OBJECT
public:
    //端口的定义，只有入或者仅有出
    ComponentList();
    //setID以及初始话 田俊杰





    //获取指定组件的端口对象（仅返回普通端口）
    QList<Place*> getPortinComponent(QString ComponentID);//完成

    //返回指定组件的Place与Transition的name（ID的第三部分)
    QList<QString> getCertainPlaceName(QString ComponentID);//田俊杰
    QList<QString>getCertainTransitionName(QString ComponentID);//完成


    //！
    //void seperateCompoundPort(QString CompoundPortID);

    //遍历找到连接的connector，删除这个connector（从list里弹出）
    void deleteConnect(QString PlaceID1,QString PlaceID2);//田俊杰


    //！
    //从com_list里弹出,放到垃圾桶
    void deleteComponent(QString ComponentID);//完成
    //！
    //从垃圾桶里添加会com_list
    void recoverComponent(QString ComponentID);//田俊杰
    //给connector的sourceID、targetID赋值
    void addComponentPort(QString portID1,QString portID2);//完成
    //遍历文件树，添加到com_list里，记得设置id
    QString addNewComponent(QString Filename);//田俊杰

    const QList<Connector*> getConnectorList();
    void push_back_connectorList(Connector*c);


    //lwy:set函数是设置属性，get函数是返回属性，以下函数应该是set函数才对吧？
    void getComponent(componentController *comController){this->comController=comController;}
    void getPTNScene(PTNscene * scene){Scene=scene;}
    void intiCom_list(QVector<Component*>c_list){com_list=c_list;}
    void initConnector_list(QList<Connector*>l){connectList=l;};
private:
    //func
    //如果未找到返回nullptr
    //Component* getCertainComponent( QString ComID);
    Component* OriginComponent(QString Filename);//欣然


    void deleteArc(QString placeId,QString transitionID);
    //!!!一定要在addNewComponent()函数中调用，返回已分配好ID的组件
    void setnewComponentIDinSimulation(Component *newComponent);
    QList<Connector*> connectList;
    QVector<Component*>com_list;//存储的每一个组件信息，里面存放attr
    componentController*comController;//要
    QVector<Component*>garbage2;



    //没用
    //----------------------------------
    //void addNewComponent(Component*newCom);
    Transition*getcertainTransition(QString tranID);
    //根据传入ID获取Place，包括普通端口，复合端口，普通节点
    //Place* getCertainPlace(QString PlaceID);//田俊杰



    //没用了
    //-----------------------------
    QMap<QString,PTNscene*>garbage;//要
    PTNscene*Scene;//要



};

#endif // COMPONENTLIST_H
