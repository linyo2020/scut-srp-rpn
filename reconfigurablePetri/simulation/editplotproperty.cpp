#include "editplotproperty.h"
#include "ui_editplotproperty.h"
#include"plot.h"

extern QColor newColor;
extern int newType;
extern int newWidth;
extern int graphNum;

editplotproperty::editplotproperty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editplotproperty)
{
    ui->setupUi(this);

    setWindowTitle(QString("Edit curve properties"));

    ui->frame->setAutoFillBackground(true);
    ui->frame->setPalette(QPalette(currentColor));
    newColor=currentColor;
    initialComboBox();
}

editplotproperty::~editplotproperty()
{
    delete ui;
}

void editplotproperty::on_pushButton_clicked()
{
    getNewData();
    Plot *ptr=(Plot*)parentWidget();
    ptr->updatePlot(graphNum,newColor,newType,newWidth);
    this->close();
}

void editplotproperty::on_pushButton_2_clicked()
{
    this->close();
}

void editplotproperty::on_pushButton_3_clicked()
{
    showColor();
}
void editplotproperty::showColor()
{
    QColor c=QColorDialog::getColor(Qt::blue);
    if(c.isValid())
    {
        ui->frame->setPalette(QPalette(c));
        newColor=c;
    }
}
void editplotproperty::initialComboBox()
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
void editplotproperty::getNewData()
{
    newWidth=ui->comboBox->currentIndex()+1;
    newType=ui->comboBox_2->currentIndex()+1;
    graphNum=currentGraphNum;
}
