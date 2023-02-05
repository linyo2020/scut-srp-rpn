#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QVariant>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>

#include "defs.h"

class XmlWriter
{

 public:

    explicit XmlWriter(const PTNET_ATTR &net);

    bool writeXML(QFile * xmlContent);


 private:

    bool writePage(QXmlStreamWriter &xml, const PAGE_ATTR &page);
    bool writePlaceNode(QXmlStreamWriter &xml, const PLACE_ATTR &place);
    bool writeTransitionNode(QXmlStreamWriter &xml, const TRANSITION_ATTR &transition);
    bool writeArc(QXmlStreamWriter &xml, const ARC_ATTR &arc);
    bool writeConnnector(QXmlStreamWriter &xml, const CONNECTOR_ATTR &connector);
    bool writeComponent(QXmlStreamWriter &xml,const COMPONENT_ATTR &component);
    bool writeRule(QXmlStreamWriter &xml,const RULE_ATTR &rule);
    PTNET_ATTR ptnet;
};

#endif
