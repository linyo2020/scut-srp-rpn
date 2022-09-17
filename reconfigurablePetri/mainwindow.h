#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QStatusBar>
#include <QSlider>
#include<QFont>
#include <QToolTip>

#include <QCloseEvent>

#include "tabwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //QT5的槽函数可以写到public/全局
    void buttonGroupClicked (int id);
    void tabChanged (int index);
    void sliderValueChanged (int value);
    void open ();
    void about();

private:

    //各个菜单栏及其动作
    QMenu   * fileMenu;
    QAction * newMenuAct;
    QAction * openMenuAct;
    QAction * saveMenuAct;
    QAction * saveAsMenuAct;
    QAction * exportMenuAct;
    QAction * printMenuAct;
    QAction * quitMenuAct;

    QMenu   * editMenu;
    QAction * undoMenuAct;
    QAction * redoMenuAct;
    QAction * removeMenuAct;

    QMenu   * helpMenu;
    QAction * aboutMenuAct;

    //同等于工具栏的圆框线
    QMenu   * m_modelingMenu;
    QAction * m_placeMenuAct;
    QAction * m_transitionMenuAct;
    QAction * m_arcMenuAct;


    //状态栏
    QStatusBar * statusBar;

    //工具栏及按钮组
    QToolBar * toolBar;
    QButtonGroup * buttonGroup;

    QToolButton  * newToolButton;
    QToolButton  * openToolButton;
    QToolButton  * saveToolButton;
    QToolButton * saveAsToolButton;
    QToolButton * printToolButton;

    QToolButton  * undoToolButton;
    QToolButton  * redoToolButton;
    QToolButton  * removeToolButton;

    QToolButton  * cursorToolButton;
    QToolButton  * addPlaceToolButton;
    QToolButton  * addTransToolButton;
    QToolButton  * drawArcToolButton;

    //仿真按钮
    QToolButton  * animateToolButton;

    //选项卡式的窗口控件
    TabWidget  * tabWidget;

    //用于缩放的滑动条
    QSlider  * slider;

    //初始化菜单，工具，状态栏，拖拉界面
    void createMenuBar ();
    void createToolBar ();
    void createStatusBar ();
    void createDocks ();

};

#endif // MAINWINDOW_H
