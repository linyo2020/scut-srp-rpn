#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <QXmlStreamReader>
#include <QVariant>

#include "defs.h"

class XmlParser
{

public:

    explicit XmlParser(){
        pen.red = 0;
        pen.green = 0;
        pen.blue = 0;
        brush.red = 255;
        brush.green = 255;
        brush.blue = 255;
    }
    bool parseXML(const QString &xmlContent);
    PTNET_ATTR getXML_net() const;

private:

    bool parseXML_Net(QXmlStreamReader &xml);
    bool parseXML_Page(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Place(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Transition(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Arc(QXmlStreamReader &xml, PAGE_ATTR &page);
    bool parseXML_Name(QXmlStreamReader &xml);
    bool parseXML_Graphics(QXmlStreamReader &xml);
    bool parseXML_Offset(QXmlStreamReader &xml);
    bool parseXML_Position(QXmlStreamReader &xml);
    bool parseXML_Color(QXmlStreamReader &xml);
    bool parseXML_InitialMarking(QXmlStreamReader &xml);
    bool parseXML_Inscription(QXmlStreamReader &xml);
    bool parseXML_Positions(QXmlStreamReader &xml);
    bool parseXML_ToolSpecific(QXmlStreamReader &xml);
    bool parseXML_Comment(QXmlStreamReader &xml);
    bool parseXML_Function(QXmlStreamReader &xml);
    bool parseXML_Action(QXmlStreamReader &xml);
    bool parseXML_Vector(QXmlStreamReader &xml, std::vector<double> &vec, std::string eleName);
    bool parseXML_Vector(QXmlStreamReader &xml, std::vector<int> &vec, std::string eleName);
    bool parseXML_Vector(QXmlStreamReader &xml, std::vector<std::string> &vec, std::string eleName);
    template<typename T>
    bool parseXML_bloVector(QXmlStreamReader &xml, std::vector<T> &vec, std::string eleName);

    QString getElementData(QXmlStreamReader& xml) const;

    QVariant v;
    QString id, name, source, target, ref, self_function, comment, show;//MassAction;
    int offsetx, offsety, x, y, capacity, rotation, weight;
    COLOR pen,brush;
    double initmark;
    QList<QPointF> points;

    PTNET_ATTR net;
    QList <PAGE_ATTR> pages;
};

#endif // XMLPARSER_H
