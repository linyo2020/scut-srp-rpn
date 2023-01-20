#include "xmlwriter.h"

#include <QDebug>

XmlWriter::XmlWriter(const PTNET_ATTR &net)
{
    ptnet = net;
}

//![0]
bool XmlWriter::writeXML(QFile * xmlContent)
{
    QXmlStreamWriter xml(xmlContent);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("pnml");
    //xml.writeDefaultNamespace("http://www.pnml.org/version-2009/grammar/pnml");

     xml.writeStartElement("net");
     xml.writeAttribute("id", ptnet.id);
     xml.writeAttribute("type", "http://www.pnml.org/version-2009/grammar/ptnet");


        xml.writeStartElement("name");
            xml.writeTextElement("text", ptnet.name);
        xml.writeEndElement();

        foreach(PAGE_ATTR page, ptnet.pages)
        {
            if(!writePage(xml, page))
                qDebug()<<"Error ...";
        }

     xml.writeEndElement();
     /* </net> */

    xml.writeEndElement();
   /* </pnml> */

   xml.writeEndDocument();

  if (xml.hasError ())
    return false;

  return true;
}
//![0]

//![1]
/* write page */
bool XmlWriter::writePage(QXmlStreamWriter &xml, PAGE_ATTR page)
{
    /* <page id="pagexx"> */
    xml.writeStartElement("page");
    xml.writeAttribute("id", page.id);

    xml.writeStartElement("name");
        xml.writeTextElement("text", page.name);
    xml.writeEndElement();


        foreach(PLACE_ATTR place, page.placeNodes)
        {
            if(!writePlaceNode(xml, place))
                qDebug()<<"Error ...";
        }

        foreach(TRANSITION_ATTR transition, page.transitionNodes)
        {
            if(!writeTransitionNode(xml, transition))
                qDebug()<<"Error ...";
        }

        foreach(ARC_ATTR arc, page.arcs)
        {
             if(!writeArc(xml, arc))
                qDebug()<<"Error ...";
        }
        foreach(CONNECTOR_ATTR conn, page.connector)
        {
             if(!writeConnnector(xml, conn))
                qDebug()<<"Error ...";
        }

    xml.writeEndElement();
    /* </page>*/

    if (xml.hasError ())
      return false;

     return true;
}

/* write place */
bool XmlWriter::writePlaceNode(QXmlStreamWriter &xml, PLACE_ATTR place)
{
   QVariant v;
   v.setValue(place.x);
   QString x = v.toString();
   v.setValue(place.y);
   QString y = v.toString();
   v.setValue(place.offsetx);
   QString offsetx = v.toString();
   v.setValue(place.offsety);
   QString offsety = v.toString();
   v.setValue(place.initmark);
   QString initmark = v.toString();
   v.setValue(place.capacity);
   QString capacity = v.toString();
   QString show = (place.show?"Y":"N");
   int r,g,b;
   place.brushColor.getRgb(&r,&g,&b);
   v.setValue(r);
   QString bRed = v.toString();
   v.setValue(g);
   QString bGreen = v.toString();
   v.setValue(b);
   QString bBlue = v.toString();
   place.penColor.getRgb(&r,&g,&b);
   v.setValue(r);
   QString pRed = v.toString();
   v.setValue(g);
   QString pGreen = v.toString();
   v.setValue(b);
   QString pBlue = v.toString();

   /* <place id="xx"> */
   xml.writeStartElement("place");
   xml.writeAttribute("id", place.id);

   /* <component_id> */
   xml.writeStartElement("component_id");
        xml.writeTextElement("id",place.component_id);
   xml.writeEndElement();

    /*<name>*/
    xml.writeStartElement("name");
        xml.writeTextElement("text", place.name);
        xml.writeStartElement("graphics");
            xml.writeEmptyElement("offset");
            xml.writeAttribute("x", offsetx);
            xml.writeAttribute("y", offsety);
        xml.writeEndElement();
    xml.writeEndElement();
    /*</name>*/

    /* <color> */
    xml.writeStartElement("color");
        xml.writeEmptyElement("brush");
            xml.writeAttribute("red", bRed);
            xml.writeAttribute("green", bGreen);
            xml.writeAttribute("blue", bBlue);
        xml.writeEmptyElement("pen");
            xml.writeAttribute("red", pRed);
            xml.writeAttribute("green", pGreen);
            xml.writeAttribute("blue", pBlue);
    xml.writeEndElement();
    /* </color> */

    /* <toolspecific> */
    xml.writeStartElement("toolspecific");
        xml.writeAttribute("tool", "petrinet");
        xml.writeAttribute("version", "1.0");
        xml.writeEmptyElement("placeCapacity");
        xml.writeAttribute("capacity", capacity);
    xml.writeEndElement();
    /* </toolspecific> */

    xml.writeStartElement("graphics");
        xml.writeEmptyElement("position");
        xml.writeAttribute("x", x);
        xml.writeAttribute("y", y);
    xml.writeEndElement();

    /* <initialMarking> */
    xml.writeStartElement("initialMarking");
        xml.writeTextElement("text", initmark);
    xml.writeEndElement();

    /* <comment> */
    xml.writeStartElement(("comment"));
        xml.writeTextElement("text", place.comment);
        xml.writeTextElement("show", show);
    xml.writeEndElement();

  xml.writeEndElement();
  /*</place>*/

  if (xml.hasError ())
    return false;

   return true;
}

