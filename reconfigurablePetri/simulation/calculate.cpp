#include "calculate.h"
//QVector<QString> namevector;
//QVector<QVector<double>> datavv;
//vector<fisRecord> fisVec;   //存储arc中fis
//vector<FUNCTIONDEF> e_vFunDef;
//map<string,double> e_mInputVaraible2Value;
extern int g_run;

Calculate::Calculate(Plot *gui)
{
    m_gui = gui;

    connect(this, SIGNAL(updateui(double,QString)), this, SLOT(slotUpdateUi(double,QString)));
    connect(this, SIGNAL(addgraph(string)),this,SLOT(slotAddGraph(string)));
    connect(this, SIGNAL(adddata(unsigned,QVector<double>,QVector<double>)),this,SLOT(slotAddData(unsigned,QVector<double>,QVector<double>)));
}

Calculate::~Calculate()
{

}
void Calculate::slotAddGraph(string s)
{
    m_gui->addGraph(s);
}
void Calculate::slotAddData(unsigned i,QVector<double>t1,QVector<double>t2)
{
    m_gui->addData(i,t1,t2);
}
void Calculate::slotUpdateUi(double x,QString y)
{
    m_gui->updateUi(x,y);
}
bool Calculate::run(QString PlotId,double l_start,double l_end,double dh,bool state)
{
    //子线程无法操作界面，例如显示数据怎么搞？？
    //发信号给主线程
    map<string,double> m_mInputVaraible2Value=e_mInputVaraible2Value[PlotId];
    vector<FUNCTIONDEF> m_vFunDef=e_vFunDef[PlotId];

        //发出信号，此时调用槽函数
        datavv[PlotId].clear();
        QTime start_time=QTime::currentTime();
        QTime end_time=QTime::currentTime();
        ODEsolver l_solver;
        l_solver.setMap(m_mInputVaraible2Value);
        l_solver.setVector(m_vFunDef);
        bool l_check=l_solver.parser();
        if(l_check==false)
        {
            //QMessageBox::about(this,tr("Compile Error"),tr("Please check the input"));
            return false;
        }
        else
        {
            map<string,double> name2value;
            name2value.clear();
            vector<double>receiver;
            QVector<double>temp; //temp中存放初始值，存放顺序为m_vFunDef中每个位置的先后顺序
            for(unsigned i=0;i<m_vFunDef.size();i++)
            {
                emit addgraph(m_vFunDef[i].m_sDifferentialName);
                //addGraph(m_vFunDef[i].m_sDifferentialName);
                QVector<double>temp1;
                temp1.push_back(l_start);
                QVector<double>temp2;
                temp2.push_back(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]);
                temp.push_back(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]);
                emit adddata(i,temp1,temp2);
                //addData(i,temp1,temp2);
            }
            datavv[PlotId].push_back(temp);
            double dx;
            int count=0;
            QApplication::setOverrideCursor(Qt::WaitCursor);
            if(state)
            {
                for(dx=l_start;dx+dh<=l_end||dx+dh-l_end<0.00000000001;dx=dx+dh)
                {
                    ODEsolver ode1=l_solver;//此时l_solver仍为上一步
                    receiver=ode1.evaluate(dx,dh,true);//计算下一步的值
                    double record_dh=dh;//记录步长
                    while(true)//检测是否小于0
                    {
                        int flag=1;//flag用来判断是否均为非负
                        double min_step=record_dh;
                        double pre_step=0;
                        for(int i=0;i<receiver.size();i++)//对于每一个下一步值
                        {
                            int flag2=1;//判断是否有次数用尽但仍未到0
                            double step=0.5*record_dh;
                            double l_wall=0.0;
                            double r_wall=record_dh;
                            if(receiver[i]<0)//检测一个receiver若小于0，则重复至求得为0时步长
                            {
                                flag=0;//存在负值
                                ODEsolver ode4=l_solver;
                                //////////double record_step=0;
                                receiver[i]=(ode4.evaluate(dx,step,true))[i];//不同的步长，计算下一步值
                                int count=0;
                                while(receiver[i]<-0.00000000001||receiver[i]>0.00000000001)//求出0时步长
                                {
                                    ODEsolver ode2=l_solver;
                                    if(receiver[i]>0.00000000001)
                                    {
                                        l_wall=step;
                                        step=(step+r_wall)/2;
                                        ////////////record_step=step;
                                        pre_step=step;
                                    }
                                    else if(receiver[i]<-0.00000000001)
                                    {
                                        r_wall=step;
                                        step=(l_wall+step)/2;
                                    }
                                    receiver[i]=(ode2.evaluate(dx,step,true))[i];
                                    count++;
                                    if(count==50)//重复n次，若n次后仍未负值，退出循环
                                    {
                                        flag2=0;
                                        break;
                                    }
                                }
                            }
                            if(flag2==0)//若未找到负值
                                min_step=min(min_step,pre_step);
                            else min_step=min(min_step,step);//min_step为使所有值均为非负的步长
                        }
                        if(flag==1)
                        {
                            break;
                        }
                        receiver=l_solver.evaluate(dx,min_step,true);//按最小步长进行计算
                        ODEsolver ode3=l_solver;
                        record_dh-=min_step;//计算原步长-下一步长
                        receiver=ode3.evaluate(dx,record_dh,true);
                    }
                    receiver=l_solver.evaluate(dx,record_dh,true);
                    QVector<double>tempxx;
                    QVector<double>tempy;
                    tempxx.push_back(dx+dh);

                    //qDebug()<<dx<<" RESULT";
                    for(unsigned i=0;i<receiver.size();i++)
                    {
                        //qDebug()<<dx<<" RESULT";
                        //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" "<<receiver[i];
                        QVector<double>tempyy;
                        tempyy.push_back(receiver[i]);
                        tempy.push_back(receiver[i]);
                        emit adddata(i,tempxx,tempyy);
                        //addData(i,tempxx,tempyy);
                    }
                    datavv[PlotId].push_back(tempy);
                    double value=(dx+dh-l_start)/(l_end-l_start)*100;
                    end_time=QTime::currentTime();
                    QString qs=QString::number(start_time.msecsTo(end_time)/1000.0,'f',3);
                    if(count%10==0)
                    {
                        emit updateui(value,qs);
                        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                    }
                    //ui->progressBar->setValue((dx+dh-l_start)/(l_end-l_start)*100);
                    //end_time=QTime::currentTime();
                    //ui->label_9->setText(QString::number(start_time.msecsTo(end_time)/1000.0,'f',3));//0.082
                    count++;
                    //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                }
            }
            else
            {
                for(dx=l_start;dx+dh<=l_end||dx+dh-l_end<0.000000000001;dx=dx+dh)
                {
                    receiver=l_solver.evaluate(dx,dh,false);
                    QVector<double>tempxx;
                    QVector<double>tempy;
                    tempxx.push_back(dx+dh);

                    for(unsigned i=0;i<receiver.size();i++)
                    {
                        QVector<double>tempyy;
                        tempyy.push_back(receiver[i]);
                        tempy.push_back(receiver[i]);
                        emit adddata(i,tempxx,tempyy);
                        //addData(i,tempxx,tempyy);
                    }
                    datavv[PlotId].push_back(tempy);
                    double value=(dx+dh-l_start)/(l_end-l_start)*100;
                    end_time=QTime::currentTime();
                    QString qs=QString::number(start_time.msecsTo(end_time)/1000.0,'f',3);
                    if(count%10==0)
                    {
                        emit updateui(value,qs);
                        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                    }
                    //ui->progressBar->setValue((dx+dh-l_start)/(l_end-l_start)*100);
                    //end_time=QTime::currentTime();
                    //ui->label_9->setText(QString::number(start_time.msecsTo(end_time)/1000.0,'f',3));
                    count++;
                    //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                }
            }
            QApplication::restoreOverrideCursor();
        }
    return true;
}


