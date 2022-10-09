#include "xmlparser.h"
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QString>

// return XML objects
PTNET_ATTR XmlParser::getXML_net() const
{
    return net;
}

/* begin parsing */
bool XmlParser::parseXML(const QString &xmlContent)
{
    QXmlStreamReader xml(xmlContent);

    bool isPnml=false;

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::ProcessingInstruction)
            continue;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "pnml")
            {
                isPnml=true;
                continue;
            }

            if (xml.name() == "net"&&isPnml==true)
            {
                if (xml.attributes().hasAttribute("id"))
                {
                    net.id = xml.attributes().value("id").toString();

                    if (!parseXML_Net(xml))
                        return false;

                    continue;
                }
            }
            else if(xml.name() == "net"&&isPnml==false)
            {
                QMessageBox::critical(0,"Warning!",QString("Not a pnml!"),
                                      QMessageBox::Ok,0,0);
                return false;
            }
         }
    }

    if (xml.hasError())
    {
        QMessageBox::critical(0,"Warning!",QString("XML-Pseudocode parsing error: ")+xml.errorString(),
                              QMessageBox::Ok,0,0);
        return false;
    }

    return true;
}

bool XmlParser::parseXML_Net(QXmlStreamReader &xml)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "net")
            break;

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                net.name = name;

                continue;
            }
            if (xml.name() == "page")
            {
                PAGE_ATTR page;

                if (xml.attributes().hasAttribute("id"))
                {
                    page.id = xml.attributes().value("id").toString();

                    if (!parseXML_Page(xml, page))
                        return false;

                    continue;
                }
            }
        }
    }

    return true;
}

bool XmlParser::parseXML_Page(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if ((token == QXmlStreamReader::EndElement) && (xml.name() == "page"))
        {
            net.pages << page;
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                page.name = name;

                continue;
            }
            if (xml.name() == "place")
            {
                if (xml.attributes().hasAttribute("id"))
                {
                    id = xml.attributes().value("id").toString();

                    if (!parseXML_Place(xml, page))
                        return false;

                    continue;
                }
            }
            if (xml.name() == "transition")
            {
                if (xml.attributes().hasAttribute("id"))
                {
                    id = xml.attributes().value("id").toString();

                    if (!parseXML_Transition(xml, page))
                        return false;

                    continue;
                }
            }
            if (xml.name() == "arc")
            {
                if (xml.attributes().hasAttribute("id")
                    && xml.attributes().hasAttribute("source")
                    && xml.attributes().hasAttribute("target"))
                 {
                    id = xml.attributes().value("id").toString();
                    source = xml.attributes().value("source").toString();
                    target = xml.attributes().value("target").toString();

                    if (!parseXML_Arc(xml, page))
                        return false;

                     continue;
                 }
            }
            continue;
        }
    }

    if (xml.hasError())
    {
        qDebug() << "XML-Pseudocode parsing error:- "<< xml.errorString();
        return false;
    }

    return true;

}

bool XmlParser::parseXML_Place(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "place")
        {
            PLACE_ATTR place;

            place.id = id;
            place.name = name;
            place.x = x;
            place.y = y;
            place.offsetx = offsetx;
            place.offsety = offsety;
            place.initmark = initmark;
            place.capacity = capacity;
            place.comment = comment;
            place.show = (show == "Y");
            QColor brushColor(brush.red,brush.green,brush.blue);
            QColor penColor(pen.red,pen.green,pen.blue);
            place.brushColor = brushColor;
            place.penColor = penColor;
            page.placeNodes << place;

            break;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                continue;

            }else if (xml.name() == "graphics")
             {
                if (!parseXML_Graphics(xml)) return false;
                continue;

             }else if (xml.name() == "initialMarking")
             {
                if (!parseXML_InitialMarking(xml)) return false;
                continue;
             }else if (xml.name() == "toolspecific")
               {
                    if (!parseXML_ToolSpecific(xml)) return false;
                    continue;
               }else if (xml.name() == "comment")
            {
                if(!parseXML_Comment(xml)) return false;
                continue;
            }else if (xml.name() == "color")
            {
                if(!parseXML_Color(xml)) return false;
                continue;
            }
        }
    }

    return true;
}

