#ifndef COMPONENT_H
#define COMPONENT_H
//have Todo tag
#include <QObject>
//this class defines a base unit of component library
#include"defs.h"
#include"ptnet.h"
#include"ptnscene.h"
#include"QDateTime"
  #include <QtGlobal>
#include"ODESolver/ODEsolver.h"
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

    //不要
    //------------------------
    //返回该组件中所有place
    QList<Place*> getPlaceList();
    //返回TransitionList
    QList<Transition*>getTransitionList();
    //返回ArcList
    QList<Arcus*>getTArcList();
    //-----------------------------


    //废弃属性
    QString Component_type;

    QString getComponentFileName();

    Place*getCertainPlaceByName(QString p0);

    //只获取普通端口，不获取复合端口
    QList<Place*>getNormalPort();

    QList<Place*>getCompoundPort();
    //！！！不要删除，会报错！！！
    PTNet *mynet;
    bool net_att_isEdited;//useless

    QString getComponent_type() const;
    //QString getComponent_id();
    QString getLabel() const;
    void setID(QString comID,int i);
    void setID(QString id);
    QString getID();
    void setComponent_type(QString type);//slots//UI
    void setLabel(const QString &value);//slots//UI
    QString getFileName();
    //variable :net need to connect,source ,target

    Place* getCertainPlace(QString PlaceID);

    //返回特定place的token值
    double getCertainPlaceToken(QString PlaceID);

    QList<PLACE_ATTR>getPlace_ATTRList();
    QList<TRANSITION_ATTR>getTransition_ATTRList();
    QList<ARC_ATTR>getArc_ATTRList();

    void setPlace_ATTRList( QList<PLACE_ATTR>);
    void setTransition_ATTRList(QList<TRANSITION_ATTR>);
    void setArc_ATTRList(QList<ARC_ATTR>);

    /**
        * @brief changeTokens 修改组件的库所的token值
        * @author lwy
        * @param placeID
        * @param tokens
        * @return
        */
       bool changeTokens(QString placeID,double tokens);
    /**
     * @brief setStep 设置仿真步长
     * @author lwy
     */
    void setStep(double);
    /**
     * @brief getStep 读取仿真步长
     * @author lwy
     * @return
     */
    double getStep();
    /**
     * @brief makeFunction 读取组件结构，生成速率方程
     * @author lwy
     * @return
     */
    void makeFunction();
    /**
     * @brief tick 组件单步仿真
     * @author lwy
     * @param l_start 仿真开始的时间戳
     * @param state 是否检查负值
     */
    bool tick(double,bool);

    void transform();
private:
    /**
     * @brief m_step 仿真步长
     * @author lwy
     */
    double m_step;
    /**
     * @brief m_mInputVaraible2Value 库所变量-token值的映射
     * @author lwy
     */
    map<string,double> m_mInputVaraible2Value;
    /**
     * @brief m_vFunDef 速率方程
     * @author lwy
     */
    vector<FUNCTIONDEF> m_vFunDef;

    QList<PLACE_ATTR> placeList;
    QList<TRANSITION_ATTR> transitionList;
    QList<ARC_ATTR> arcList;


};

#endif // COMPONENT_H
