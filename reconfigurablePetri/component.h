#ifndef COMPONENT_H
#define COMPONENT_H
//have Todo tag
#include <QObject>
//this class defines a base unit of component library
#include"defs.h"
#include"ptnet.h"

class Component
{
public:
    Component();

    //The unique identity of the component unit
    QString Component_id;

    //The name displayed on the UI
    QString label;

    //Todo
    //Identifies the type of the component, such as id= A1xxxxx, its type=A
    //need to determine the variable type
    int Component_type;


    PTNet mynet;

    int getComponent_type() const;
    void setComponent_type(int type);//slots//UI
    QString getLabel() const;
    void setLabel(const QString &value);//slots//UI

    //variable :net need to connect,source ,target
    Component merge(PTNet otherNet, QString thisNet_port,QString otherNet_port);
    //todo
    //放在UI？
    //void deleteComponent();
    //void AddComponent();
    //todo
    bool isport();
    bool check();




};

#endif // COMPONENT_H
