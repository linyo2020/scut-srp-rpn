#include "Simulation/savediffcsv.h"
#include "ui_savediffcsv.h"
#include"plot.h"

QString fileName;

savediffcsv::savediffcsv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::savediffcsv)
{
    ui->setupUi(this);

    setWindowTitle(QString("Export properties"));

    ui->comboBox->addItem(tr("colon"));
    ui->comboBox->addItem(tr("comma"));
    ui->comboBox->addItem(tr("semicolon"));
    ui->comboBox->addItem(tr("tabulator"));
    ui->comboBox->setCurrentIndex(1);
}

savediffcsv::~savediffcsv()
{
    delete ui;
}

void savediffcsv::on_pushButton_clicked()
{
    fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),tr("Files (*.csv)"));
    if(fileName.isEmpty())
        return;
    if(QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".csv");
    ui->lineEdit->setText(fileName);
}

void savediffcsv::on_pushButton_3_clicked()
{
    this->close();
}

void savediffcsv::on_pushButton_2_clicked()
{
    if(ui->comboBox->currentIndex()==0)
    {
        if(QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(this,"Operation failed!","Can't open the file!");
            return;
        }
        QTextStream out(&file);
        QVector<QString>::iterator it1;
        for(it1=namevector[PlotId].begin();it1!=namevector[PlotId].end()-1;it1++)
        {
            out<<tr("%1 :").arg(*it1);
        }
        out<<tr("%1").arg(*it1);
        out<<'\n';
        QVector<QVector<double>>::iterator it2;
        int count=namevector[PlotId].size();
        for(it2=datavv[PlotId].begin();it2!=datavv[PlotId].end();it2++)
        {
            for(int j=0;j<count-1;j++)
            {
                out<<tr("%1 :").arg(*(it2->begin()+j));
            }
            out<<tr("%1").arg(*(it2->begin()+count-1));
            out<<'\n';
        }
        QMessageBox::information(this,tr("Operation succeed!"),tr("File is saved in %1!").arg(fileName),tr("OK"));
        file.close();
    }
    if(ui->comboBox->currentIndex()==1)
    {
        if(QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(this,"Operation failed!","Can't open the file!");
            return;
        }
        QTextStream out(&file);
        QVector<QString>::iterator it1;
        for(it1=namevector[PlotId].begin();it1!=namevector[PlotId].end()-1;it1++)
        {
            out<<tr("%1 ,").arg(*it1);
        }
        out<<tr("%1").arg(*it1);
        out<<'\n';
        QVector<QVector<double>>::iterator it2;
        int count=namevector[PlotId].size();
        for(it2=datavv[PlotId].begin();it2!=datavv[PlotId].end();it2++)
        {
            for(int j=0;j<count-1;j++)
            {
                out<<tr("%1 ,").arg(*(it2->begin()+j));
            }
            out<<tr("%1").arg(*(it2->begin()+count-1));
            out<<'\n';
        }
        QMessageBox::information(this,tr("Operation succeed!"),tr("File is saved in %1!").arg(fileName),tr("OK"));
        file.close();
    }
    if(ui->comboBox->currentIndex()==2)
    {
        if(QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(this,"Operation failed!","Can't open the file!");
            return;
        }
        QTextStream out(&file);
        QVector<QString>::iterator it1;
        for(it1=namevector[PlotId].begin();it1!=namevector[PlotId].end()-1;it1++)
        {
            out<<tr("%1 ;").arg(*it1);
        }
        out<<tr("%1").arg(*it1);
        out<<'\n';
        QVector<QVector<double>>::iterator it2;
        int count=namevector[PlotId].size();
        for(it2=datavv[PlotId].begin();it2!=datavv[PlotId].end();it2++)
        {
            for(int j=0;j<count-1;j++)
            {
                out<<tr("%1 ;").arg(*(it2->begin()+j));
            }
            out<<tr("%1").arg(*(it2->begin()+count-1));
            out<<'\n';
        }
        QMessageBox::information(this,tr("Operation succeed!"),tr("File is saved in %1!").arg(fileName),tr("OK"));
        file.close();
    }
    if(ui->comboBox->currentIndex()==3)
    {
        if(QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".csv");
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(this,"Operation failed!","Can't open the file!");
            return;
        }
        QTextStream out(&file);
        QVector<QString>::iterator it1;
        for(it1=namevector[PlotId].begin();it1!=namevector[PlotId].end()-1;it1++)
        {
            //out<<tr("%1").arg(*it1)<<'\t';
            out<<tr("%1").arg(*it1)<<"        ";
        }
        out<<tr("%1").arg(*it1);
        out<<'\n';
        QVector<QVector<double>>::iterator it2;
        int count=namevector[PlotId].size();
        for(it2=datavv[PlotId].begin();it2!=datavv[PlotId].end();it2++)
        {
            for(int j=0;j<count-1;j++)
            {
                //out<<tr("%1").arg(*(it2->begin()+j))<<'\t';
                out<<tr("%1").arg(*(it2->begin()+j))<<"        ";
            }
            out<<tr("%1").arg(*(it2->begin()+count-1));
            out<<'\n';
        }
        QMessageBox::information(this,tr("Operation succeed!"),tr("File is saved in %1!").arg(fileName),tr("OK"));
        file.close();
    }
    this->close();
}
