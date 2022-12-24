#ifndef COMPOUNDCOMPONENTLIST_H
#define COMPOUNDCOMPONENTLIST_H
//已废弃
#include <QObject>
#include"compoundcomponent.h"
class CompoundComponentList : public QObject
{
    Q_OBJECT
public:
    explicit CompoundComponentList(QObject *parent = nullptr);
    CompoundComponentList();

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

    //返回指定组件的Place与Transition的name（ID的第三部分)
    QList<QString> getCertainPlaceName(QString ComponentID);
    QList<QString>getCertainTransitionName(QString ComponentID);

    //!!!一定要在addNewComponent()函数中调用，返回已分配好ID的组件
    QString setnewComponentIDinSimulation(Component *newComponent);





    //todo 欣然
    void addComponentPort(QString portID1,QString portID2);
    void addNewComponent(Component*newCom  );

    //todo 田俊杰
    //注意new place时的细节
    void seperateCompoundPort(QString CompoundPortID);
    void deleteComponent(QString ComponentID);





private:
    QList<CompoundComponent*>CompoundComponent_List;
    QList<Component*>garbage;
signals:

};

#endif // COMPOUNDCOMPONENTLIST_H
