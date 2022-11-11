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

    Arc(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
        QString TargetId, QPainterPath arc_path, const QString &ArcId,int ArcWeight);

    Arc(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
        QString TargetId, const QString &ArcId,int ArcWeight);//计算用，不能用于画图


    Arc(QGraphicsItem * item1, QGraphicsItem * item2,
        QPainterPath paintpath, const ARC_ATTR &arc);

    ~Arc();

    void createArc();
    ARC_ATTR toXml() const;

    void updatePosition();
    void showRects(bool show);

    QString getId();

    int getWeight() const;
    void setWeight(int Weight);

    void setLabel();

    QColor getBrushColor() const;
    QColor getPenColor() const;
    void setBrushColor(QColor color);
    void setPenColor(QColor color);

    QGraphicsItem * getSourceItem() const;
    QGraphicsItem * getTargetItem() const;

    int type () const;
    QPainterPath shape() const;
    QRectF boundingRect() const;

    //void updateradius(int);

 protected:

    void paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option,
    QWidget * widget );

 private:

    QString id;
    QString source_id;
    QString target_id;
    int weight;

    QPolygonF ArcHead;
    QGraphicsSimpleTextItem* label;

    QList<ArcEdgeSelectionRectangle *> rects;

    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;


    QPointF intersectionWithPlace(QGraphicsItem * circle, QLineF * line) const;
    QPointF intersectionWithTransition(QGraphicsItem * rectangle, QLineF * line) const;

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
//  void createRuleSet();
};

#endif // ARC_H
