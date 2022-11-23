#include "editlineproperty.h"
#include "ui_editlineproperty.h"
#include "plot.h"

QColor newColor;
int newType;
int newWidth;
int graphNum;

editlineproperty::editlineproperty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editlineproperty)
{
    ui->setupUi(this);

    ui->frame->setAutoFillBackground(true);
    ui->frame->setPalette(QPalette(currentColor));

    initialComboBox();
}

editlineproperty::~editlineproperty()
{
    delete ui;
}

void editlineproperty::on_pushButton_3_clicked()
{
    showColor();
}

void editlineproperty::showColor()
{
    QColor c=QColorDialog::getColor(Qt::blue);
    if(c.isValid())
    {
        ui->frame->setPalette(QPalette(c));
        newColor=c;
    }
}

void editlineproperty::on_pushButton_2_clicked()
{
    this->close();
}
void editlineproperty::initialComboBox()
{
    for(int i=0;i<10;i++)
    {
        ui->comboBox->addItem(tr("%1").arg(i+1));
    }
    ui->comboBox_2->addItem(tr("NoScatterStyle"));
    ui->comboBox_2->addItem(tr("Cross"));
    ui->comboBox_2->addItem(tr("Plus"));
    ui->comboBox_2->addItem(tr("Circle"));
    ui->comboBox_2->addItem(tr("Disc"));
    ui->comboBox_2->addItem(tr("Square"));
    ui->comboBox_2->addItem(tr("Diamond"));
    ui->comboBox_2->addItem(tr("Star"));
    ui->comboBox_2->addItem(tr("Triangle"));

    ui->comboBox->setCurrentIndex(currentWidth-1);
    ui->comboBox_2->setCurrentIndex(currentType-1);
}
void editlineproperty::getNewData()
{
    newWidth=ui->comboBox->currentIndex()+1;
    newType=ui->comboBox_2->currentIndex()+1;
    graphNum=currentGraphNum;
}
void editlineproperty::on_pushButton_clicked()
{
    getNewData();

}
