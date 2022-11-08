#include "place.h"

const QColor Place::defalut_brushColor = Qt::white;
const QColor Place::defalut_penColor = Qt::black;

Place::Place(const QString &id)
{
    this->id = id;
    name = id;
    createPlace();

    label->setPos(30, 30);
}

/* From XML */
Place::Place(const PLACE_ATTR &place)
{
    id = place.id;

    if(place.name.isNull())
        name = id;
    else
        name = place.name;

    tokens = place.initmark;

    capacity = place.capacity;

    m_comment = place.comment;

    m_brushColor = place.brushColor;

    m_penColor = place.penColor;

    show = place.show;

    createPlace();

    label->setPos(place.offsetx, place.offsety);

    if(show)setLabel_2();
}

bool Place::getShow()
{
    return show;
}

void Place::setShow(bool flag)
{
    show = flag;
}
//判断端口
bool Place::isInputPort()
{
    return inputPort;
}

void Place::setInputPort(bool flag)
{
    inputPort = flag;
}

bool Place::isOutputPort()
{
    return outputPort;
}

void Place::setOutputPort(bool flag)
{
    outputPort = flag;
}


QColor Place::getBrushColor() const
{
    return m_brushColor;
}

QColor Place::getPenColor() const
{
    return m_penColor;
}

void Place::setBrushColor(QColor color)
{
    m_brushColor = color;
    update();
}

void Place::setPenColor(QColor color)
{
    m_penColor = color;
    update();
}

QString Place::getComment()
{
    return m_comment;
}

/* return place attributes as a structure */
PLACE_ATTR Place::toXml() const
{
  PLACE_ATTR place;

  place.id = id;
  place.name = name;
  place.initmark = tokens;
  place.capacity = capacity;
  place.x = pos().x();
  place.y = pos().y();
  place.offsetx = label->x();
  place.offsety = label->y();
  place.comment = m_comment;
  place.show = show;
  place.brushColor = m_brushColor;
  place.penColor = m_penColor;

  return place;
}

void Place::createPlace()
{
    setRect(0, 0, place_diameter, place_diameter);


    setZValue(1000.0);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    label = new QGraphicsSimpleTextItem(this);
    label->setFlag(QGraphicsItem::ItemIsMovable, true);
    label->setFlag(QGraphicsItem::ItemIsSelectable, true);
    label->setText(name);
}


/* add input arc */
void Place::addInputArc(QGraphicsItem * arc)
{
   input << qgraphicsitem_cast<Arc*>(arc);
}

/* add output arc */
void Place::addOutputArc(QGraphicsItem * arc)
{
   output << qgraphicsitem_cast<Arc*>(arc);
}

/* delete Arc */
void Place::deleteArc(QString id)
{
    for(int i=0; i < input.size(); i++)
    {
        if(input[i]->getId() == id)
        {
            input.removeAt(i);
            return;
        }
    }

    for(int i=0; i < output.size(); i++)
    {
        if(output[i]->getId() == id)
        {
            output.removeAt(i);
            return;
        }
    }
}

/* update tokens */
void Place::updateTokens(double tok)
{
    if((tok<0)&&(tokens==0))
            return;

    tokens += tok;
}

void Place::setTokens (double tok)
{
    tokens = tok;
}

/* get tokens */
double Place::getTokens()  const
{
  return tokens;
}

/* get capacity */
int Place::getCapacity() const
{
  return capacity;
}

void Place::setCapacity(int c)
{
    capacity = c;
}

/* get name */
QString Place::getName ()  const
{
    return name;
}

/* set name */
void Place::setName (const QString& nm)
{
    name = nm;
}

/* get id */
QString Place::getId ()  const
{
    return id;
}

void Place::setLabel_1()
{
   label->setText(name);
}

void Place::setLabel_2()
{
    //文本设置
    QString lb;

        lb=QString (name+"\n"+f_getComment());

   label->setText(lb);

}
void Place::drawInputport()
{
    QString lb;

        lb=QString (name+"\n"+"inputPort");

   label->setText(lb);

    m_brushColor = QColor(170, 255, 127);
    setInputPort(true);
    setOutputPort(false);
    update();
}
void Place::drawOutputport()
{
    QString lb;

        lb=QString (name+"\n"+"outputPort");

   label->setText(lb);

   m_brushColor = QColor(255, 170, 127);
   setOutputPort(true);
   setInputPort(false);
   update();
}
void Place::cancelSetPort()
{
     setInputPort(false);
     setOutputPort(false);

     m_brushColor =defalut_brushColor;
     m_penColor =defalut_penColor;
     update();
}

/* set comment */
void Place::f_setComment(QString str)
{
    m_comment=str;
}
/* get comment */
QString Place::f_getComment() const
{
    return m_comment;
}

/* Check if the place reach capacity with connection "arc" */
bool Place::reachCapacity(Arc * arc)
{

  if(capacity == 0)
      return false;
  else if(arc->getWeight()+tokens > capacity)
      return true;
  //this place update for weight from double to QString by syx 8.15
  else
      return false;
}

