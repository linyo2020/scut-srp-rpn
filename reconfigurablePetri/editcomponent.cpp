#include "editcomponent.h"
#include "ui_editcomponent.h"
#include"QLineEdit";
#include"QDebug"
editComponent::editComponent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editComponent)
{
    ui->setupUi(this);

}

editComponent::~editComponent()
{
    delete ui;
}

