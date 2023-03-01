#include "plot.h"
#include "ui_plot.h"
#include<iostream>
#include <QThread>
#include "calculate.h"
#include "simulationcontroller.h"
using namespace std;

map<QString,QVector<QString>> namevector;
map<QString,QVector<QVector<double>>> datavv;
map<QString,vector<FUNCTIONDEF>> e_vFunDef;
map<QString,map<string,double>> e_mInputVaraible2Value;
//QVector<QColor> colorv;
//QVector<int> lineType;
//QVector<int> lineWidth;

int currentGraphNum;
QColor currentColor;
int currentType;
int currentWidth;
int g_run=0;
//int legendpositionH;
//int legendpositionV;
//int lineStyle;
//int legendShoworNot;
//int titleShoworNot;

Plot::Plot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plot)
{
    //srand(QDateTime::currentDateTime().toTime_t());
    setWindowTitle(QString("Simulation"));
    count=0;
    flag=0;
    legendpositionH=2;
    legendpositionV=0;
    lineStyle=1;
    legendShoworNot=1;
    titleShoworNot=1;
    m_mInputVaraible2Value.clear();
    m_vFunDef.clear();
    lineType.clear();
    colorv.clear();
    lineWidth.clear();
    ///////////////////namevector.clear();
    ////////////////////datavv.clear();
    /////////////InitializeNet();//初始化
    legendFont = font();
    legendFont.setPointSize(10);
    //initialVector();
    /////////////for(unsigned i=0;i<m_vFunDef.size();i++)
    /////////{
        /////////////namevector.push_back(QString::fromStdString(m_vFunDef[i].m_sDifferentialName));
    ///////////}

    ui->setupUi(this);

    ui->checkBox->setCheckState(Qt::Checked);
    ui->label_9->setText(QString("0"));
    ui->lineEdit->setText(QString("0"));
    ui->lineEdit_2->setText(QString("10"));
    ui->lineEdit_5->setText(QString("0.1"));
    ui->comboBox_2->addItem(QString("Runge-Kutta"));
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(2);
    ///////////int rowcount=1;
    ///////////for(int i=0;i<namevector.size();i++)
    ///////////{
    ///////////    ui->tableWidget->setRowCount(rowcount);
    ///////////    QTableWidgetItem *check=new QTableWidgetItem();
    ///////////    check->setCheckState(Qt::Checked);
    ///////////    ui->tableWidget->setItem(i,0,check);
    ///////////    ui->tableWidget->setItem(i,1,new QTableWidgetItem(namevector[i]));
    ///////////    rowcount++;
    ///////////}
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tableWidget->setColumnWidth(0,24);
    //ui->tableWidget->setColumnWidth(1,176);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");
    ui->progressBar->setRange(0,100);

    ui->comboBox->addItem(tr("Image Export"));
    ui->comboBox->addItem(tr("Image Export PDF"));
    ui->comboBox->addItem(tr("CSV Export"));
    ui->comboBox->addItem(tr("ODE Export"));
    ui->comboBox->addItem(tr("Printer"));

    //initialTablev();
    //initialColor();
    //initialLineType();
    //initialLineWidth();

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    //ui->customPlot->xAxis->setRange(-50, 50);
    //ui->customPlot->yAxis->setRange(-3, 3);
    ui->customPlot->axisRect()->setupFullAxesBox();

    ui->customPlot->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(ui->customPlot, " ", QFont("sans", 17, QFont::Bold));
    ui->customPlot->plotLayout()->addElement(0, 0, title);

    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel("Concentration");
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->rescaleAxes(true);
    //ui->customPlot->legend->setVisible(false);

    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignRight|Qt::AlignTop);
    //ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignBottom);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems);

    //addAllGraph();
    connect(ui->customPlot, &QCustomPlot::selectionChangedByUser, this, &Plot::selectionChanged);
    //connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(updateGraph()));
    ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->customPlot, &QWidget::customContextMenuRequested, this, &Plot::contextMenuRequest);
    connect(ui->Start, &QAbstractButton::clicked, this, &Plot::startSimulation);


    //////for(unsigned i=0;i<m_vFunDef.size();i++)
    //////{
    //////    qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<"  "<<QString::fromStdString(m_vFunDef[i].m_sFunctionExp);
    //////}
    //////map<string,double>::iterator it;
    //////for(it=m_mInputVaraible2Value.begin();it!=m_mInputVaraible2Value.end();it++)
    //////{
    //////    qDebug()<<QString::fromStdString(it->first)<<"  "<<it->second;
    //////}
    ui->tableWidget->hide();
    ui->checkBox_2->setDisabled(true);
}

