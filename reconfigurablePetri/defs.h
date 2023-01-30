#ifndef DEFS_H
#define DEFS_H

#include <QList>
#include <QPointF>
#include <QMap>
#include <QColor>
//#include "FIS/pn_defines.h"

#define omega 9999999
#define place_diameter 30
#define transition_width 30
#define transition_heigh 29

typedef QMap<QString, double> Marking;

enum{normalMode=0, animationMode=1, addPlaceMode=2, \
            addTransMode=3,drawArcMode=4, drawConnectorMode=5,addToken=6, subToken=7};

typedef struct{
     QString id, name;/*可导入导出*/
     /* coordinates */
     int x, y;/*可导入导出*/
     double initmark;/*可导入导出*/
     double capacity;/*可导入导出*/
     /* label offset */
     int offsetx, offsety;/*可导入导出*/
     /* new addition */
      QString comment;/*可导入导出*/
      bool show;/*可导入导出*/
      QColor brushColor;/*可导入导出*/
      QColor penColor;/*可导入导出*/
      QString component_id;//[new]属于哪个组件/*可导入导出*/
   } PLACE_ATTR;

typedef struct{
     QString id, name;/*可导入导出*/
     /* coordinate */
     int x;/*可导入导出*/
     int y;/*可导入导出*/
     int rotation;/*可导入导出*/
     /* label coordinate */
     int offsetx;/*可导入导出*/
     int offsety;/*可导入导出*/
     QString self_function;/*可导入导出*/
     //QString MassAction;
     QString comment;/*可导入导出*/
     bool show;/*可导入导出*/
     QColor brushColor;/*可导入导出*/
     QColor penColor;/*可导入导出*/
   } TRANSITION_ATTR;

typedef struct{
     QString id;/*可导入导出*/
     QString source;/*可导入导出*/
     QString target;/*可导入导出*/
     double weight;/*可导入导出*/

     QList<QPointF> points;/*可导入导出*/
     QColor brushColor;/*可导入导出*/
     QColor penColor;/*可导入导出*/

   } ARC_ATTR;
typedef struct{
    QString id;/*可导入导出*/
    QString source;/*可导入导出*/
    QString target;/*可导入导出*/

    QList<QPointF> points;/*可导入导出*/
} CONNECTOR_ATTR;


typedef struct{
    QString id;
    QString name;
    QString type;
    double step;//仿真步长
    QList <PLACE_ATTR> placeNodes;
    QList <TRANSITION_ATTR> transitionNodes;
    QList <ARC_ATTR> arcs;

} COMPONENT_ATTR;


typedef struct{
     QString id;/*可导入导出*/
     QString name;/*可导入导出*/
     QList <PLACE_ATTR> placeNodes;
     QList <TRANSITION_ATTR> transitionNodes;
     QList <ARC_ATTR> arcs;
     QList <CONNECTOR_ATTR> connector;
     QList <COMPONENT_ATTR> componentList;
   } PAGE_ATTR;

typedef struct{
     QString id;/*可导入导出*/
     QString name;/*可导入导出*/
     QList <PAGE_ATTR> pages;
   } PTNET_ATTR;




typedef struct{
    QString name;
    QMap<QString, QString> preSet;
    QMap<QString, QString> postSet;
  } TRANS_RELATION;

typedef struct{   
    int red;
    int green;
    int blue;
} COLOR;

//[规则库相关定义]
//比较的符号
enum ComparisonSymbol{EQUAL=1,NOT_EQUAL,GREATER,LESS,GREATER_EQUAL,LESS_EQUAL};

//比较的类型，每种规则只处理对应的类型，如时间规则只处理时间规则相关类型
enum ComparisionType{
    /*时间规则相关类型*/
    TIME_POINT_COMPARE=1,//当前总仿真时间和某个时间点比较。比较类型为此项时，监控因素将忽略，可填空字符串。比较形式如下：<当前时间点><比较符号><被比较的数值>
    FIRE_REACH_TIME_DURATION=2,//持续触发达到某个时长   **！次要需求，暂无实现！**
    CERTAIN_TOKEN_DURATION,//对token的比较满足，并维持一定的时间。前部CONDITION为token比较，后部为时间比较（监控因素将忽略），即：token比较→时间比较
    TIME_TO_REACH_CERTAIN_TOKEN,//令token满足比较,所需的时间。token比较→时间比较（后部的监控因素将忽略）

    /*事件规则相关类型*/

    /*状态规则相关类型*/
    TOKEN_COMPARE//比较token是否符合范围
};
//<监控的因素（token等)><比较符号（大于/小于等）><要比较的数值>
#pragma pack(push)
#pragma pack(1)
typedef struct _CONDITION
{
    ComparisionType conditionOption;//比较的类型，如库所token的比较，仿真总时间的比较
    QString monitorFactor;//监控的因素
    ComparisonSymbol symbol;//比较的符号
    QVariant value;//被比较的数值
    _CONDITION* rearPart;//蕴含式的后半部，即离散数学中的“→”，拥有此指针的结构体为前半部，用于“位置的token值在一个数值范围的维持时间”这种前一个条件满足后才监测后一个因素的规则类型

    _CONDITION(ComparisionType option,QString factor,ComparisonSymbol symbol,QVariant value)
        :conditionOption(option),monitorFactor(factor),symbol(symbol),value(value),rearPart(nullptr)
    {}
    _CONDITION(ComparisionType option,QString factor,ComparisonSymbol symbol,QVariant value,_CONDITION* rp)
        :conditionOption(option),monitorFactor(factor),symbol(symbol),value(value),rearPart(rp)
    {}
    _CONDITION(const _CONDITION& other)
    {
        conditionOption=other.conditionOption;
        monitorFactor=other.monitorFactor;
        symbol=other.symbol;
        value=other.value;
        rearPart=(nullptr==other.rearPart)?
                    nullptr:
                    new _CONDITION(other.rearPart->conditionOption,other.rearPart->monitorFactor,other.rearPart->symbol,other.rearPart->value);
    }
    _CONDITION &operator=(const _CONDITION& other)
    {
        conditionOption=other.conditionOption;
        monitorFactor=other.monitorFactor;
        symbol=other.symbol;
        value=other.value;
        rearPart=(nullptr==other.rearPart)?
                    nullptr:
                    new _CONDITION(other.rearPart->conditionOption,other.rearPart->monitorFactor,other.rearPart->symbol,other.rearPart->value);
        return *this;
    }

    _CONDITION(_CONDITION&& other)
    {
        conditionOption=other.conditionOption;
        monitorFactor=other.monitorFactor;
        symbol=other.symbol;
        value=other.value;
        rearPart=other.rearPart;
        other.rearPart=nullptr;
    }
    _CONDITION &operator=(_CONDITION&& other)
    {
        conditionOption=other.conditionOption;
        monitorFactor=other.monitorFactor;
        symbol=other.symbol;
        value=other.value;
        rearPart=other.rearPart;
        other.rearPart=nullptr;
        return *this;
    }

    ~_CONDITION()
    {
        if(rearPart!=nullptr)
            delete rearPart;
    }
} CONDITION,* pCONDITION;
#pragma pack(pop)

//仿真前，提供给规则的仿真信息
typedef struct
{
    double totalTime;//总仿真时间、仿真全局时钟
}RULE_RUNTIME_INFOMATION;

//[/规则库相关定义]

#endif
