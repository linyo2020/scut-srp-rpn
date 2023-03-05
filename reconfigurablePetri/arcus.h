#ifndef ARCUS_H
#define ARCUS_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>

#include "arcedgeselectionrectangle.h"

#include "defs.h"

//#include "FIS/pn_defines.h"

class Arcus : public QGraphicsPathItem
{
 public:

    enum { Type = UserType + 3 };

    Arcus(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
        QString TargetId, QPainterPath arc_path, const QString &ArcId,double ArcWeight);

    Arcus(QGraphicsItem * SourceItem, QString SourceId,QGraphicsItem * TargetItem,
        QString TargetId, const QString &ArcId,double ArcWeight);//计算用，不能用于画图


    Arcus(QGraphicsItem * item1, QGraphicsItem * item2,
        QPainterPath paintpath, const ARC_ATTR &arc);
    Arcus(QGraphicsItem * item1, QGraphicsItem * item2,
        QPainterPath paintpath, const ARC_ATTR &arc,int count);

    Arcus();

    ~Arcus();

    void createArc();
    ARC_ATTR toXml() const;

    void updatePosition();
    void showRects(bool show);

    QString getId();
    void setID(QString id);
    void setsourceId(QString id);
    void setTargetId(QString id);
    QString getSourceId();
    QString getTargetId();
    double getWeight() const;
    void setWeight(double Weight);

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

    bool isInComponent();
    void setIncomponent(bool isInComponent);

    void setSourceItem(QGraphicsItem*it);
    void setTargetItem(QGraphicsItem*it);

    //void updateradius(int);

 protected:

    void paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option,
    QWidget * widget );

 private:

    QString id;
    QString source_id;
    QString target_id;
    double weight;

    QPolygonF ArcHead;
    QGraphicsSimpleTextItem* label;

    QList<ArcEdgeSelectionRectangle *> rects;

    QGraphicsItem * sourceItem;
    QGraphicsItem * targetItem;


    QPointF intersectionWithPlace(QGraphicsItem * circle, QLineF * line) const;
    QPointF intersectionWithTransition(QGraphicsItem * rectangle, QLineF * line) const;

    QColor color;

    bool InComponent=false;

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

#endif // ARCUS_H
