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
    /**
     * @brief ComponentList 仿真前对信息进行拷贝
     * @author lwy
     */
    ComponentList(ComponentList*);

    //根据传入ID获取Place，包括普通端口，复合端口，普通节点
    Place* getCertainPlace(QString PlaceID);//田俊杰
    //返回库所token值
    double getCertainPlaceToken(QString PlaceID);
    //获取指定组件的端口对象（仅返回普通端口）
    QList<Place*> getPortinComponent(QString ComponentID);//完成

    //返回指定组件的Place与Transition的name（ID的第三部分)
    QList<QString> getCertainPlaceName(QString ComponentID);//田俊杰
    QList<QString>getCertainTransitionName(QString ComponentID);//完成


    //遍历找到连接的connector，删除这个connector（从list里弹出）
    void deleteConnect(QString PlaceID1,QString PlaceID2);//田俊杰

    //！
    //从com_list里弹出,放到垃圾桶
    void deleteComponent(QString ComponentID);//完成
    //！
    //从垃圾桶里添加会com_list
    void recoverComponent(QString ComponentID);//田俊杰

    //给connector的sourceID、targetID赋值
    //增加connector操作，sourceID为portID1
    void addComponentPort(QString portID1,QString portID2);//完成
    //遍历文件树，添加到com_list里，记得设置id
    QString addNewComponent(QString Filename);//田俊杰

    QVector<Component*> getComponentList();

    const QList<Connector*> getConnectorList();
    void push_back_connectorList(Connector*c);
    //修改组件步长
    void setComponentStep(QString ComponentID,double step);

    void getComponent(ComponentController *comController){this->comController=comController;}
    void getPTNScene(PTNscene * scene){Scene=scene;}
    void intiCom_list(QVector<Component*>c_list){com_list=c_list;}
    void initConnector_list(QList<Connector*>l){connectList=l;};
    /**
     * @brief getConnectorAttrList返回lconnector的属性结构体
     * @author lwy
     * @return
     */
    QList<CONNECTOR_ATTR> getConnectorAttrList();
    /**
     * @brief simulateStructChanged 模拟网结构变化（用于测试）：删除vector中最后一个组件以及相关连接
     * @author lwy
     * @return 变化是否成功
     */
    bool simulateStructChanged();
    /**
     * @brief show 打印组件信息和连接器信息
     */
    void show();
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
    ComponentController*comController;//要
    QVector<Component*>garbage2;



    //没用
    //----------------------------------
    //void addNewComponent(Component*newCom);
    Transition*getcertainTransition(QString tranID);


    //！废弃函数！！
    void seperateCompoundPort(QString CompoundPortID);

    //没用了
    //-----------------------------
    QMap<QString,PTNscene*>garbage;//要
    PTNscene*Scene;//要

    /**
     * @brief m_vConnector
     * @author lwy
     */
    QList<CONNECTOR_ATTR>m_lConnector;

};

#endif // COMPONENTLIST_H
