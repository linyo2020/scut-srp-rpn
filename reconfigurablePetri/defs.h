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
     QString id, name;
     /* coordinates */
     int x, y;
     double initmark;
     double capacity;
     /* label offset */
     int offsetx, offsety;
     /* new addition */
      QString comment;
      bool show;
      QColor brushColor;
      QColor penColor;
      QString componet_id;//[new]属于哪个组件
   } PLACE_ATTR;

typedef struct{
     QString id, name;
     /* coordinate */
     int x;
     int y;
     int rotation;
     /* label coordinate */
     int offsetx;
     int offsety;
     QString self_function;
     //QString MassAction;
     QString comment;
     bool show;
     QColor brushColor;
     QColor penColor;
   } TRANSITION_ATTR;

typedef struct{
     QString id;
     QString source;
     QString target;
     double weight;

     QList<QPointF> points;
     QColor brushColor;
     QColor penColor;

   } ARC_ATTR;
typedef struct{
    QString id;
    QString source;
    QString target;

    QList<QPointF> points;
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
     QString id;
     QString name;
     QList <PLACE_ATTR> placeNodes;
     QList <TRANSITION_ATTR> transitionNodes;
     QList <ARC_ATTR> arcs;
     QList <CONNECTOR_ATTR> connector;
     QList <COMPONENT_ATTR> componentList;
   } PAGE_ATTR;

typedef struct{
     QString id;
     QString name;
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
enum ComparisonSymbol{EQUAL=1,NOT_EQUAL,GREATER,LESS,GREATER_EQUAL,LESS_EQUAL};
/*
 * 比较类型选项
 */
//时间相关条件
enum ComparisionType{
    /*时间规则相关类型*/
    REACH_TIME_POINT=1,//到达某个时间点
    FIRE_REACH_TIME_DURATION=2,//持续触发达到某个时长
    /*事件规则相关类型*/
    TOKEN_COMPARE//比较token是否符合范围
};
//<监控的因素（token等)><比较符号（大于/小于等）><要比较的数值>
typedef struct
{
    ComparisionType conditionOption;//比较的类型，如库所token的比较，时间的比较
    QString monitorFactor;//监控的因素
    ComparisonSymbol symbol;//比较的符号
    QVariant value;//比较的数值
} CONDITION,* pCONDITION;

//仿真前，提供给规则的仿真信息
typedef struct
{
    double step;//仿真步长
}RULE_INITIALIZE_INFOMATION;

//[/规则库相关定义]

#endif
