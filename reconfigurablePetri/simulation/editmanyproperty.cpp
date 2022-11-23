#include "editmanyproperty.h"
#include "ui_editmanyproperty.h"
#include "plot.h"

editmanyproperty::editmanyproperty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editmanyproperty)
{
    ui->setupUi(this);

    setWindowTitle(QString("Result viewer properties"));

    initialComboBox();

    Plot *ptr=(Plot*)parentWidget();
    if(ptr->getTitleShoworNot())
    {
        ui->checkBox_3->setCheckState(Qt::Checked);
        ui->lineEdit->setText(ptr->getTitle());
        ui->lineEdit->setEnabled(true);
    }
    else
    {
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->lineEdit->setEnabled(false);
    }
    ui->lineEdit_2->setText(ptr->getXlabel());
    ui->lineEdit_3->setText(ptr->getYlabel());
    if(ptr->getLegendShoworNot())
    {
        ui->checkBox->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox->setCheckState(Qt::Unchecked);
    }
    if(ptr->getLineStyle())
    {
        ui->checkBox_2->setCheckState(Qt::Checked);
    }
    else
    {
        ui->checkBox_2->setCheckState(Qt::Checked);
    }
    ui->comboBox->setCurrentIndex(ptr->getLegendPositionH());
    ui->comboBox_2->setCurrentIndex(ptr->getLegendPositionV());
    ui->comboBox_3->setCurrentIndex(10);//默认不变
    ui->comboBox_4->setCurrentIndex(9);
}

editmanyproperty::~editmanyproperty()
{
    delete ui;
}

void editmanyproperty::on_pushButton_2_clicked()
{
    this->close();
}
void editmanyproperty::initialComboBox()
{
    ui->comboBox->addItem(tr("Left"));
    ui->comboBox->addItem(tr("Center"));
    ui->comboBox->addItem(tr("Right"));
    ui->comboBox_2->addItem(tr("Top"));
    ui->comboBox_2->addItem(tr("Center"));
    ui->comboBox_2->addItem(tr("Bottom"));

    for(int i=0;i<10;i++)
    {
        ui->comboBox_3->addItem(tr("%1").arg(i+1));
    }
    ui->comboBox_3->addItem(tr("don't change"));

    ui->comboBox_4->addItem(tr("NoScatterStyle"));
    ui->comboBox_4->addItem(tr("Cross"));
    ui->comboBox_4->addItem(tr("Plus"));
    ui->comboBox_4->addItem(tr("Circle"));
    ui->comboBox_4->addItem(tr("Disc"));
    ui->comboBox_4->addItem(tr("Square"));
    ui->comboBox_4->addItem(tr("Diamond"));
    ui->comboBox_4->addItem(tr("Star"));
    ui->comboBox_4->addItem(tr("Triangle"));
    ui->comboBox_4->addItem(tr("don't change"));
}

void editmanyproperty::on_pushButton_clicked()
{
    int newShowTitleorNot;
    QString newTitle;
    if(ui->checkBox_3->checkState()==Qt::Checked)
    {
        newShowTitleorNot=1;
        newTitle=ui->lineEdit->text();
    }
    else
    {
        newShowTitleorNot=0;
        newTitle="";
    }
    //QString newTitle=ui->lineEdit->text();
    QString newXTitle=ui->lineEdit_2->text();
    QString newYTitle=ui->lineEdit_3->text();
    int newShowLegendorNot;
    if(ui->checkBox->checkState()==Qt::Checked)
    {
        newShowLegendorNot=1;
    }
    else
    {
        newShowLegendorNot=0;
    }
    int newPositionH=ui->comboBox->currentIndex();
    int newPositionV=ui->comboBox_2->currentIndex();
    int newLineStyle;
    if(ui->checkBox_2->checkState()==Qt::Checked)
    {
        newLineStyle=1;
    }
    else
    {
        newLineStyle=0;
    }
    int newWidth=ui->comboBox_3->currentIndex();
    int newType=ui->comboBox_4->currentIndex();
    Plot *ptr=(Plot*)parentWidget();
    ptr->updateProperty(newShowTitleorNot,newTitle,newXTitle,newYTitle,newShowLegendorNot,newPositionH,newPositionV,newLineStyle,newWidth,newType);
    this->close();
}

void editmanyproperty::on_checkBox_3_stateChanged(int arg1)
{
    if(ui->checkBox_3->checkState()!=Qt::Checked)
    {
        ui->lineEdit->setEnabled(false);
    }
    else
    {
        ui->lineEdit->setEnabled(true);
    }
}