Plot::~Plot()
{
    delete ui;
}
void Plot::setPlotId(QString id)
{
    PlotId=id;
    ui->label_5->setText(PlotId);
    namevector[PlotId].clear();
    datavv[PlotId].clear();
    InitializeNet();
    for(unsigned i=0;i<m_vFunDef.size();i++)
    {
        namevector[PlotId].push_back(QString::fromStdString(m_vFunDef[i].m_sDifferentialName));
    }
    int rowcount=1;
    for(int i=0;i<namevector[PlotId].size();i++)
    {
        ui->tableWidget->setRowCount(rowcount);
        QTableWidgetItem *check=new QTableWidgetItem();
        check->setCheckState(Qt::Checked);
        ui->tableWidget->setItem(i,0,check);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(namevector[PlotId][i]));
        rowcount++;
    }
    connect(ui->tableWidget,&QTableWidget::cellChanged,this,&Plot::updateGraph);
}
void Plot::updateUi(double x,QString y)
{
    ui->progressBar->setValue(x);
    ui->label_9->setText(y);
}
void Plot::startSimulation()
{
    ui->customPlot->clearGraphs();
    count=0;
    //qDebug()<<ui->customPlot->graphCount();
    double l_start=ui->lineEdit->text().toDouble();
    double l_end=ui->lineEdit_2->text().toDouble();
    double dh=ui->lineEdit_5->text().toDouble();
    //判断步长是否合理
    if(dh==0)
    {
        QMessageBox::about(this,tr("Error"),tr("Please change the step size!"));
        return;
    }
    //启动子线程
    g_run = 1;
//    Calculate *p = new Calculate(this);
//    p->start();
//    bool suc=p->run(PlotId,l_start,l_end,dh,ui->checkBox->checkState()==Qt::Checked);
      SimulationController*p = new SimulationController(m_com_list,m_ruleManager,this,l_start,l_end,dh);
      p->start();
      bool suc=true;

    if(suc==true)
    {
        ui->customPlot->rescaleAxes(true);
        ui->customPlot->replot();
        ui->progressBar->setValue(100);
        ui->tableWidget->show();
        ui->checkBox_2->setEnabled(true);
        ui->checkBox_2->setCheckState(Qt::Checked);
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
        }
    }
    else
    {
        QMessageBox::about(this,tr("Compile Error"),tr("Please check the input"));
    }
//    p->destroyed();
    p->destroyed();