bool XmlParser::parseXML_Transition(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "transition")
        {
            TRANSITION_ATTR transition;

            transition.id = id;
            transition.name = name;
            transition.x = x;
            transition.y = y;
            transition.offsetx = offsetx;
            transition.offsety = offsety;
            transition.rotation = rotation;
            transition.self_function = self_function;
            //transition.MassAction=MassAction;
            transition.comment = comment;
            transition.show = (show == "Y");
            QColor brushColor(brush.red,brush.green,brush.blue);
            QColor penColor(pen.red,pen.green,pen.blue);
            transition.brushColor = brushColor;
            transition.penColor = penColor;
            page.transitionNodes << transition;

            break;
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "name")
            {
                if (!parseXML_Name(xml))
                    return false;

                continue;

            } else if (xml.name() == "graphics")
            {
                if (!parseXML_Graphics(xml))
                    return false;

                continue;

            }else if (xml.name() == "toolspecific")
            {
                if (!parseXML_ToolSpecific(xml))
                    return false;

                continue;
            }else if (xml.name() == "function")
            {
                if (!parseXML_Function(xml))
                    return false;
                continue;
            }//else if (xml.name() == "MassAction")
            //{
                //if (!parseXML_Function(xml))
                    //return false;
                //continue;
            //}
            else if (xml.name() == "comment")
            {
                if(!parseXML_Comment(xml))
                    return false;
                continue;
            }else if (xml.name() == "color")
            {
                if(!parseXML_Color(xml)) return false;
                continue;
            }
        }
    }

    return true;
}

bool XmlParser::parseXML_Arc(QXmlStreamReader &xml, PAGE_ATTR &page)
{
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "arc")
        {
            ARC_ATTR arc;

            arc.id = id;
            arc.source = source;
            arc.target = target;
            arc.points << points;
            arc.weight = weight;
            QColor brushColor(brush.red,brush.green,brush.blue);
            QColor penColor(pen.red,pen.green,pen.blue);
            arc.brushColor = brushColor;
            arc.penColor = penColor;
            points.clear();

            page.arcs << arc;
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "inscription")
            {
                if (!parseXML_Inscription(xml))
                    return false;

                continue;

            }
            if (xml.name() == "graphics")
            {
                if (!parseXML_Positions(xml))
                    return false;

                continue;

            }
            else if (xml.name() == "color")
            {
                if(!parseXML_Color(xml)) return false;
                continue;
            }
        }
    }

    return true;

}

bool XmlParser::parseXML_Vector(QXmlStreamReader &xml, std::vector<double> &vec, std::string eleName)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == QString::fromStdString(eleName))
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "double")
            {
                v.setValue(getElementData(xml));
                vec.push_back(v.toDouble());
                continue;
            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Vector(QXmlStreamReader &xml, std::vector<int> &vec, std::string eleName)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == QString::fromStdString(eleName))
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "int")
            {
                v.setValue(getElementData(xml));
                vec.push_back(v.toInt());
                continue;
            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Vector(QXmlStreamReader &xml, std::vector<std::string> &vec, std::string eleName)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == QString::fromStdString(eleName))
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "string")
            {
                vec.push_back(getElementData(xml).toStdString());
                continue;
            }
        }
    }
    return true;
}

template<typename T>
bool XmlParser::parseXML_bloVector(QXmlStreamReader &xml, std::vector<T> &vec, std::string eleName)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == QString::fromStdString(eleName))
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "row")
            {
                vec.resize(vec.size()+1);
                if(!parseXML_Vector(xml, vec[vec.size()-1], "row"))
                    return false;
                continue;
            }
        }
    }
    return true;
}



