#ifndef COMPONENT_H
#define COMPONENT_H
//have Todo tag
#include <QObject>
//this class defines a base unit of component library
#include"defs.h"
#include"ptnet.h"
#include"ptnscene.h"
#include"QDateTime"
class Component: public QObject
{
public:
    //特别注意,组件类创建的时机以及方式.
    Component();
    Component(const PTNET_ATTR& PTnet,PTNscene*scene);//对应着读取xml文件时的构造函数
    Component(QString type,QString label);//对应着用户在ui上创建控件时的构造函数,一开始无法直接将数据导入到PTNet类中
    Component(QString PTnet_ID,PTNscene*scene);
    //The unique identity of the component unit

    QString Component_id;//该数据的获取方式:type+唯一编号\系统读取控件xml文件时读取

    //The name displayed on the UI
    QString label;//该数据获取方式:用户在新建控件时输入\系统读取控件xml文件时读取

    //返回该组件中所有place
    QList<Place*> getPlaceList();
    //返回TransitionList
    QList<Transition*>getTransitionList();
    //返回ArcList
    QList<Arc*>getTArcList();
    //废弃属性
    QString Component_type;

    QString getComponentFileName();

    Place*getCertainPlaceByName(QString p0);

    //只获取普通端口，不获取复合端口
    QList<Place*>getNormalPort();

    QList<Place*>getCompoundPort();

    PTNet *mynet;
    bool net_att_isEdited;//useless

    QString getComponent_type() const;
    //QString getComponent_id();
    QString getLabel() const;
    void setID(QString id);
    QString getID();
    void setComponent_type(QString type);//slots//UI
    void setLabel(const QString &value);//slots//UI
    //variable :net need to connect,source ,target

    Place* getCertainPlace(QString PlaceID);





};

#endif // COMPONENT_H
