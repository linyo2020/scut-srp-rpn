#include "place.h"
#include<QtGlobal>
#include<qdebug.h>
const QColor Place::defalut_brushColor = Qt::white;
const QColor Place::defalut_penColor = Qt::black;

Place::Place(const QString &id)
{
    this->id = id;
    name = id;
    createPlace();

    label->setPos(30, 30);
}

Place::Place()
{
    label=new QGraphicsSimpleTextItem();
}

/* From XML */
Place::Place(const PLACE_ATTR &place)
{
    id = place.id;
    //component_id=place.componet_id;
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

Place::Place(const QString &id, const QPointF &position)
{
    this->id=id;
    //might have bug
    label->setPos(position.x(),position.y());
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
    if(inputPort&&!outputPort&&!isCompoundPort)
        drawInputport();
    else if(!inputPort&&outputPort&&!isCompoundPort)
        drawOutputport();
    else if(inputPort&&outputPort&&isCompoundPort)
        drawCompoundport();
    else
        cancelSetPort();
}

void Place::setCompoundPort(bool flag)
{
    isCompoundPort=flag;
    if(inputPort&&!outputPort&&!isCompoundPort)
        drawInputport();
    else if(!inputPort&&outputPort&&!isCompoundPort)
        drawOutputport();
    else if(inputPort&&outputPort&&isCompoundPort)
        drawCompoundport();
    else
        cancelSetPort();
}
bool Place::isOutputPort()
{
    return outputPort;
}

void Place::setOutputPort(bool flag)
{
    outputPort = flag;
    if(inputPort&&!outputPort&&!isCompoundPort)
        drawInputport();
    else if(!inputPort&&outputPort&&!isCompoundPort)
        drawOutputport();
    else if(inputPort&&outputPort&&isCompoundPort)
        drawCompoundport();
    else
        cancelSetPort();
}

bool Place::isACompoundPort()
{
    return this->isCompoundPort;
}

bool Place::isInComponent()
{
    return this->InComponent;
}

void Place::setIncomponent(bool isInComponent)
{
    this->InComponent=isInComponent;
}

bool Place::isNormalPort()
{
    if(isCompoundPort==false)
    {
        if(this->isInputPort()||this->isOutputPort())
        {
            return true;
        }
    }
    return false;
}
QList<Arcus*> Place::getinput()
{
    return input;
}
QList<Arcus*> Place::getoutput()
{
    return output;
}

void Place::pushInput(Arcus *a)
{
    this->input.push_back(a);
}

void Place::pushOutput(Arcus *a)
{
    this->output.push_back(a);
}

//传入单独的组号，返回该组号下对应的name
//无校验
QString Place::getName(QString singleComID)
{
    Q_ASSERT_X(this->getComponentID().size()<=2,"Place ID","the number of place(in compoundPort) exceeds the limit");
    if(this->getComponentID()[0]==singleComID)
    {
        return this->getId().split("+")[0].split("&")[2];
    }
    else if(this->getComponentID()[1]==singleComID)
    {
        return this->getId().split("+")[1].split("&")[2];
    }

}

QStringList Place::getFileName()
{
    QStringList id;
    id.push_back(this->getComponentID()[0].split("&")[0]);
    if(this->getComponentID().size()==2)
    {
        id.push_back(this->getComponentID()[1].split("&")[0]);
    }
    return id;
}

QStringList Place::getComponentID()
{
    QStringList ID=this->getId().split("+");
    QStringList cID;
    cID.push_back(ID[0].split("&")[0]+"&"+ID[0].split("&")[1]);
    if(ID.size()==2)
    {
        cID.push_back(ID[1].split("&")[0]+"&"+ID[1].split("&")[1]);
    }

    return cID;
}
void Place::setcontain_portNum(int n)
{
    contain_portNum=n;
}

int Place::getcontain_portNum()
{
    return contain_portNum;
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
  pos();
  place.x = mapToScene(QPointF(0,0)).x();
  place.y = mapToScene(QPointF(0,0)).y();
  place.offsetx = label->x();
  place.offsety = label->y();
  place.comment = m_comment;
  place.show = show;
  place.brushColor = m_brushColor;
  place.penColor = m_penColor;
//  place.componet_id=component_id;
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
   input << qgraphicsitem_cast<Arcus*>(arc);
}

/* add output arc */
void Place::addOutputArc(QGraphicsItem * arc)
{
   output << qgraphicsitem_cast<Arcus*>(arc);
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
    if((tok<0)&&(tokens==0.0))
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
double Place::getCapacity() const
{
  return capacity;
}

void Place::setCapacity(double c)
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

void Place::setPlaceID(QString id)
{
    this->id=id;
}
void Place::drawInputport()
{
    QString lb;

        lb=QString (name+"\n"+"inputPort");

   label->setText(lb);

    m_brushColor = QColor(170, 255, 127);
    update();
}
void Place::drawOutputport()
{
    QString lb;

        lb=QString (name+"\n"+"outputPort");

   label->setText(lb);

   m_brushColor = QColor(255, 170, 127);
   update();
}
void Place::drawCompoundport()
{
    QString lb;

        lb=QString (name+"\n"+"compoundPort");

   label->setText(lb);

   m_brushColor = QColor(255, 127, 170);
   update();
}
void Place::cancelSetPort()
{
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
bool Place::reachCapacity(Arcus * arc)
{

  if(capacity == 0.0)
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
        foreach (Arcus * inarc, input)
            inarc->updatePosition();

        foreach (Arcus * outarc, output)
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
        foreach(Arcus * arc, input)
            arc->setSelected(true);
        foreach(Arcus * arc, output)
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
    //画圆
    painter->drawEllipse (0, 0, place_diameter, place_diameter);
    //判断是否为端口再画图
    if(isInputPort())
    {
        painter->drawEllipse (3, 3, place_diameter-6, place_diameter-6);
    }
    if (isOutputPort()) {
        //用drawConvexPolygon画三角形
            static const QPointF points[3] = {
                  QPointF(place_diameter/2-place_diameter*0.866/2, place_diameter*1.5/2),
                  QPointF(place_diameter/2, 0),
                  QPointF(place_diameter/2+place_diameter*0.866/2,place_diameter*1.5/2)
              };
            painter->drawConvexPolygon(points, 3);

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

