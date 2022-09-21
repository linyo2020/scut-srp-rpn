#ifndef ARC_H
#define ARC_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>

#include "arcedgeselectionrectangle.h"

#include "defs.h"

//#include "FIS/pn_defines.h"

class Arc : public QGraphicsPathItem
{
 public:

    enum { Type = UserType + 3 };

    Arc(QGraphicsItem * item1, QString id1,QGraphicsItem * item2,
        QString id2, QPainterPath arc_path, const QString &id,int w,QString expression="1");

//	Arc(QGraphicsItem * item1, QGraphicsItem * item2,
//		QPainterPath paintpath, const ARC_ATTR &arc);

    ~Arc();

    void createArc();
//	ARC_ATTR toXml() const;

    void updatePosition();
    void showRects(bool show);

    QString getId();
    int getWeight() const;
    void setWeight(int w);
    QString getExpression() const;
    void setExpression(QString e);

    void f_setExperssion(QString);
    QString f_getExperssion() const;

    void f_setLabel_1();
    void f_setLabel_2();

    QGraphicsItem * getSourceItem() const;
    QGraphicsItem * getTargetItem() const;

    int type () const;
    QPainterPath shape() const;
    QRectF boundingRect() const;

    //void updateradius(int);

    QColor getBrushColor() const;
    QColor getPenColor() const;
    void setBrushColor(QColor color);
    void setPenColor(QColor color);

 protected:

    void paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option,
    QWidget * widget );

 private:

    QString id;
    QString source_id;
    QString target_id;
    int weight;
    QString expression;

    QPolygonF ArcHead;
    QGraphicsSimpleTextItem * label;

    QList<ArcEdgeSelectionRectangle *> rects;

    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;

    QString m_experssion;

    QPointF intersectionPoint1(QGraphicsItem * circle, QLineF * line) const;
    QPointF intersectionPoint2(QGraphicsItem * rectangle, QLineF * line) const;

    QColor color;


//	FISStruct2 m_FIS;

//	RuleSet m_ruleSet;

    QColor m_brushColor = defalut_brushColor;
    QColor m_penColor = defalut_penColor;

    static const QColor defalut_brushColor;
    static const QColor defalut_penColor;

public:

//	FISStruct2* GetFISStruct()
//	{
//		return &m_FIS;
//	}
//	FISStruct2 getFISStruct()
//	{
//		return m_FIS;
//	}

//	RuleSet* GetRuleSet()
//	{
//		return &m_ruleSet;
//	}

//	RuleSet getRuleSet()
//	{
//		return m_ruleSet;
//	}
    void createRuleSet();
};

#endif // ARC_H
