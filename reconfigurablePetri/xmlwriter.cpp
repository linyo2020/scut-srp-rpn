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
    xml.setCodec("utf-8");
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

        for(const PAGE_ATTR &page : ptnet.pages)
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
bool XmlWriter::writePage(QXmlStreamWriter &xml, const PAGE_ATTR &page)
{
    /* <page id="pagexx"> */
    xml.writeStartElement("page");
    xml.writeAttribute("id", page.id);

    xml.writeStartElement("name");
        xml.writeTextElement("text", page.name);
    xml.writeEndElement();



    for(const auto &place : page.placeNodes)
    {
        if(!writePlaceNode(xml, place))
            qDebug()<<"Error ...";
    }

    for(const auto &transition : page.transitionNodes)
    {
        if(!writeTransitionNode(xml, transition))
            qDebug()<<"Error ...";
    }

    for(const auto &arc : page.arcs)
    {
        if(!writeArc(xml, arc))
            qDebug()<<"Error ...";
    }
    for(const auto &conn : page.connector)
    {
        if(!writeConnnector(xml, conn))
            qDebug()<<"Error ...";
    }
    for(const auto &component : page.componentList)
    {
        if(!writeComponent(xml,component))
            qDebug()<<"Error ...";
    }
    for(const auto &rule : page.rules)
    {
        if(!writeRule(xml,rule))
            qDebug()<<"Error ...";
    }

    xml.writeEndElement();
    /* </page>*/

    if (xml.hasError ())
      return false;

     return true;
}

/* write place */
bool XmlWriter::writePlaceNode(QXmlStreamWriter &xml, const PLACE_ATTR &place)
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
   QString inputPort=(place.inputPort?"Y":"N");
   QString outputPort=(place.outputPort?"Y":"N");
   QString isCompoundPort=(place.isCompoundPort?"Y":"N");

   /* <place id="xx" component_id="xx"> */
   xml.writeStartElement("place");
   xml.writeAttribute("id", place.id);
   xml.writeAttribute("component_id",place.component_id);

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

    /* <port> */
    xml.writeStartElement("port");
        xml.writeTextElement("inputPort",inputPort);
        xml.writeTextElement("outputPort",outputPort);
        xml.writeTextElement("isCompoundPort",isCompoundPort);
    xml.writeEndElement();

  xml.writeEndElement();
  /*</place>*/

  if (xml.hasError ())
    return false;

   return true;
}

bool XmlWriter::writeTransitionNode(QXmlStreamWriter &xml, const TRANSITION_ATTR &transition)
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
bool XmlWriter::writeArc(QXmlStreamWriter &xml, const ARC_ATTR &arc)
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

        for(const auto &p : arc.points)
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
/* write connector */
bool XmlWriter::writeConnnector(QXmlStreamWriter &xml, const CONNECTOR_ATTR &connector)
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

        for(const auto &p : connector.points)
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

bool XmlWriter::writeComponent(QXmlStreamWriter &xml, const COMPONENT_ATTR &component)
{
    QVariant v;
    v.setValue(component.step);
    QString step=v.toString();

    /* <component id="xx" type="xx" step="xx"> */
    xml.writeStartElement("component");
    xml.writeAttribute("id",component.id);
    xml.writeAttribute("type",component.type);
    xml.writeAttribute("step",step);

    /* <name> */
    xml.writeStartElement("name");
        xml.writeTextElement("text",component.name);
    xml.writeEndElement();
    /* </name> */

    for(const auto &place : component.placeNodes)
    {
        if(!writePlaceNode(xml,place))
            qDebug()<<"Error ...";
    }
    for(const auto &transition : component.transitionNodes)
    {
        if(!writeTransitionNode(xml, transition))
            qDebug()<<"Error ...";
    }

    for(const auto &arc : component.arcs)
    {
         if(!writeArc(xml, arc))
            qDebug()<<"Error ...";
    }
    return true;
}

bool XmlWriter::writeRule(QXmlStreamWriter &xml, const RULE_ATTR &rule)
{
    QString type=QString::number(rule.type);

    /* <rule type="xx"> */
    xml.writeStartElement("rule");
    xml.writeAttribute("type",type);

    /* <name> */
    xml.writeStartElement("name");
        xml.writeTextElement("text",rule.name);
    xml.writeEndElement();

    /* <comment> */
    xml.writeStartElement("comment");
        xml.writeTextElement("text",rule.comment);
    xml.writeEndElement();

    /* <orCondition> */
    xml.writeStartElement("orCondition");
    for(const auto &orCondition:rule.conditions)
    {
        /* <andCondition> */
        xml.writeStartElement("andCondition");
        for(const auto &andCondition:orCondition)
        {
            QString conditionOption=QString::number(int(andCondition.conditionOption));
            QString symbol=QString::number(int(andCondition.symbol));

            /* <condition> */
            xml.writeStartElement("condition");
                xml.writeTextElement("conditionOption",conditionOption);
                xml.writeTextElement("monitorFactor",andCondition.monitorFactor);
                xml.writeTextElement("symbol",symbol);
                xml.writeTextElement("value",andCondition.value.toString());
            if(andCondition.rearPart!=nullptr)
            {
                conditionOption=QString::number(int(andCondition.rearPart->conditionOption));
                symbol=QString::number(int(andCondition.rearPart->symbol));

                /* <rearPart> */
                xml.writeStartElement("rearPart");
                    xml.writeTextElement("conditionOption",conditionOption);
                    xml.writeTextElement("monitorFactor",andCondition.rearPart->monitorFactor);
                    xml.writeTextElement("symbol",symbol);
                    xml.writeTextElement("value",andCondition.rearPart->value.toString());
                xml.writeEndElement();
            }
            xml.writeEndElement();
        }
        xml.writeEndElement();
        /* </andCondition> */
    }
    xml.writeEndElement();
    /* </orCondition> */

    for(const auto &operation:rule.operations)
    {
        QString type=QString::number(operation.type);

        /* <operation type="xx"> */
        xml.writeStartElement("operation");
        xml.writeAttribute("type",type);
        for(const auto &argument:operation.arguments)
        {
            /* <argument> */
            xml.writeTextElement("argument",argument);
        }
        for(const auto &ports:operation.portsToMerge)
        {
            /* <portsToMerge port1="xx" port2="xx"> */
            xml.writeStartElement("portsToMerge");
            xml.writeAttribute("port1",ports.first);
            xml.writeAttribute("port2",ports.second);
            xml.writeEndElement();
        }

        xml.writeEndElement();
    }

    xml.writeEndElement();
    /* </rule> */
    if(xml.hasError())
        return false;
    return true;
}

