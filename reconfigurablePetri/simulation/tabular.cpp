#include "tabular.h"
#include "ui_tabular.h"
#include "plot.h"

Tabular::Tabular(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tabular)
{
    ui->setupUi(this);

    setWindowTitle(QString("Tabular"));

    //initialTablev();

}

Tabular::~Tabular()
{
    delete ui;
}

void Tabular::addNewTableItem()
{
    /*
    for(int i=0;i<1000;i++)
    {
            double x=i/(double)100;
            double y0=sin(i/(double)100);
            double y1=0.5*sin(i/(double)100);
            double y2=cos(i/(double)100);
            double y3=0.5*cos(2*i/(double)100);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(tr("%1").arg(x)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(y0)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(tr("%1").arg(y1)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(tr("%1").arg(y2)));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(tr("%1").arg(y3)));
    }
    */
}

void Tabular::initialTablev()
{
    ui->tableWidget->clear();
    int count1=namevector[PlotId].size();
    int count2=datavv[PlotId].size();
    ui->tableWidget->setColumnCount(count1);
    ui->tableWidget->setRowCount(count2);
    QStringList header;
    for(int i=0;i<count1;i++)
    {
        header<<namevector[PlotId][i];
    }
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(int i=0;i<count2;i++)
    {
        QVector<double> temp=datavv[PlotId][i];
        for(int j=0;j<count1;j++)
        {
            double tempd=temp[j];
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(tr("%1").arg(tempd)));
        }
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(248,248,225);}");
}

