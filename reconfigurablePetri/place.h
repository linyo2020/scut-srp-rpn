#ifndef PLACE_H
#define PLACE_H

#include <QGraphicsEllipseItem>

#include "arc.h"

class Place : public QGraphicsEllipseItem
{
 public:

    enum { Type = UserType + 1 };

    explicit Place(const QString &id);
    Place(const PLACE_ATTR &place);
    ~Place ();

    void createPlace();
    PLACE_ATTR toXml() const;

    void addInputArc(QGraphicsItem * arc);
    void addOutputArc(QGraphicsItem * arc);
    void deleteArc(QString id);

    double getTokens() const;
    void setTokens (double tok);
    void updateTokens(double tok);
    int getCapacity() const;
    void setCapacity(int c);
    QString getName () const;
    void setName (const QString& nm);
    QString getId () const;
    QString f_getComment() const;
    void f_setComment(QString);
    void setLabel_1();
    void setLabel_2();

    //设置端口
    void drawInputport();
    void drawOutputport();
    void cancelSetPort();

    bool reachCapacity(Arc* arc);
    bool hasRelations ();

    int type () const;
    QRectF boundingRect() const;
    QPainterPath shape () const;
    QVariant itemChange (GraphicsItemChange change, const QVariant &value);
    bool collidesWithItem ( const QGraphicsItem * other,
     Qt::ItemSelectionMode mode ) const;
    QString getComment();
    bool getShow();
    void setShow(bool);

    QColor getBrushColor() const;
    QColor getPenColor() const;
    void setBrushColor(QColor color);
    void setPenColor(QColor color);

    //判断是否为端口
    bool isInputPort();
    bool isOutputPort();
    void setInputPort(bool);
    void setOutputPort(bool);

 protected:

    void paint ( QPainter * painter,
    const QStyleOptionGraphicsItem * option,
        QWidget * widget );

 private:

    QString id;
    QString name;
    QString m_comment;
    bool show = false;
    double tokens=0;
    int capacity=0;

    QGraphicsSimpleTextItem * label;

    QList<Arc*> input;
    QList<Arc*> output;

    QColor m_brushColor=defalut_brushColor;
    QColor m_penColor=defalut_penColor;

    static const QColor defalut_brushColor;
    static const QColor defalut_penColor;

    //判断是否为端口
    bool inputPort=false;
    bool outputPort=false;

};

#endif // PLACE_H