bool Place::hasRelations ()
{
    if (input.isEmpty() && output.isEmpty())
        return false;
    else
        return true;
}

int Place::type () const
{
    return Type;
}

QRectF Place::boundingRect() const
{
    qreal a = (pen().width())/2;
    return QRectF(0, 0, place_diameter, place_diameter)
            .normalized()
            .adjusted(-a, -a, a, a);
}

QPainterPath Place::shape () const
{
    QPainterPath shape;
    shape.addEllipse(0, 0, place_diameter , place_diameter);
    return shape;
}

QVariant Place::itemChange (GraphicsItemChange change, const QVariant &value)
{

    if ((change == QGraphicsItem::ItemPositionChange)
    ||(change == QGraphicsItem::ItemPositionHasChanged))
    {
        foreach (Arc * inarc, input)
            inarc->updatePosition();

        foreach (Arc * outarc, output)
            outarc->updatePosition();
    }

    return value;
}

void Place::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option,
             QWidget * widget )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QColor PenColor;
    QColor BrushColor;

    if((input.isEmpty()) && (output.isEmpty()))
    {
        PenColor = Qt::darkRed;
        BrushColor = QColor(255, 240, 240);
    }
    else if(isSelected())
    {
        foreach(Arc * arc, input)
            arc->setSelected(true);
        foreach(Arc * arc, output)
            arc->setSelected(true);

        PenColor = Qt::blue;
        BrushColor = QColor(240, 240, 255);
    }
    else
    {
        PenColor = m_penColor;
        BrushColor = m_brushColor;
    }


    painter->setPen (QPen(PenColor, 1, Qt::SolidLine,
     Qt::RoundCap, Qt::MiterJoin));
    label->setBrush (PenColor);
    painter->setBrush (BrushColor);
    painter->setRenderHint (QPainter::Antialiasing);
    //判断是否为端口再画图
    if(isInputPort())
    {
        painter->drawEllipse (0, 0, place_diameter, place_diameter);
        painter->drawEllipse (3, 3, place_diameter-6, place_diameter-6);
    }
    else if (isOutputPort()) {
        painter->drawEllipse (0, 0, place_diameter, place_diameter);
        //用drawConvexPolygon画三角形
            static const QPointF points[3] = {
                  QPointF(place_diameter/2-place_diameter*0.866/2, place_diameter*1.5/2),
                  QPointF(place_diameter/2, 0),
                  QPointF(place_diameter/2+place_diameter*0.866/2,place_diameter*1.5/2)
              };
            painter->drawConvexPolygon(points, 3);

    }
    else {
        painter->drawEllipse (0, 0, place_diameter, place_diameter);
    }



    painter->setBrush (PenColor);

    if(tokens == 1)
     painter->drawEllipse(10, 10, 10, 10);
    else if(tokens == 2)
    {
        painter->drawEllipse(15, 15, 10, 10);
        painter->drawEllipse(5, 5, 10, 10);
    }
    else if(tokens == 3)
    {
        painter->drawEllipse(15, 15, 10, 10);
        painter->drawEllipse(8, 3, 10, 10);
        painter->drawEllipse(3, 15, 10, 10);
    }
    else if(tokens == 0)
    {

    }
    else
    {
        QVariant v(tokens);
        if(tokens < 100)
            painter->drawText(7, 20, QString(v.toString()));
        else
            painter->drawText(4, 20, QString(v.toString()));
    }
    /*else if(tokens == 4)
    {
        painter->drawEllipse(20, 20, 5, 5);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
    }*/
    /*else if(tokens == 5)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
    }
    else if(tokens == 6)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
    }
    else if(tokens == 7)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
    }
    else if(tokens == 8)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
        painter->drawEllipse(13, 6, 4, 4);
        painter->drawEllipse(13, 20, 4, 4);
    }

    else if(tokens == 9)
    {
        painter->drawEllipse(20, 20, 4, 4);
        painter->drawEllipse(6, 6, 4, 4);
        painter->drawEllipse(6, 20, 4, 4);
        painter->drawEllipse(20, 6, 4, 4);
        painter->drawEllipse(6, 13, 4, 4);
        painter->drawEllipse(20, 13, 4, 4);
        painter->drawEllipse(13, 13, 4, 4);
        painter->drawEllipse(13, 6, 4, 4);
        painter->drawEllipse(13, 20, 4, 4);
    }
    else if(tokens > 9)
    {
        QVariant v(tokens);
        if(tokens < 100)
            painter->drawText(7, 20, QString(v.toString()));
        else
            painter->drawText(4, 20, QString(v.toString()));
    }*/

}

bool Place::collidesWithItem ( const QGraphicsItem * other, Qt::ItemSelectionMode mode ) const
{
    Q_UNUSED(mode);
    QPainterPath path1 = this->mapFromItem(other, other->shape());
    return path1.intersects(this->shape());
}

Place::~Place ()
{
    delete label;
}

