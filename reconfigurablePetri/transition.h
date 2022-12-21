#ifndef TRANSITION_H
#define TRANSITION_H
//new 田俊杰
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>
#include<QPainter>
#include"arc.h"
#include<QGraphicsScene>
#include<place.h>
#include"defs.h"
class Transition : public QGraphicsRectItem
{
 public:

    enum { Type = UserType + 2 };

    explicit Transition(const QString &id);
    Transition(const TRANSITION_ATTR &transition);
    //控件用到
    Transition(const QString &id,const QPointF &position);
    ~Transition ();

    void createTransition();
    TRANSITION_ATTR toXml() const;

    void showEditDialog ();
    void setAttributes ();

    QString getId () const;
    QString getName () const;
    void setName (const QString& nm);
    void setMode (int mod);
    void setID(QString ID);
    void addInputArc(QGraphicsItem * arc);
    void addOutputArc(QGraphicsItem * arc);
    void deleteArc(QString id);

    void f_setComment(QString);
    QString f_getComment() const;
    void setFunction(const QString&);
    QString getFunction() const;


    void f_setFunction(QString);
    QString f_getFunction() const;

    bool isFirable();
    void fire();

    void setLabel_1();
    void setLabel_2();

    bool hasRelations ();
    TRANS_RELATION getTrans_Relations() const;

    /* @;;;; */
    int type () const;
    QRectF boundingRect() const;
    QPainterPath shape () const;
    //todo
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);
    bool collidesWithItem ( const QGraphicsItem * other, Qt::ItemSelectionMode mode ) const;

    void setRotation(int degree);
    int getRotation() const;
    QString getComment();
    bool getShow();
    void setShow(bool);

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
    QString name;
    QString m_comment;
    bool show = false;
    int rotation;

    QString self_function="MassAction(1)";
    QString m_function;
    QString m_action;
    QGraphicsSimpleTextItem * label;

    //todo
    QList<Arc *> input;
    QList<Arc *> output;

    int mode;
    QColor color;

    static const QColor defalut_brushColor;
    static const QColor defalut_penColor;

    QColor m_brushColor = defalut_brushColor;
    QColor m_penColor = defalut_penColor;


};
#endif // TRANSITION_H
