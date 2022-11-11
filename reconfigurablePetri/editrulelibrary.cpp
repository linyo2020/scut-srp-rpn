#include "editrulelibrary.h"
#include "ui_editrulelibrary.h"

editRuleLibrary::editRuleLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRuleLibrary)
{
    ui->setupUi(this);
}

editRuleLibrary::~editRuleLibrary()
{
    delete ui;
}

void editRuleLibrary::on_comboBox_activated(const QString &arg1)
{

}
