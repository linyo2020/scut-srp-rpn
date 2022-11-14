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
   } PLACE_ATTR;

typedef struct{
     QString id, name;
     /* coordinate */
     int x, y;
     int rotation;
     /* label coordinate */
     int offsetx, offsety;
     QString self_function;
     //QString MassAction;
     QString comment;
     bool show;
     QColor brushColor;
     QColor penColor;
   } TRANSITION_ATTR;

typedef struct{
     QString id, source, target;
     double weight;
     QList<QPointF> points;
     QColor brushColor;
     QColor penColor;
   } ARC_ATTR;


typedef struct{
     QString id, name;
     QList <PLACE_ATTR> placeNodes;
     QList <TRANSITION_ATTR> transitionNodes;
     QList <ARC_ATTR> arcs;
   } PAGE_ATTR;

typedef struct{
     QString id, name;
     QList <PAGE_ATTR> pages;
   } PTNET_ATTR;

typedef struct{
    QString name;
    QMap<QString, QString> preSet;
    QMap<QString, QString> postSet;
  } TRANS_RELATION;

typedef struct{
    int red,green,blue;
} COLOR;

#endif