//    Component*l_Component=nullptr;
//    QList<PLACE_ATTR> l_placeList;
//    QVector<Component*>l_vComponent = com_list->getComponentList();
//    for( int i = 0; i<l_vComponent.size();i++)
//    {
//        qDebug()<<"this is thread :"<<QThread::currentThreadId();
//        l_Component=l_vComponent[i];
//        ///目前无法获得步长数据！！！
//        l_vComponent[i]->setStep(0.5);
//        qDebug()<<"this is the "<<i<<"component :"<<l_vComponent[i]->getID()<<", and step is "<<l_vComponent[i]->getStep();
//        l_placeList=l_vComponent[i]->getPlace_ATTRList();
//        for( int i = 0; i<l_placeList.size();i++)
//        {
//             qDebug()<<"place name: "<<l_placeList[i].name<<"and token : "<<l_placeList[i].initmark;
//        }
//    }
}
void Plot::initialVector()
{
    //namevector.clear();
    //datavv.clear();
}/*
void Plot::on_pushButton_clicked()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
        ui->customPlot->graph(i)->setVisible(true);
    }
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}
void Plot::on_pushButton_2_clicked()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        ui->customPlot->graph(i)->setVisible(false);
    }
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}*/
void Plot::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->checkState()==Qt::Checked)
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
            ui->customPlot->graph(i)->setVisible(true);
            ui->customPlot->legend->item(i)->setVisible(true);
        }
        ui->customPlot->rescaleAxes(true);
        ui->customPlot->replot();
        //ui->checkBox_2->setCheckState(Qt::Unchecked);
    }
    else if(ui->checkBox_2->checkState()==Qt::PartiallyChecked)
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
            ui->customPlot->graph(i)->setVisible(true);
            ui->customPlot->legend->item(i)->setVisible(true);
        }
        ui->customPlot->rescaleAxes(true);
        ui->customPlot->replot();
        ui->checkBox_2->setCheckState(Qt::Checked);
    }
    else if(ui->checkBox_2->checkState()==Qt::Unchecked)
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
            ui->customPlot->graph(i)->setVisible(false);
            ui->customPlot->legend->item(i)->setVisible(false);
        }
        ui->customPlot->rescaleAxes(true);
        ui->customPlot->replot();
        //ui->checkBox_2->setCheckState(Qt::Checked);
    }
}
/*
void Plot::initialVector()
{
    namevector.clear();
    datavv.clear();
    namevector.push_back("x");
    namevector.push_back("y=sin(x)");
    namevector.push_back("y=0.5sin(x)");
    namevector.push_back("y=cos(x)");
    namevector.push_back("0.5cos(2x)");
    for(int i=0;i<1000;i++)
    {
        QVector<double> temp;
        temp.push_back(i/(double)100);
        temp.push_back(sin(i/(double)100));
        temp.push_back(0.5*sin(i/(double)100));
        temp.push_back(cos(i/(double)100));
        temp.push_back(0.5*cos(2*i/(double)100));
        datavv.push_back(temp);
    }
}
*/
/*
void Plot::initialTablev()
{
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(2);
    int l_count=namevector.size();
    ui->tableWidget->setRowCount(l_count);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<l_count;i++)
    {
        QTableWidgetItem *check=new QTableWidgetItem();
        check->setCheckState(Qt::Checked);
        ui->tableWidget->setItem(i,0,check);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(tr("%1").arg(namevector[i])));
    }
    //ui->tableWidget->setColumnWidth(0,5);
    ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //璁剧疆閫変腑鑳屾櫙鑹?
}
*/
/*
void Plot::initialTablev()
{
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnCount(2);
    int l_count=namevector.size();
    ui->tableWidget->setRowCount(l_count-1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=1;i<l_count;i++)
    {
        QTableWidgetItem *check=new QTableWidgetItem();
        check->setCheckState(Qt::Checked);
        ui->tableWidget->setItem(i-1,0,check);
        QVector<QString>::iterator it1;
        it1=namevector.begin()+i;
        QString name=*it1;
        //QString name=QString::fromStdString(m_vFunDef[i].m_sDifferentialName+'='+m_vFunDef[i].m_sFunctionExp);
        ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(tr("%1").arg(name)));
    }
    ui->tableWidget->setColumnWidth(0,5);
    ui->tableWidget->setColumnWidth(1,90);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;"); //璁剧疆閫変腑鑳屾櫙鑹?
}
*/
void Plot::addNewGraphv(int n)
{
    ui->customPlot->graph(n)->setVisible(true);
    ui->customPlot->replot();
}
/*
void Plot::addNewGraphv(int n)
{
    QVector<QString>::iterator it1;
    it1=namevector.begin()+n;
    QString name=*it1;
    QVector<double> x,y;
    QVector<QVector<double>>::iterator it2;
    for(it2=datavv.begin();it2!=datavv.end();it2++)
    {
        double xtemp,ytemp;
        xtemp=*it2->begin();
        ytemp=*(it2->begin()+n);
        x.push_back(xtemp);
        y.push_back(ytemp);
    }
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setName(name);
    ui->customPlot->graph()->setData(x, y);
    ui->customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(lineStyle));
    //if (rand()%100 > 50)
    //  ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
    int typeTemp=lineType[n-1];
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(typeTemp)));
    QPen graphPen;
    QColor temp=colorv[n-1];
    graphPen.setColor(temp);
    //graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    //graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    //graphPen.setWidthF(2);
    int widthTemp=lineWidth[n-1];
    graphPen.setWidthF(widthTemp);
    ui->customPlot->graph()->setPen(graphPen);
    ui->customPlot->replot();
}
*/
void Plot::addAllGraph()
{
    for(int i=0;i<namevector[PlotId].size();i++)
    {
        addNewGraphv(i);
    }
    ui->customPlot->replot();
}
/*
void Plot::addAllGraph()
{
    int count=namevector.size();
    for(int i=1;i<count;i++)
    {
        addNewGraphv(i);
    }
    ui->customPlot->replot();
}
*/
void Plot::saveCSVv()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),tr("Files (*.csv)"));
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::information(this,"operation failed!","can't open the file!");
        return;
    }
    else
    {
    QTextStream out(&file);
    QVector<QString>::iterator it1;
    for(it1=namevector[PlotId].begin();it1!=namevector[PlotId].end();it1++)
    {
        out<<tr("%1 ,").arg(*it1);
    }
    out<<'\n';
    QVector<QVector<double>>::iterator it2;
    int count=namevector[PlotId].size();
    for(it2=datavv[PlotId].begin();it2!=datavv[PlotId].end();it2++)
    {
        for(int j=0;j<count;j++)
        {
            out<<tr("%1 ,").arg(*(it2->begin()+j));
        }
        out<<'\n';
    }
    QMessageBox::information(this,tr("operation succeed!"),tr("file is saved in%1!").arg(fileName),tr("OK"));
    file.close();
    }
}

void Plot::updateGraph()
{
    int count=0;
    vector<bool> listCheck=getTableChecked();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->customPlot->graph(i)->setVisible(false);
        ui->customPlot->legend->item(i)->setVisible(false);
    }
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        if(listCheck[i]==true)
        {
            ui->customPlot->graph(i)->setVisible(true);
            ui->customPlot->legend->item(i)->setVisible(true);
            count++;
        }
    }
    if(count==0)
    {
        ui->checkBox_2->setCheckState(Qt::Unchecked);
    }
    else if(count!=listCheck.size())
    {
        ui->checkBox_2->setCheckState(Qt::PartiallyChecked);
    }
    else if(count==listCheck.size())
    {
        ui->checkBox_2->setCheckState(Qt::Checked);
    }
    ui->customPlot->rescaleAxes(true);
    ui->customPlot->replot();
}
/*
void Plot::updateGraph()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    QVector<bool> listCheck=getTableChecked();
    QVector<bool>::iterator it;
    int n=0;
    for(it=listCheck.begin();it!=listCheck.end();it++)
    {
        if(*it==1)
            addNewGraphv(n);
        n++;
    }
}
*/
void Plot::addGraph(string s)
{
    colorv.push_back(QColor::fromHsl(rand()%360,rand()%256,rand()%200));
    lineType.push_back(1);
    lineWidth.push_back(1);
    pen.setColor(colorv[count]);
    pen.setWidthF(1);
    ui->customPlot->addGraph();
    ui->customPlot->graph(count)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(1)));
    ui->customPlot->graph(count)->setPen(pen);
    ui->customPlot->graph(count)->setName(QString::fromStdString(s));
    count++;
}
void Plot::addData(int i,QVector<double>& x,QVector<double>& y)
{
    ui->customPlot->graph(i)->addData(x,y);
}

