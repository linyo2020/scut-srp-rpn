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
     * @brief run
     * @return
     */
    bool run(QString,double,double,double,bool,int);

signals:
    /**
     * @brief updateui
     */
    void updateui(double,QString);
    /**
     * @brief addgraph
     */
    void addgraph(string);
    /**
     * @brief adddata
     */
    void adddata(unsigned,QVector<double>,QVector<double>);
public slots:
    /**
     * @brief slotUpdateUi
     */
    void slotUpdateUi(double,QString);
    /**
     * @brief slotAddGraph
     */
    void slotAddGraph(string);
    /**
     * @brief slotAddData
     */
    void slotAddData(unsigned,QVector<double>,QVector<double>);

public:
    /**<主线程对象指针*/
    Plot *m_gui;
};

#endif // CALCULATE_H
