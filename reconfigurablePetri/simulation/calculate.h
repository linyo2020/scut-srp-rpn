#ifndef CALCULATE_H
#define CALCULATE_H
#include <QThread>
#include "plot.h"
#include <QApplication>
/**
 * @brief The Calculate class
 */
class Calculate : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Calculate
     * @param gui
     */
    Calculate(Plot *gui);
    ~Calculate();

    /**
     * @brief run     重写虚run函数
     * @param PlotId  编号
     * @param l_start 开始时间
     * @param l_end   截止时间
     * @param dh      步长
     * @param state   是否检查负数
     * @return
     */
    bool run(QString,double,double,double,bool);

signals:
    /**
     * @brief updateui 更新仿真进度条
     * @param x        进度
     * @param y        仿真运行时间
     */
    void updateui(double,QString);
    /**
     * @brief addgraph 在图中增加一条曲线
     * @param string   曲线名字
     */
    void addgraph(string);
    /**
     * @brief adddata 在曲线上增加数据
     * @param i       曲线编号
     * @param t1      x坐标集合
     * @param t2      y坐标集合
     */
    void adddata(unsigned,QVector<double>,QVector<double>);
public slots:
    /**
     * @brief slotUpdateUi 更新仿真进度条
     * @param x            进度
     * @param y            仿真运行时间
     */
    void slotUpdateUi(double,QString);
    /**
     * @brief slotAddGraph 在图中增加一条曲线
     * @param s            曲线名字
     */
    void slotAddGraph(string);
    /**
     * @brief slotAddData      向曲线增加数据
     * @param i                曲线编号
     * @param t1               x坐标集合
     * @param t2               y坐标集合
     */
    void slotAddData(unsigned,QVector<double>,QVector<double>);

public:
    /** 主线程对象指针*/
    Plot *m_gui;
};

#endif // CALCULATE_H
