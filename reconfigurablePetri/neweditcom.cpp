#include "neweditcom.h"
#include"QCoreApplication"
#include"QLine"
neweditcom::neweditcom(QWidget *parent) : QDialog(parent)
{
    line_type=new QLineEdit(this);
    //mybutton=new QPushButton(this);
    this->resize(500,500);
    line_type->move(150,150);
    line_type->setPlaceholderText("输入type");
    QLineEdit*l=new QLineEdit(this);
    l->move(50,50);
    l->setPlaceholderText("按回车");
    //mybutton->move(250,250);
    //mybutton->setText("确认保存");

    //connect(mybutton,&QPushButton::clicked,this,&neweditcom::editFinished);
    //connect(mybutton,&QPushButton::clicked,this,[=](){line_type->setText("");});
    connect(line_type,&QLineEdit::returnPressed,this,&neweditcom::typeedit);
    //connect(mybutton,&QPushButton::clicked,this,&neweditcom::typeedit);
}


void neweditcom::typeedit()
{
    this->type=line_type->text();
    qDebug()<<"succeed edit type in the line";
    QString s=line_type->text();
    emit typechange(s);
    emit editFinished();
    line_type->setText("");
}

neweditcom::~neweditcom()
{
    delete this->line_type;
}
