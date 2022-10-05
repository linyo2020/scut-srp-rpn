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

    bool writePage(QXmlStreamWriter &xml, PAGE_ATTR page);
    bool writePlaceNode(QXmlStreamWriter &xml, PLACE_ATTR place);
    bool writeTransitionNode(QXmlStreamWriter &xml, TRANSITION_ATTR transition);
    bool writeArc(QXmlStreamWriter &xml, ARC_ATTR arc);
    PTNET_ATTR ptnet;
};

#endif
