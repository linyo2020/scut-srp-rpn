#include "calculate.h"
extern int g_run;

Calculate::Calculate(Plot *gui)
{
    m_gui = gui;

    connect(this, &Calculate::updateui, this, &Calculate::slotUpdateUi);
    connect(this, &Calculate::addgraph,this,&Calculate::slotAddGraph);
    connect(this, &Calculate::adddata,this,&Calculate::slotAddData);
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
        //获取当前页的函数表达式以及库所变量-token值的映射
        map<string,double> m_mInputVaraible2Value=e_mInputVaraible2Value[PlotId];
        vector<FUNCTIONDEF> m_vFunDef=e_vFunDef[PlotId];
        //用来记录仿真数据
        datavv[PlotId].clear();
        //用来记录仿真时间
        QTime start_time=QTime::currentTime();
        QTime end_time=QTime::currentTime();
        //ode计算器初始化
        ODEsolver l_solver;
        l_solver.setMap(m_mInputVaraible2Value);
        l_solver.setVector(m_vFunDef);
        //解析函数表达式的变量，检查合法性
        bool l_check=l_solver.parser();
        if(l_check==false)
        {
            return false;
        }
        else
        {
            map<string,double> name2value;
            name2value.clear();
            vector<double>receiver;
            //temp中存放初始值，存放顺序为m_vFunDef中每个库所的先后顺序
            QVector<double>temp;
            for(unsigned i=0;i<m_vFunDef.size();i++)
            {
                //增加曲线和起点数据
                emit addgraph(m_vFunDef[i].m_sDifferentialName);
                QVector<double>temp1;
                temp1.push_back(l_start);
                QVector<double>temp2;
                temp2.push_back(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]);
                temp.push_back(m_mInputVaraible2Value[m_vFunDef[i].m_sDifferentialName]);
                emit adddata(i,temp1,temp2);
            }
            datavv[PlotId].push_back(temp);
            double dx;
            int count=0;
            QApplication::setOverrideCursor(Qt::WaitCursor);
            //如果仿真需要检查负值
            if(state)
            {
                //按步长间隔进行仿真
                for(dx=l_start;dx+dh<=l_end||dx+dh-l_end<0.00000000001;dx=dx+dh)
                {
                    //此时l_solver仍为上一步
                    ODEsolver ode1=l_solver;
                    //计算下一步的值
                    receiver=ode1.evaluate(dx,dh,true);
                    //记录步长
                    double record_dh=dh;
                    //检测是否小于0，每个循环将一个零点处的斜率置为0来修正结果
                    while(true)
                    {
                        //flag用来判断是否均为非负
                        int flag=1;
                        //min_step为使所有值均为非负的步长
                        double min_step=record_dh;
                        //二分法中用来记录支点右移前的原位置，等同于左边界
                        double pre_step=0;
                        //对于每一个下一步值
                        for(int i=0;i<receiver.size();i++)
                        {
                            //flag2判断是否有次数用尽但仍未到0
                            int flag2=1;
                            //二分法的支点，初始值设置为中点
                            double step=0.5*record_dh;
                            //二分法左边界
                            double l_wall=0.0;
                            //二分法右边界
                            double r_wall=record_dh;
                            //检测一个receiver若小于0，则重复至求得为0时步长
                            if(receiver[i]<0)
                            {
                                flag=0;//存在负值
                                ODEsolver ode4=l_solver;
                                //不同的步长，计算下一步值
                                receiver[i]=(ode4.evaluate(dx,step,true))[i];
                                int count=0;
                                //二分法求零点
                                while(receiver[i]<-0.00000000001||receiver[i]>0.00000000001)
                                {
                                    ODEsolver ode2=l_solver;
                                    //零点在支点右边
                                    if(receiver[i]>0.00000000001)
                                    {
                                        l_wall=step;
                                        //支点右移
                                        step=(step+r_wall)/2;
                                        pre_step=step;
                                    }
                                    //零点在支点左边
                                    else if(receiver[i]<-0.00000000001)
                                    {
                                        r_wall=step;
                                        //支点左移
                                        step=(l_wall+step)/2;
                                    }
                                    receiver[i]=(ode2.evaluate(dx,step,true))[i];
                                    count++;
                                    //重复n次，若n次后仍未定位到0，退出循环
                                    if(count==50)
                                    {
                                        flag2=0;
                                        break;
                                    }
                                }
                            }
                            //若step没定位到零点
                            if(flag2==0)
                                min_step=min(min_step,pre_step);
                            //若step定位到零点
                            else min_step=min(min_step,step);
                        }
                        //如果值全部为非负
                        if(flag==1)
                        {
                            break;
                        }
                        //按最小步长进行计算，更新映射表，映射表的（值可能）出现最小零点
                        receiver=l_solver.evaluate(dx,min_step,true);
                        ODEsolver ode3=l_solver;
                        //计算原步长与下一步长的差值
                        record_dh-=min_step;
                        //evaluate通过识别映射表的向下零点，对相应函数表达式清零，得到非负结果
                        receiver=ode3.evaluate(dx,record_dh,true);
                    }
                    receiver=l_solver.evaluate(dx,record_dh,true);
                    QVector<double>tempxx;
                    QVector<double>tempy;
                    tempxx.push_back(dx+dh);

                    //qDebug()<<dx<<" RESULT";
                    //保存与发送绘图数据
                    for(unsigned i=0;i<receiver.size();i++)
                    {
                        //qDebug()<<dx<<" RESULT";
                        //qDebug()<<QString::fromStdString(m_vFunDef[i].m_sDifferentialName)<<" "<<receiver[i];
                        QVector<double>tempyy;
                        tempyy.push_back(receiver[i]);
                        tempy.push_back(receiver[i]);
                        emit adddata(i,tempxx,tempyy);
                    }
                    //保存仿真数据用来显示表格或导出
                    datavv[PlotId].push_back(tempy);
                    //仿真进度
                    double value=(dx+dh-l_start)/(l_end-l_start)*100;
                    //计算仿真时间
                    end_time=QTime::currentTime();
                    QString qs=QString::number(start_time.msecsTo(end_time)/1000.0,'f',3);
                    //间隔地在UI上更新仿真进度和仿真时间
                    if(count%10==0)
                    {
                        emit updateui(value,qs);
                        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                    }
                    count++;
                }
            }
            //如果仿真不需要检查负值
            else
            {
                //按步长间隔进行仿真
                for(dx=l_start;dx+dh<=l_end||dx+dh-l_end<0.000000000001;dx=dx+dh)
                {
                    //计算
                    receiver=l_solver.evaluate(dx,dh,false);

                    //保存与发送绘图数据
                    QVector<double>tempxx;
                    QVector<double>tempy;
                    tempxx.push_back(dx+dh);
                    for(unsigned i=0;i<receiver.size();i++)
                    {
                        QVector<double>tempyy;
                        tempyy.push_back(receiver[i]);
                        tempy.push_back(receiver[i]);
                        emit adddata(i,tempxx,tempyy);
                    }
                    //保存仿真数据用来显示表格或导出
                    datavv[PlotId].push_back(tempy);
                    //仿真进度
                    double value=(dx+dh-l_start)/(l_end-l_start)*100;
                    //计算仿真时间
                    end_time=QTime::currentTime();
                    QString qs=QString::number(start_time.msecsTo(end_time)/1000.0,'f',3);
                    //间隔地在UI上更新仿真进度和仿真时间
                    if(count%10==0)
                    {
                        emit updateui(value,qs);
                        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                    }
                    count++;
                }
            }
            QApplication::restoreOverrideCursor();
        }
    return true;
}