void Plot::InitializeNet()
{
    m_mInputVaraible2Value=e_mInputVaraible2Value[PlotId];
    m_vFunDef=e_vFunDef[PlotId];
}
/*
void Plot::InitializeNet()
{
    m_mInputVaraible2Value["y1"] = 0;
    m_mInputVaraible2Value["y2"] = 1;
    m_mInputVaraible2Value["y3"] = 1;
    m_mInputVaraible2Value["y4"] = 0.5;
    FUNCTIONDEF m_FunDef2;
    m_FunDef2.m_sDifferentialName="y2";
    m_FunDef2.m_sFunctionExp = "-y1*y3";
    m_vFunDef.push_back(m_FunDef2);
    FUNCTIONDEF m_FunDef1;
    m_FunDef1.m_sDifferentialName="y1";
    m_FunDef1.m_sFunctionExp = "y2*y3";
    m_vFunDef.push_back(m_FunDef1);
    FUNCTIONDEF m_FunDef3;
    m_FunDef3.m_sDifferentialName="y3";
    m_FunDef3.m_sFunctionExp = "-0.51*y1*y2";
    m_vFunDef.push_back(m_FunDef3);
}*/
/*
bool Plot::on_Start_clicked()
{
    datavv.clear();
    QTime start_time=QTime::currentTime();
    QTime end_time=QTime::currentTime();
    double l_start=ui->lineEdit->text().toDouble();
    double l_end=ui->lineEdit_2->text().toDouble();
    double dh=ui->lineEdit_5->text().toDouble();
    //ui->progressBar->setRange(0,100);
    //m_mInputVaraible2Value.clear();
    //m_vFunDef.clear();
    //InitializeNet();
    ODEsolver l_solver;
    l_solver.setMap(m_mInputVaraible2Value);
    l_solver.setVector(m_vFunDef);
    //initialVector();
    //for(unsigned i=0;i<m_vFunDef.size();i++)
    //{
    //    namevector.push_back(QString::fromStdString(m_vFunDef[i].m_sDifferentialName);
    //}
    bool l_check=l_solver.parser();
    if(l_check==false)
    {
        QMessageBox::about(this,tr("Compile Error"),tr("Please check the input"));
        return false;
    }
    else
    {
        map<string,double> name2value;name2value.clear();
        vector<double>receiver;
        count=0;
        ui->customPlot->clearGraphs();
        QVector<double>temp; //temp中存放初始值，存放顺序为m_vFunDef中每个位置的先后顺序
        for(unsigned i=0;i<m_vFunDef.size();i++)
        {
            addGraph(m_vFunDef[i].m_sDifferentialName);
            QVector<double>temp1;
            temp1.push_back(l_start);
            QVector<double>temp2;
            temp2.push_back(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]);
            temp.push_back(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]);
            addData(i,temp1,temp2);
        }
        datavv.push_back(temp);
        double dx;
        if(ui->checkBox->checkState()==Qt::Checked)
        {
            for(dx=l_start;dx+dh<=l_end||dx+dh-l_end<0.000000000001;dx=dx+dh)
            {
                qDebug()<<"NOW dx="<<dx;
                //for(unsigned i=0;i<m_vFunDef.size();i++)
                //{
                //    qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<"  "<<QString::fromStdString(m_vFunDef[i].m_sFunctionExp);
                //}
                ODEsolver ode1=l_solver;//此时l_solver仍为上一步
                receiver=ode1.evaluate(dx,dh,true);
                //for(int i=0;i<m_vFunDef.size();i++)
                //{
                //    qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" "<<receiver[i];
                //}
                double record_dh=dh;
                while(true)//重复至每一步都无小于0出现
                {
                    int flag=1;
                    double min_step=record_dh;
                    double pre_step=0;
                    for(int i=0;i<receiver.size();i++)
                    {
                        int flag2=1;//判断是否有次数用尽但仍未到0
                        double step=0.5*record_dh;
                        double l_wall=0.0;
                        double r_wall=record_dh;
                        if(receiver[i]<0)//检测一个receiver若小于0，则重复至求得为0时步长
                        {
                            flag=0;
                            ODEsolver ode4=l_solver;
                            double record_step=0;
                            receiver[i]=(ode4.evaluate(dx,step,true))[i];
                            int count=0;
                            while(receiver[i]<-0.000000000001||receiver[i]>0.000000000001)
                            {
                                ODEsolver ode2=l_solver;
                                if(receiver[i]>0.000000000001)
                                {
                                    l_wall=step;
                                    step=(step+r_wall)/2;
                                    record_step=step;
                                }
                                else if(receiver[i]<-0.000000000001)
                                {
                                    r_wall=step;
                                    step=(l_wall+step)/2;
                                }
                                receiver[i]=(ode2.evaluate(dx,step,true))[i];
                                //qDebug()<<count<<" "<<receiver[i];
                                count++;
                                if(count==100)
                                {
                                    flag2=0;
                                    break;
                                }
                            }
                        }
                        if(flag2==0)
                            min_step=min(min_step,pre_step);
                        else min_step=min(min_step,step);
                    }
                    if(flag==1)
                    {
                        break;
                    }
                    qDebug()<<"IN STEP"<<min_step;
                    receiver=l_solver.evaluate(dx,min_step,true);

                    for(int i=0;i<m_vFunDef.size();i++)
                    {
                        qDebug()<<receiver[i];
                    }
                    ODEsolver ode3=l_solver;
                    record_dh-=min_step;
                    //qDebug()<<"AND "<<record_dh;
                    receiver=ode3.evaluate(dx,record_dh,true);

                    for(int i=0;i<m_vFunDef.size();i++)
                    {
                        qDebug()<<receiver[i];
                    }
                }
                map<string,double>::iterator it;
                qDebug()<<"END STEP"<<record_dh;
                receiver=l_solver.evaluate(dx,record_dh,true);
                //for(it=(*(l_solver.GetInputVaraible2Value())).begin();it!=(*(l_solver.GetInputVaraible2Value())).end();it++)
                //{
                //    qDebug()<<QString::fromStdString(it->first)<<"  "<<it->second;
                //}
                //qDebug()<<"Before FIS Receiver";
                //for(int i=0;i<receiver.size();i++)
                //{
                //    qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName);
                //    qDebug()<<receiver[i];
                //}
                QVector<double>tempxx;
                QVector<double>tempy;
                tempxx.push_back(dx+dh);

                if(!fisVec.empty()) //如果存在fis
                {
                    for(unsigned i=0;i<m_vFunDef.size();++i)    //记录初值
                        name2value[m_vFunDef[i].m_sDifferentialName]=datavv[datavv.size()-1][i];
                    //for(unsigned j=0;j<m_vFunDef.size();++j)    //计算差值delta
                    //  name2value[m_vFunDef[j].m_sDifferentialName]-=receiver[j];
                    for(unsigned i=0;i<fisVec.size();++i)   //对于每一个fis
                    {
                        vector<double> con;
                        vector<QString> con1;
                        con1.clear();
                        con.clear();
                        for(unsigned j=0;j<fisVec[i].m_FIS.m_vVariableName.size()-1;++j) //将delta放入vector
                        {
                            //qDebug()<<"Check";
                            //qDebug()<<QString::fromStdString(fisVec[i].m_FIS.m_vVariableName[j]);
                            //qDebug()<<name2value[fisVec[i].m_FIS.m_vVariableName[j]];
                            con.push_back(name2value[fisVec[i].m_FIS.m_vVariableName[j]]);
                            con1.push_back(QString::fromStdString(fisVec[i].m_FIS.m_vVariableName[j]));
                        }
                        double ans;
                        if(QString::fromStdString(fisVec[i].m_FIS.m_sFISType)=="Mamdani")
                            ans=fisVec[i].ruleset->getResultValue1(con);  //传入ruleSet进行模糊推理
                        else
                            ans=fisVec[i].ruleset->getResultValue2(con,con1);
                        ans*=dh/fisVec[i].m_FIS.m_dTimeStep;
                        qDebug()<<"ans:"<<ans;
                        for (unsigned j = 0; j < m_vFunDef.size(); j++)
                        {
                            if (fisVec[i].target.toStdString() == m_vFunDef[j].m_sDifferentialName)
                            {
                                receiver[j] += fisVec[i].op*ans;
                                if(receiver[j]<0)
                                    receiver[j]=0;
                                //qDebug()<<QString::fromStdString(m_vFunDef[j].m_sDifferentialName)<<" Change to:"<<receiver[j];
                                break;
                            }
                        }
                        (*(l_solver.GetInputVaraible2Value()))[fisVec[i].target.toStdString()] += fisVec[i].op*ans;
                        if((*(l_solver.GetInputVaraible2Value()))[fisVec[i].target.toStdString()]<0)
                            (*(l_solver.GetInputVaraible2Value()))[fisVec[i].target.toStdString()]=0;
                    }
                }
                //qDebug()<<"After FIS Receiver";
                for(unsigned i=0;i<receiver.size();i++)
                {
                    //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<"  "<<receiver[i];
                    QVector<double>tempyy;
                    tempyy.push_back(receiver[i]);
                    tempy.push_back(receiver[i]);
                    addData(i,tempxx,tempyy);
                }
                datavv.push_back(tempy);
                ui->progressBar->setValue((dx+dh-l_start)/(l_end-l_start)*100);
                end_time=QTime::currentTime();
                ui->label_9->setText(QString::number(start_time.msecsTo(end_time)/1000.0,'f',3));//0.082
                //ui->customPlot->rescaleAxes();//set range
                //ui->customPlot->rescaleAxes();//0.144-0.082
                //ui->customPlot->replot();//print
            }
        }
        else
        {
            for(dx=l_start;dx+dh<=l_end||dx+dh-l_end<0.000000000001;dx=dx+dh)
            {
                receiver=l_solver.evaluate(dx,dh,false);
                //qDebug()<<"Before FIS Receiver";
                //for(int i=0;i<receiver.size();i++)
                //{
                //    qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<"  "<<receiver[i];
                //}
                QVector<double>tempxx;
                QVector<double>tempy;
                tempxx.push_back(dx+dh);
                if(!fisVec.empty()) //如果存在fis
                {
                    for(unsigned i=0;i<m_vFunDef.size();++i)    //记录初值
                        name2value[m_vFunDef[i].m_sDifferentialName]=datavv[datavv.size()-1][i];
                    //for(unsigned j=0;j<m_vFunDef.size();++j)    //计算差值delta
                    //  name2value[m_vFunDef[j].m_sDifferentialName]-=receiver[j];
                    for(unsigned i=0;i<fisVec.size();++i)   //对于每一个fis
                    {
                        vector<double> con;
                        vector<QString> con1;
                        con1.clear();
                        con.clear();
                        for(unsigned j=0;j<fisVec[i].m_FIS.m_vVariableName.size()-1;++j) //将delta放入vector
                        {
                            //qDebug()<<"Check";
                            //qDebug()<<QString::fromStdString(fisVec[i].m_FIS.m_vVariableName[j]);
                            //qDebug()<<name2value[fisVec[i].m_FIS.m_vVariableName[j]];
                            con.push_back(name2value[fisVec[i].m_FIS.m_vVariableName[j]]);
                            con1.push_back(QString::fromStdString(fisVec[i].m_FIS.m_vVariableName[j]));
                        }
                        double ans;
                        if(QString::fromStdString(fisVec[i].m_FIS.m_sFISType)=="Mamdani")
                            ans=fisVec[i].ruleset->getResultValue1(con);  //传入ruleSet进行模糊推理
                        else
                            ans=fisVec[i].ruleset->getResultValue2(con,con1);
                        ans*=dh/fisVec[i].m_FIS.m_dTimeStep;
                        qDebug()<<"ans:"<<ans;
                        for (unsigned j = 0; j < m_vFunDef.size(); j++)
                        {
                            if (fisVec[i].target.toStdString() == m_vFunDef[j].m_sDifferentialName)
                            {
                                receiver[j] += fisVec[i].op*ans;
                                qDebug()<<QString::fromStdString(m_vFunDef[j].m_sDifferentialName)<<" Change to:"<<receiver[j];
                                break;
                            }
                        }
                        (*(l_solver.GetInputVaraible2Value()))[fisVec[i].target.toStdString()] += fisVec[i].op*ans;
                    }
                }
                //qDebug()<<"After FIS Receiver";
                for(unsigned i=0;i<receiver.size();i++)
                {
                    //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName);
                    //qDebug()<<receiver[i];
                    QVector<double>tempyy;
                    tempyy.push_back(receiver[i]);
                    tempy.push_back(receiver[i]);
                    addData(i,tempxx,tempyy);
                }
                datavv.push_back(tempy);
                ui->progressBar->setValue((dx+dh-l_start)/(l_end-l_start)*100);
                end_time=QTime::currentTime();
                ui->label_9->setText(QString::number(start_time.msecsTo(end_time)/1000.0,'f',3));
                //ui->customPlot->rescaleAxes();//set range
                //ui->customPlot->rescaleAxes();
                //ui->customPlot->replot();//print
            }
        }

        //int rowcount=1;
        //for(int i=0;i<namevector.size();i++)
        //{
        //    ui->tableWidget->setRowCount(rowcount);
        //    QTableWidgetItem *check=new QTableWidgetItem();
        //    check->setCheckState(Qt::Checked);
        //    ui->tableWidget->setItem(i,0,check);
        //    ui->tableWidget->setItem(i,1,new QTableWidgetItem(namevector[i]));
        //    rowcount++;
        //}

        ui->customPlot->rescaleAxes();
        ui->customPlot->replot();
        ui->progressBar->setValue(100);
    }
    ui->tableWidget->show();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    return true;
}*/
/*
void Plot::on_stop_clicked()
{
    flag=1;
}*/
void Plot::updateProperty(int showTitle,QString newTitle,QString newX,QString newY,int showLegend,int newH,int newV,int newStyle,int newWidth,int newType)
{
    titleShoworNot=showTitle;
    if(showTitle==1)
    {
        ui->label->setVisible(true);
        ui->label->setText(newTitle);
    }
    else
    {
        ui->label->setVisible(false);
    }
    ui->customPlot->xAxis->setLabel(newX);
    ui->customPlot->yAxis->setLabel(newY);
    legendShoworNot=showLegend;
    if(showLegend==1)
    {
        ui->customPlot->legend->setVisible(1);
    }
    else
    {
        ui->customPlot->legend->setVisible(0);
    }
    legendpositionH=newH;
    legendpositionV=newV;
    switch(newH)
    {
    case 0:
    {
     if(newV==0)
     {
         ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignTop);
     }
     if(newV==1)
     {
         ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignCenter);
     }
     if(newV==2)
     {
         ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);
     }
    }break;
    case 1:
    {
        if(newV==0)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignTop);
        }
        if(newV==1)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignCenter);
        }
        if(newV==2)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignCenter|Qt::AlignBottom);
        }
    }break;
    case 2:
    {
        if(newV==0)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignRight|Qt::AlignTop);
        }
        if(newV==1)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignRight|Qt::AlignCenter);
        }
        if(newV==2)
        {
            ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignRight|Qt::AlignBottom);
        }
    }break;
    }
    lineStyle=newStyle;
    for(int i=0;i<ui->customPlot->graphCount();i++)
    {
        if(newWidth!=10)
        {
            lineWidth[i]=newWidth;
            pen.setWidthF(newWidth);
            pen.setColor(colorv[i]);
            ui->customPlot->graph(i)->setPen(pen);
        }
        if(newType!=9)
        {
            lineType[i]=newType;
            ui->customPlot->graph(i)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(newType)));
        }
    }
    ui->customPlot->replot();
}
bool Plot::getTitleShoworNot()
{
    return titleShoworNot;
}
void Plot::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender()))
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->customPlot->replot();
    }
  }
}
void Plot::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
  //ui->statusBar->showMessage(message, 2500);
  //ui->sBar->showMessage(message, 2500);
}
void Plot::selectionChanged()
{
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  for (int i=0; i<ui->customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = ui->customPlot->graph(i);
    QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
    }
  }
}
void Plot::saveImage()
{
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui->customPlot->winId());
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    if(filename1!="")
    {
        if(QFileInfo(filename1).suffix().isEmpty())
            filename1.append(".png");
        p.save(filename1);
        QMessageBox::information(this,tr("operation succeed!"),tr("image is saved in%1!").arg(filename1),tr("OK"));
    }
    else
        QMessageBox::warning(this,tr("Path"),tr("You did not select any file."));
}