bool XmlWriter::writeTransitionNode(QXmlStreamWriter &xml, TRANSITION_ATTR transition)
{
   QVariant v;
   v.setValue(transition.x);
   QString x = v.toString();
   v.setValue(transition.y);
   QString y = v.toString();
   v.setValue(transition.offsetx);
   QString offsetx = v.toString();
   v.setValue(transition.offsety);
   QString offsety = v.toString();
   v.setValue(transition.rotation);
   QString rotation = v.toString();
   v.setValue(transition.self_function);
   QString self_function=v.toString();
   //v.setValue(transition.MassAction);
   //QString MassAction=v.toString();
   QString show = (transition.show?"Y":"N");
   int r,g,b;
   transition.brushColor.getRgb(&r,&g,&b);
   v.setValue(r);
   QString bRed = v.toString();
   v.setValue(g);
   QString bGreen = v.toString();
   v.setValue(b);
   QString bBlue = v.toString();
   transition.penColor.getRgb(&r,&g,&b);
   v.setValue(r);
   QString pRed = v.toString();
   v.setValue(g);
   QString pGreen = v.toString();
   v.setValue(b);
   QString pBlue = v.toString();

   xml.writeStartElement("transition");
   xml.writeAttribute("id", transition.id);

    /*<name>*/
    xml.writeStartElement("name");
        xml.writeTextElement("text", transition.name);
        xml.writeStartElement("graphics");
        xml.writeEmptyElement("offset");
        xml.writeAttribute("x", offsetx);
        xml.writeAttribute("y", offsety);
        xml.writeEndElement();
    xml.writeEndElement();
    /*</name>*/

    /* <color> */
    xml.writeStartElement("color");
        xml.writeEmptyElement("brush");
            xml.writeAttribute("red", bRed);
            xml.writeAttribute("green", bGreen);
            xml.writeAttribute("blue", bBlue);
        xml.writeEmptyElement("pen");
            xml.writeAttribute("red", pRed);
            xml.writeAttribute("green", pGreen);
            xml.writeAttribute("blue", pBlue);
    xml.writeEndElement();
    /* </color> */

      /* <toolspecific> */
      xml.writeStartElement("toolspecific");
        xml.writeAttribute("tool", "petrinet");
        xml.writeAttribute("version", "1.0");
        xml.writeEmptyElement("rotation");
        xml.writeAttribute("degree", rotation);
      xml.writeEndElement();
      /* </toolspecific> */

    xml.writeStartElement("graphics");
        xml.writeEmptyElement("position");
        xml.writeAttribute("x", x);
        xml.writeAttribute("y", y);
    xml.writeEndElement();


    xml.writeStartElement("function");
        xml.writeTextElement("text", transition.self_function);
    xml.writeEndElement();

    /* <comment> */
    xml.writeStartElement(("comment"));
        xml.writeTextElement("text", transition.comment);
        xml.writeTextElement("show", show);
    xml.writeEndElement();

  xml.writeEndElement();
  /*</transition>*/

  if (xml.hasError ())
    return false;

   return true;
}

/* write arc */
bool XmlWriter::writeArc(QXmlStreamWriter &xml, ARC_ATTR arc)
{
    QVariant v;
    int r,g,b;
    arc.brushColor.getRgb(&r,&g,&b);
    v.setValue(r);
    QString bRed = v.toString();
    v.setValue(g);
    QString bGreen = v.toString();
    v.setValue(b);
    QString bBlue = v.toString();
    arc.penColor.getRgb(&r,&g,&b);
    v.setValue(r);
    QString pRed = v.toString();
    v.setValue(g);
    QString pGreen = v.toString();
    v.setValue(b);
    QString pBlue = v.toString();
    v=arc.weight;
    QString weight=v.toString();

    xml.writeStartElement("arc");
    xml.writeAttribute("id", arc.id);
    xml.writeAttribute("source", arc.source);
    xml.writeAttribute("target", arc.target);

    /* <inscription> */
    xml.writeStartElement("inscription");
        xml.writeTextElement("text", weight);
    xml.writeEndElement();

    /* <graphics>*/
    if(!arc.points.isEmpty())
    {
        /* <graphics> */
        xml.writeStartElement("graphics");

        foreach(QPointF p, arc.points)
        {
            xml.writeEmptyElement("position");
                v.setValue(p.x());
            xml.writeAttribute("x", v.toString());
                v.setValue(p.y());
            xml.writeAttribute("y", v.toString());
        }

        xml.writeEndElement();
        /* </graphics> */
    }

    /* <color> */
    xml.writeStartElement("color");
        xml.writeEmptyElement("brush");
            xml.writeAttribute("red", bRed);
            xml.writeAttribute("green", bGreen);
            xml.writeAttribute("blue", bBlue);
        xml.writeEmptyElement("pen");
            xml.writeAttribute("red", pRed);
            xml.writeAttribute("green", pGreen);
            xml.writeAttribute("blue", pBlue);
    xml.writeEndElement();
    /* </color> */

    xml.writeEndElement();
    /* </arc> */

    if (xml.hasError ())
        return false;

    return true;
}
/* write arc */
bool XmlWriter::writeConnnector(QXmlStreamWriter &xml, CONNECTOR_ATTR connector)
{
    QVariant v;
    xml.writeStartElement("connector");
    xml.writeAttribute("id", connector.id);
    xml.writeAttribute("source", connector.source);
    xml.writeAttribute("target", connector.target);


    /* <graphics>*/
    if(!connector.points.isEmpty())
    {
        /* <graphics> */
        xml.writeStartElement("graphics");

        foreach(QPointF p, connector.points)
        {
            xml.writeEmptyElement("position");
                v.setValue(p.x());
            xml.writeAttribute("x", v.toString());
                v.setValue(p.y());
            xml.writeAttribute("y", v.toString());
        }

        xml.writeEndElement();
        /* </graphics> */
    }


    xml.writeEndElement();
    /* </connector> */

    if (xml.hasError ())
        return false;

    return true;
}