bool XmlParser::parseXML_Name(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "name")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                name = getElementData(xml);
                continue;

            } else if (xml.name() == "graphics")
            {
                if (!parseXML_Graphics(xml))
                    return false;

                continue;

            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Graphics(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "graphics")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "offset")
            {
                v.setValue(xml.attributes().value("x").toString());
                offsetx = v.toInt();
                v.setValue(xml.attributes().value("y").toString());
                offsety = v.toInt();
                    continue;
            }
            else if(xml.name() == "position")
            {
                v.setValue(xml.attributes().value("x").toString());
                x = v.toInt();
                v.setValue(xml.attributes().value("y").toString());
                y = v.toInt();
                    continue;
            }
       }
    }
    return true;
}

bool XmlParser::parseXML_Color(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "color")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "brush")
            {
                v.setValue(xml.attributes().value("red").toString());
                brush.red = v.toInt();
                v.setValue(xml.attributes().value("green").toString());
                brush.green = v.toInt();
                v.setValue(xml.attributes().value("blue").toString());
                brush.blue = v.toInt();
                    continue;
            }
            else if(xml.name() == "pen")
            {
                v.setValue(xml.attributes().value("red").toString());
                pen.red = v.toInt();
                v.setValue(xml.attributes().value("green").toString());
                pen.green = v.toInt();
                v.setValue(xml.attributes().value("blue").toString());
                pen.blue = v.toInt();
                    continue;
            }
       }
    }
    return true;
}

bool XmlParser::parseXML_InitialMarking(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "initialMarking")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                v.setValue(getElementData(xml));
                initmark = v.toDouble();

            }
            else if (xml.name() == "graphics")
            {
                if (!parseXML_Graphics(xml)) return false;
                continue;

            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Inscription(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "inscription")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                v.setValue(getElementData(xml));
                weight = v.toInt();
            }
        }
    }
    return true;

}

bool XmlParser::parseXML_Positions(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "graphics")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "position")
            {
                v.setValue(xml.attributes().value("x").toString());
                //x = v.toFloat();
                x=v.toInt();
                v.setValue(xml.attributes().value("y").toString());
                //y = v.toFloat();
                y=v.toInt();
                points<<QPointF(x,y);
                    continue;
            }
        }
    }
    return true;


}

bool XmlParser::parseXML_ToolSpecific(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "toolspecific")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "placeCapacity")
            {
                v.setValue(xml.attributes().value("capacity").toString());
                capacity = v.toInt();
                    continue;
            }
            else if(xml.name() == "rotation")
            {
                v.setValue(xml.attributes().value("degree").toString());
                rotation = v.toInt();
                    continue;
            }
       }
    }
    return true;

}

bool XmlParser::parseXML_Comment(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "comment")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                comment = getElementData(xml);
                continue;
            }else if(xml.name() == "show")
            {
                show = getElementData(xml);
                continue;
            }
        }
    }
    return true;
}

bool XmlParser::parseXML_Function(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "function")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                self_function = getElementData(xml);
                continue;

            }
        }
    }
    return true;
}
/*
bool XmlParser::parseXML_Action(QXmlStreamReader &xml)
{
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::EndElement && xml.name() == "MassAction")
        {
            break;
        }

        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "text")
            {
                MassAction = getElementData(xml);
                continue;

            }
        }
    }
    return true;
}*/
QString XmlParser::getElementData(QXmlStreamReader &xml) const
{
    /* We need a start element, like <name> */
    if (xml.tokenType() != QXmlStreamReader::StartElement)
    {
        return "";
    }

    xml.readNext();

    /* This elements needs to contain Characters so we know it's
     * actually data, if it's not we'll leave.     */
    if (xml.tokenType() != QXmlStreamReader::Characters)
    {
        return "";
    }

    /* Now we can return the data. */
    return xml.text().toString();
}