void Plot::savePDF()
{
    //QScreen * screen = QGuiApplication::primaryScreen();
    //QPixmap pixmap = screen->grabWindow(ui->customPlot->winId());
    QString path="./this_is_for_printer_please_do_not_name_the_pic_same.png";
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui->customPlot->winId());
    p.save(path);
    QPrinter pic_printer(QPrinter::ScreenResolution);
    pic_printer.setPageSize(QPrinter::A4);
    //pic_printer.setPageSize(QPrinter::Custom);
    //pic_printer.setPageSizeMM(QSizeF(200,150));
    pic_printer.setOutputFormat(QPrinter::PdfFormat);
    QString file_path = QFileDialog::getSaveFileName(this,"Export PDF",QString(),"*.pdf");
    if(!file_path.isEmpty())
    {
        if(QFileInfo(file_path).suffix().isEmpty())
            file_path.append(".pdf");
        pic_printer.setOutputFileName(file_path);           //设置文件名
        //QPixmap pixmap=QWidget::grab(QRect(ui->customplot->x(),ui->qcustomplot->y(),ui->qcustomplot->frameGeometry().width(),ui->qcustomplot->frameGeometry().height()+10));
        QPainter pic_painter;
        pic_painter.begin(&pic_printer);
        QRect rect=pic_painter.viewport();
        QImage img(path);
        QSize size=img.size();
        size.scale(rect.size(),Qt::KeepAspectRatio);
        pic_painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        pic_painter.setWindow(img.rect());
        pic_painter.drawImage(0, 0, img);
        pic_painter.end();
        /*
        int factor1=rect.width()/pixmap.width();
        int factor2=rect.height()/pixmap.height();
        if(factor1<factor2)
            pic_painter.scale(factor1,factor1);
        else
            pic_painter.scale(factor2,factor2);
        pic_painter.drawPixmap(10,10,pixmap);
        pic_painter.end();
        */
        QMessageBox::information(this,tr("operation succeed!"),tr("pdf is saved in%1!").arg(file_path),tr("OK"));
    }
    else
        QMessageBox::warning(this,tr("Path"),tr("You did not select any file."));
}
void Plot::on_save_clicked()
{
    if(ui->comboBox->currentIndex()==0)
    {
        saveImage();
    }
    if(ui->comboBox->currentIndex()==1)
    {
        savePDF();
    }
    if(ui->comboBox->currentIndex()==2)
    {
        savediffcsv* view=new savediffcsv;
        view->setId(PlotId);
        view->show();
    }
    if(ui->comboBox->currentIndex()==3)
    {
        QString filename = QFileDialog::getSaveFileName(this,"Save ODE",QString(),"*.txt"); //选择路径
        if(QFileInfo(filename).suffix().isEmpty())
            filename.append(".txt");
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
        }
        QTextStream in(&file);
        for(unsigned i=0;i<m_vFunDef.size();i++)
        {
            in<<"d"<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<"/dt="<<QString::fromStdString(m_vFunDef[i].m_sFunctionExp)<<endl;
        }
        file.close();
    }
    if(ui->comboBox->currentIndex()==4)
    {
        QString path="./this_is_for_printer_please_do_not_name_the_pic_same.png";
        QScreen * screen = QGuiApplication::primaryScreen();
        QPixmap p = screen->grabWindow(ui->customPlot->winId());
        p.save(path);
        QPrinter printer(QPrinter::ScreenResolution);
        QPrintDialog* printDialog = new QPrintDialog(&printer, 0);
        if (printDialog->exec() == QDialog::Accepted)
        {
            QImage img(path);
            QPainter painter(&printer);
            QRect rect=painter.viewport();
            QSize size=img.size();
            size.scale(rect.size(),Qt::KeepAspectRatio);
            painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
            painter.setWindow(img.rect());
            painter.drawImage(0, 0, img);
            painter.end();
        }
        delete printDialog;
    }
}
void Plot::on_tabular_clicked()
{
    Tabular* view=new Tabular;
    view->setId(PlotId);
    view->initialTablev();
    view->show();
}
vector<bool> Plot::getTableChecked()
{
    vector<bool> temp;
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        if(ui->tableWidget->item(i,0)->checkState()==Qt::Checked)
        {
            temp.push_back(true);
        }
        else
        {
            temp.push_back(false);
        }
    }
    return temp;
}
void Plot::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else
  {
    if (ui->customPlot->selectedGraphs().size() > 0)
      menu->addAction("Edit line properties", this, SLOT(editLinebyMenu()));
  }

  menu->popup(ui->customPlot->mapToGlobal(pos));
}
void Plot::getCurrentInScreenGraphData()
{
    //////int inScreenGraphNum;
    //////int inScreenGrapgTotal=ui->customPlot->graphCount();
    //////for(int i=0;i<inScreenGrapgTotal;i++)
    //////{
    //////    if(ui->customPlot->graph(i)->selected())
    //////    {
    //////        inScreenGraphNum=i;
    //////        break;
    //////    }
    //////}
    //////int totalGraphCount=ui->tableWidget->rowCount();
    //////int counttemp=-1;
    //////for(int i=0;i<totalGraphCount;i++)
    //////{
    //////    if(ui->tableWidget->item(i,0)->checkState()==Qt::Checked)
    //////    {
    //////        counttemp++;
    //////        if(counttemp==inScreenGraphNum)
    //////        {
    //////            currentGraphNum=i;
    //////            break;
    //////        }
    //////    }
    //////}
    int totalGraphCount=ui->tableWidget->rowCount();
    for(int i=0;i<totalGraphCount;i++)
    {
        if(ui->customPlot->graph(i)->selected())
        {
            currentGraphNum=i;
            break;
        }
    }
    currentType=lineType[currentGraphNum];
    currentColor=colorv[currentGraphNum];
    currentWidth=lineWidth[currentGraphNum];
}
/*
void Plot::getCurrentInScreenGraphData()
{
    int inScreenGraphNum;
    int inScreenGrapgTotal=ui->customPlot->graphCount();
    for(int i=0;i<inScreenGrapgTotal;i++)
    {
        if(ui->customPlot->graph(i)->selected())
        {
            inScreenGraphNum=i;
            break;
        }
    }
    int totalGraphCount=ui->tableWidget->rowCount();
    int counttemp=-1;
    for(int i=0;i<totalGraphCount;i++)
    {
        if(ui->tableWidget->item(i,0)->checkState()==Qt::Checked)
        {
            counttemp++;
            if(counttemp==inScreenGraphNum)
            {
                currentGraphNum=i;
                break;
            }
        }
    }
    currentType=lineType[currentGraphNum];
    currentColor=colorv[currentGraphNum];
    currentWidth=lineWidth[currentGraphNum];
}*/
void Plot::editLinebyMenu()
{
    //editlineproperty* view=new editlineproperty;
    //view->show();
    getCurrentInScreenGraphData();
    editplotproperty subwin(this);
    subwin.exec();
}
/*
void Plot::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    currentGraphNum=item->row();
    currentType=lineType[currentGraphNum];
    currentColor=colorv[currentGraphNum];
    currentWidth=lineWidth[currentGraphNum];
    //editlineproperty* view=new editlineproperty;
    //view->show();
    editplotproperty subwin(this);
    subwin.exec();
}*/
void Plot::updatePlot(int graphNum,QColor newColor,int newType,int newWidth)
{
    colorv[graphNum]=newColor;
    lineType[graphNum]=newType;
    lineWidth[graphNum]=newWidth;
    pen.setColor(newColor);
    pen.setWidthF(newWidth);
    ui->customPlot->graph(graphNum)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(newType)));
    ui->customPlot->graph(graphNum)->setPen(pen);
    ui->customPlot->replot();
}
QString Plot::getTitle()
{
    return ui->label->text();
}
QString Plot::getXlabel()
{
    return ui->customPlot->xAxis->label();
}
QString Plot::getYlabel()
{
    return ui->customPlot->yAxis->label();
}
bool Plot::getLegendShoworNot()
{
    return legendShoworNot;
}
int Plot::getLegendPositionH()
{
    return legendpositionH;
}
int Plot::getLegendPositionV()
{
    return legendpositionV;
}
int Plot::getLineStyle()
{
    return lineStyle;
}
void Plot::on_edit_clicked()
{
    editmanyproperty subwin(this);
    subwin.exec();
}
void Plot::initialColor()
{
    colorv.clear();
    int count=namevector[PlotId].size();
    for(int i=0;i<count;i++)
    {
        QColor temp=QColor(rand()%245+10, rand()%245+10, rand()%245+10);
        colorv.push_back(temp);
    }
}
void Plot::initialLineType()
{
    lineType.clear();
    int count=namevector[PlotId].size();
    for(int i=0;i<count;i++)
    {
        //lineType.push_back(rand()%9+1);
        lineType.push_back(1);
    }
}
void Plot::initialLineWidth()
{
    int count=namevector[PlotId].size();
    for(int i=0;i<count;i++)
    {
        lineWidth.push_back(2);
    }
}

void Plot::setComList(ComponentList*list)
{
    m_com_list=list;
}

void Plot::setRuleManager(RuleManager*ruleManager)
{
    m_ruleManager=ruleManager;
}
