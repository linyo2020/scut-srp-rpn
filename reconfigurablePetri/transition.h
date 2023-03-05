#ifndef TRANSITION_H
#define TRANSITION_H
//new 田俊杰
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QGraphicsSimpleTextItem>
#include<QPainter>
#include"arcus.h"
#include<QGraphicsScene>
#include<place.h>
#include"defs.h"
class Transition : public QGraphicsRectItem
{
 public:

    enum { Type = UserType + 2 };

    explicit Transition(const QString &id);
    Transition(const TRANSITION_ATTR &transition);
    //2023.03.03
    Transition(const TRANSITION_ATTR &transition,int count);
    //控件用到
    Transition(const QString &id,const QPointF &position);
    Transition();

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

    bool isInComponent();
    void setIncomponent(bool isInComponent);

    bool IsNormalPort();
    bool IsCompoundPort();

    QList<Arcus*>getinput();

    QList<Arcus*>getoutput();

    void pushInput(Arcus*a);
    void pushOutput(Arcus*a);

    void setNormalPort(bool flag);
    void setCompoundPort(bool flag);

    QString getName(QString ComID);
    QStringList getFileName();
    QStringList getComponentID();
    QList<Arcus *> input;
    QList<Arcus *> output;



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

    bool isNormalPort=false;//normalport就是指该transition未与其他端口复合
    bool isCompoundPort=false;//与其他端口复合后，该属性为true




    int mode;
    QColor color;

    static const QColor defalut_brushColor;
    static const QColor defalut_penColor;

    QColor m_brushColor = defalut_brushColor;
    QColor m_penColor = defalut_penColor;

    //不要碰
    bool InComponent=false;

};
#endif // TRANSITION_H
