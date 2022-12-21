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
            addTransMode=3,drawArcMode=4, addToken=5, subToken=6};

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
     QString name;
     QList <PLACE_ATTR> placeNodes;
     QList <TRANSITION_ATTR> transitionNodes;
     QList <ARC_ATTR> arcs;
   } PAGE_ATTR;

typedef struct{
     QString id;
     QString name;
     QList <PAGE_ATTR> pages;
   } PTNET_ATTR;

typedef struct{
    QString id;
    QString name;
    QString type;
    QList <PLACE_ATTR> placeNodes;
    QList <TRANSITION_ATTR> transitionNodes;
    QList <ARC_ATTR> arcs;
    QList<QString>in;//连入该组件的所有组件id
    QList<QString>out;//该组件连出的所有组件id
} COMPONENT_ATTR;

typedef struct{
    QString id;
    QString name;
    QList<COMPONENT_ATTR>component_net;
} COMPONENTNET_ATTR;


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

#endif
