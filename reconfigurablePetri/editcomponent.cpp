#include "editcomponent.h"
#include "ui_editcomponent.h"
#include"QLineEdit"
#include"QDebug"
editComponent::editComponent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editComponent)
{
    ui->setupUi(this);

}
void editComponent::on_buttonBox_accepted()
{
    QString componentName=ui->ComponentName->text();
    emit editComponentInfo(componentName);
}

editComponent::~editComponent()
{
    delete ui;
}


