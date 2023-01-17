#ifndef PLOT_H
#define PLOT_H
#include <QDebug>
#include <QWidget>
#include <QInputDialog>
#include<cmath>
#include<QMainWindow>
#include<QFileDialog>
#include<QTextStream>
#include<QVector>
#include<QHeaderView>
#include<QTableWidget>
#include<QColorDialog>
#include<QColor>
#include<QFrame>
#include<QDialog>
#include<QStatusBar>
#include<QPainter>
#include<QPdfWriter>
#include<ODESolver/ODEsolver.h>
#include"qcustomplot.h"
#include"tabular.h"
#include"editplotproperty.h"
#include"editmanyproperty.h"
#include"savediffcsv.h"
#include<QFont>
#include"componentlist.h"
/** 页id和vector的映射*/
extern map<QString,QVector<QString>> namevector;
/** 用于数据表格化 */
extern map<QString,QVector<QVector<double>>> datavv;
/** 页id映射页内库所对应的ode方程集合*/
extern map<QString,vector<FUNCTIONDEF>> e_vFunDef;
/** 页id映射（库所名字映射初始token值）*/
extern map<QString,map<string,double>> e_mInputVaraible2Value;

extern int currentGraphNum;
extern QColor currentColor;
extern int currentType;
extern int currentWidth;

namespace Ui {
class Plot;
}

/**
 * @brief The Plot class
 */
class Plot : public QWidget
{
    Q_OBJECT

public:
    explicit Plot(QWidget *parent = 0);
    ~Plot();
    /**
     * @brief updatePlot
     * @param graphNum
     * @param newColor
     * @param newType
     * @param newWidth
     */
    void updatePlot(int graphNum,QColor newColor,int newType,int newWidth);
    QString getTitle();
    QString getXlabel();
    QString getYlabel();
    bool getLegendShoworNot();
    int getLegendPositionH();
    int getLegendPositionV();
    int getLineStyle();
    bool getTitleShoworNot();
    void setPlotId(QString);
    /**
     * @brief updateProperty
     * @param showTitle
     * @param newTitle
     * @param newX
     * @param newY
     * @param showLegend
     * @param newH
     * @param newV
     * @param newStyle
     * @param newWidth
     * @param newType
     */
    void updateProperty(int showTitle,QString newTitle,QString newX,QString newY,int showLegend,int newH,int newV,int newStyle,int newWidth,int newType);
public slots:
    /**
     * @brief startSimulation
     */
    void startSimulation();
    /**
     * @brief updateUi 更新仿真进度
     * @param x        进度
     * @param y        仿真运行时间
     */
    void updateUi(double x,QString y);
    /**
     * @brief addGraph 增加一条曲线
     * @param string   曲线名称
     */
    void addGraph(string);
    /**
     * @brief addData  向曲线增加数据
     * @param i        曲线编号
     * @param x        x坐标集合
     * @param y        y坐标集合
     */
    void addData(int,QVector<double>&,QVector<double>&);
    /**
     * @brief setComList
     */
    void setComList(ComponentList*);
private slots:
    /**
     * @brief addNewGraphv
     * @param n
     */
    void addNewGraphv(int n);
    /**
     * @brief addAllGraph
     */
    void addAllGraph();
    //void addNewGraph(int n);
    //void addGraph1();
    //void addGraph2();
    //void addGraph3();
    //void addGraph4();
    /**
     * @brief moveLegend
     */
    void moveLegend();
    /**
     * @brief selectionChanged
     */
    void selectionChanged();
    //void on_stop_clicked();
    /**
     * @brief graphClicked
     * @param plottable
     * @param dataIndex
     */
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    //bool insertListWidget( QString description );
    //void initialTablev();
    //void initialListv();
    //QVector<bool> getCheckedState();
    //void on_pushButton_clicked();
    //void on_pushButton_clicked();
    //void on_pushButton_2_clicked();
    /**
     * @brief on_checkBox_2_clicked
     */
    void on_checkBox_2_clicked();
    /**
     * @brief on_save_clicked
     */
    void on_save_clicked();
    /**
     * @brief saveImage
     */
    void saveImage();
    //void saveCSV();
    /**
     * @brief saveCSVv
     */
    void saveCSVv();
    /**
     * @brief savePDF
     */
    void savePDF();
    /**
     * @brief on_tabular_clicked
     */
    void on_tabular_clicked();
    /**
     * @brief initialVector
     */
    void initialVector();
    /**
     * @brief getTableChecked
     * @return
     */
    vector<bool> getTableChecked();
    /**
     * @brief updateGraph
     */
    void updateGraph();
    /**
     * @brief contextMenuRequest
     * @param pos
     */
    void contextMenuRequest(QPoint pos);
    /**
     * @brief editLinebyMenu
     */
    void editLinebyMenu();
    /**
     * @brief initialColor
     */
    void initialColor();
    /**
     * @brief initialLineType
     */
    void initialLineType();
    /**
     * @brief initialLineWidth
     */
    void initialLineWidth();
    /**
     * @brief getCurrentInScreenGraphData
     */
    void getCurrentInScreenGraphData();
    //bool on_Start_clicked();
    /**
     * @brief InitializeNet
     */
    void InitializeNet();
    //void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    //void addGraph(string);
    //void addData(int,QVector<double>&,QVector<double>&);
    /**
     * @brief on_edit_clicked
     */
    void on_edit_clicked();
    //void updateUi(double x,QString y);

private:
    QString PlotId;
    Ui::Plot *ui;
    QVector<QColor> colorv;
    QVector<int> lineType;
    QVector<int> lineWidth;
    QPen pen;
    int count=0;
    int legendpositionH;
    int legendpositionV;
    int lineStyle;
    int legendShoworNot;
    int titleShoworNot;
    int flag=0;
    QFont legendFont;
    map<string,double> m_mInputVaraible2Value;
    vector<FUNCTIONDEF> m_vFunDef;
    ComponentList*com_list;
};

#endif // PLOT_H
