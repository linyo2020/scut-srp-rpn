#include "mainwindow.h"
#include "editrulelibrary.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //字体设置
    QFont font;
    font.setFamily("Arial");
    this->setFont(font);

     //选项卡，设置为中心窗口部件
      tabWidget = new TabWidget;
      setCentralWidget (tabWidget);

      //初始化
      createToolBar ();
      createMenuBar();
      createDocks ();
      createStatusBar ();

      connect(tabWidget, &TabWidget::currentChanged,this,&MainWindow::tabChanged);

}

/*
 * 初始化工具栏
 *  */
void MainWindow::createToolBar ()
{
    //增加新widget页面按钮
    newToolButton = new QToolButton;
    newToolButton->setIconSize(QSize(50, 50));
    newToolButton->setIcon(QIcon(QPixmap(":/images/widow-new.png")));
    newToolButton->setToolTip(tr("Create a new Petri Net <span style=\"color:gray;\">Ctrl+N</span>"));
    connect(newToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->createNew();});
    //打开文件
    openToolButton = new QToolButton;
    openToolButton->setIconSize(QSize(50, 50));
    openToolButton->setIcon(QIcon(QPixmap(":/images/folder-open.png")));
    openToolButton->setToolTip(tr("Open a Petri Net document <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(openToolButton,&QToolButton::clicked,this,[=](){this->open();});

    saveToolButton = new QToolButton;
    saveToolButton->setIconSize(QSize(50, 50));
    saveToolButton->setIcon(QIcon(QPixmap(":/images/document-save.png")));
    saveToolButton->setToolTip(tr("Save the current Petri Net <span style=\"color:gray;\">Ctrl+S</span>"));
    connect(saveToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->save();});
    saveAsToolButton = new QToolButton;
    saveAsToolButton->setIconSize(QSize(50, 50));
    saveAsToolButton->setIcon(QIcon(QPixmap(":/images/saveAs.png")));
    saveAsToolButton->setToolTip(tr("Save the current Petri Net as <span style=\"color:gray;\">F12</span>"));
    connect(saveAsToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->saveAs();});
    printToolButton = new QToolButton;
    printToolButton->setIconSize(QSize(50, 50));
    printToolButton->setIcon(QIcon(QPixmap(":/images/printer.png")));
    printToolButton->setToolTip(tr("Print <span style=\"color:gray;\">Ctrl+P</span>"));
    connect(printToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->print();});

    undoToolButton = new QToolButton;
    undoToolButton->setIconSize(QSize(50, 50));
    undoToolButton->setIcon(QIcon(QPixmap(":/images/undo.png")));
    undoToolButton->setToolTip(tr("Undo the last action <span style=\"color:gray;\">Ctrl+Z</span>"));
    undoToolButton->setEnabled(false);
    connect(undoToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->undo();});
    connect(tabWidget, &TabWidget::canUndoChange, undoToolButton, &QToolButton::setEnabled);

    redoToolButton = new QToolButton;
    redoToolButton->setIconSize(QSize(50, 50));
    redoToolButton->setIcon(QIcon(QPixmap(":/images/redo.png")));
    redoToolButton->setToolTip(tr("Redo the last undone action <span style=\"color:gray;\">Ctrl+Shift+Z</span>"));
    redoToolButton->setEnabled(false);
    connect(redoToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->redo();});
    connect(tabWidget, &TabWidget::canRedoChange, redoToolButton, &QToolButton::setEnabled);

    removeToolButton = new QToolButton;
    removeToolButton->setIconSize(QSize(50, 50));
    removeToolButton->setIcon(QIcon(QPixmap(":/images/edit-delete.png")));
    removeToolButton->setToolTip(tr("Remove the selected items <span style=\"color:gray;\">Del</span> "));
    connect(removeToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->removeItems();});

    cursorToolButton = new QToolButton;
    cursorToolButton->setIconSize(QSize(50, 50));
    cursorToolButton->setCheckable(true);
    cursorToolButton->setIcon(QIcon(QPixmap(":/images/cursor.png")));
    cursorToolButton->setToolTip(tr("Normal cursor"));

    addPlaceToolButton = new QToolButton;
    addPlaceToolButton->setIconSize(QSize(50, 50));
    addPlaceToolButton->setCheckable(true);
    addPlaceToolButton->setIcon(QIcon(QPixmap(":/images/place.png")));
    addPlaceToolButton->setToolTip(tr("Add places"));

    addTransToolButton = new QToolButton;
    addTransToolButton->setIconSize(QSize(50, 50));
    addTransToolButton->setCheckable(true);
    addTransToolButton->setIcon(QIcon(QPixmap(":/images/transition.png")));
    addTransToolButton->setToolTip(tr("Add transitions"));

    drawArcToolButton = new QToolButton;
    drawArcToolButton->setIconSize(QSize(50, 50));
    drawArcToolButton->setCheckable(true);
    drawArcToolButton->setIcon(QIcon(QPixmap(":/images/arc.png")));
    drawArcToolButton->setToolTip(tr("Draw Polylines Arcs"));
    //仿真
    animateToolButton = new QToolButton;
    animateToolButton->setIconSize(QSize(50, 50));
    animateToolButton->setCheckable(true);
    animateToolButton->setIcon(QIcon(QPixmap(":/images/animate.png")));
    animateToolButton->setToolTip(tr("Simulation"));

    //按钮组设置,指定按钮的id
    buttonGroup = new QButtonGroup (this);
    buttonGroup->addButton(cursorToolButton,normalMode);
    buttonGroup->addButton(addPlaceToolButton, addPlaceMode);
    buttonGroup->addButton(addTransToolButton, addTransMode);
    buttonGroup->addButton(drawArcToolButton, drawArcMode);
    buttonGroup->addButton(animateToolButton,animationMode);
    //设定按钮组互斥,设置为true，按钮组中的按钮每次都只能够有一个被选中
    buttonGroup->setExclusive(true);
    void (QButtonGroup::*btnClicked)(int)=&QButtonGroup::buttonClicked;
    void (MainWindow::*btnOnClicked)(int)=&MainWindow::buttonGroupClicked;
    connect(buttonGroup, btnClicked,this, btnOnClicked);


    //默认选中光标按钮
    cursorToolButton->setChecked (true);

    //添加工具栏按钮
    toolBar = new QToolBar;
    toolBar->addWidget(newToolButton);
    toolBar->addWidget(openToolButton);
    toolBar->addWidget(saveToolButton);
    toolBar->addWidget(saveAsToolButton);
    toolBar->addWidget(printToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(undoToolButton);
    toolBar->addWidget(redoToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(removeToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(cursorToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(addPlaceToolButton);
    toolBar->addWidget(addTransToolButton);
    toolBar->addWidget(drawArcToolButton);
        toolBar->addSeparator ();
    toolBar->addWidget(animateToolButton);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea | Qt::RightToolBarArea);
    addToolBar(Qt::LeftToolBarArea, toolBar);
}

/*
 * 初始化菜单栏
 *  */
void MainWindow::createMenuBar()
{
    //菜单栏
     QMenuBar *m_Bar = menuBar();
     m_Bar->showMaximized();

    //在菜单栏上添加开始菜单File
    fileMenu = m_Bar->addMenu(tr("&File"));
    //在File菜单上添加子菜单项（添加动作）“New Net” 快捷键为"Ctrl+N"
    // triggered信号表示：点击后触发
    newMenuAct = fileMenu->addAction(tr("&New Net"));
    newMenuAct->setIcon(QIcon(QPixmap(":/images/widow-new.png")));
    newMenuAct->setShortcut(QKeySequence("Ctrl+N"));
        //qt5信号与槽lambda表达式
          connect(newMenuAct,&QAction::triggered,this,[=](){this->tabWidget->createNew();});
    openMenuAct = fileMenu->addAction(tr("&Open Net"));
    openMenuAct->setIcon(QIcon(QPixmap(":/images/folder-open.png")));
    openMenuAct->setShortcut(QKeySequence("Ctrl+O"));
          connect(openMenuAct,&QAction::triggered,this,[=](){this->open();});
            //添加分隔线
            fileMenu->addSeparator();
    saveMenuAct = fileMenu->addAction(tr("&Save"));
    saveMenuAct->setIcon(QIcon(QPixmap(":/images/document-save.png")));
    saveMenuAct->setShortcut(QKeySequence("Ctrl+S"));
          connect(saveMenuAct,&QAction::triggered,this,[=](){this->tabWidget->save();});
    saveAsMenuAct = fileMenu->addAction(tr("&Save as"));
    saveAsMenuAct->setIcon(QIcon(QPixmap(":/images/saveAs.png")));
    saveAsMenuAct->setShortcut(QKeySequence("F12"));
          connect(saveAsMenuAct,&QAction::triggered,this,[=](){this->tabWidget->saveAs();});
    exportMenuAct = fileMenu->addAction(tr("&Export"));
    exportMenuAct->setShortcut(QKeySequence("Ctrl+E"));
          connect(exportMenuAct,&QAction::triggered,this,[=](){this->tabWidget->exportNet();});
    printMenuAct = fileMenu->addAction(tr("&Print"));
    printMenuAct->setIcon(QIcon(QPixmap(":/images/printer.png")));
    printMenuAct->setShortcut(QKeySequence("Ctrl+P"));
           connect(printMenuAct,&QAction::triggered,this,[=](){this->tabWidget->print();});
           fileMenu->addSeparator();
    quitMenuAct = fileMenu->addAction(tr("&Exit"));
    quitMenuAct->setIcon(QIcon::fromTheme("application-exit"));
    quitMenuAct->setShortcut(QKeySequence("Ctrl+Q"));
            connect(quitMenuAct,&QAction::triggered,this,[=](){this->close();});

    //编辑菜单
    editMenu = m_Bar->addMenu(tr("&Edit"));
    undoMenuAct = editMenu->addAction(tr("&Undo"));
    undoMenuAct->setIcon(QIcon(QPixmap(":/images/undo.png")));
    undoMenuAct->setShortcut(QKeySequence("Ctrl+Z"));
    undoMenuAct->setEnabled(false);
          connect(undoMenuAct,&QAction::triggered,this,[=](){this->tabWidget->undo();});
          connect(tabWidget, &TabWidget::canUndoChange, undoMenuAct,&QAction::setEnabled);

    redoMenuAct = editMenu->addAction(tr("&Redo"));
    redoMenuAct->setIcon(QIcon(QPixmap(":/images/redo.png")));
    redoMenuAct->setShortcut(QKeySequence("Ctrl+Shift+Z"));
    redoMenuAct->setEnabled(false);
         connect(redoMenuAct,&QAction::triggered,this,[=](){this->tabWidget->redo();});
         connect(tabWidget, &TabWidget::canUndoChange,redoMenuAct,&QAction::setEnabled);
            editMenu->addSeparator();
    removeMenuAct = editMenu->addAction(tr("&Delete"));
    removeMenuAct->setIcon(QIcon(QPixmap(":/images/edit-delete.png")));
    removeMenuAct->setShortcut(QKeySequence("Del"));
          connect(removeMenuAct,&QAction::triggered,this,[=](){this->tabWidget->removeItems();});

    //建模菜单
    m_modelingMenu = m_Bar->addMenu(tr("&Elements"));
    m_placeMenuAct = m_modelingMenu->addAction(tr("&Place"));
    m_placeMenuAct->setIcon(QIcon(QPixmap(":/images/place.png")));
          connect(m_placeMenuAct,&QAction::triggered,this,[=](){this->addPlaceToolButton->click();});
    m_transitionMenuAct = m_modelingMenu->addAction(tr("&Transition"));
    m_transitionMenuAct->setIcon(QIcon(QPixmap(":/images/transition.png")));
          connect(m_transitionMenuAct,&QAction::triggered,this,[=](){this->addTransToolButton->click();});
    m_arcMenuAct = m_modelingMenu->addAction(tr("Arcs"));
    m_arcMenuAct->setIcon(QIcon(QPixmap(":/images/arc.png")));
          connect(m_arcMenuAct,&QAction::triggered,this,[=](){this->drawArcToolButton->click();});

     //组件库菜单
     componentMenu =m_Bar->addMenu(tr("&Component"));
     saveComponentAction = componentMenu->addAction(tr("&Save Component"));
     saveComponentAction->setIcon(QIcon(QPixmap(":/images/componentSave.png")));
         connect(saveComponentAction,&QAction::triggered,this,[=](){this->tabWidget->saveComponent();});
                componentMenu->addSeparator();
     openComponentAction = componentMenu->addAction(tr("&Open Component"));
     openComponentAction->setIcon(QIcon(QPixmap(":/images/componentLibrary.png")));
//         connect(aboutMenuAct,&QAction::triggered,this,[=](){this->about();});

     //规则库菜单
     ruleMenu=m_Bar->addMenu(tr("&Rule"));
     openRuleLibraryAction=ruleMenu->addAction(tr("&Open Rule Library"));
     connect(openRuleLibraryAction,&QAction::triggered,this,[=](){this->openRuleLibrary();});

     //帮助菜单
     helpMenu =m_Bar->addMenu(tr("&Help"));
     aboutMenuAct = helpMenu->addAction(tr("&About"));
     aboutMenuAct->setIcon(QIcon::fromTheme("help-about"));
     aboutMenuAct->setShortcut(QKeySequence("Ctrl+B"));
         connect(aboutMenuAct,&QAction::triggered,this,[=](){this->about();});
}


/*
 * 当鼠标移到滑块时，光标处浮出一个tooltip文本，内容是用户放大倍数。
 *  */
void MainWindow::sliderValueChanged(int value)
{
    QVariant v(value - 50);
    slider->setToolTip(v.toString()+" %");
    QToolTip::showText ( slider->mapToGlobal(QPoint(value-20, 0)), QString(v.toString()+" %"), slider);
}
/*
 * 初始化状态栏
 *  */
void MainWindow::createStatusBar ()
{
    statusBar = new QStatusBar;
    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(150);
    slider->setFixedWidth(150);
    slider->setRange(50, 150);
    slider->setSliderPosition(100);
    statusBar->addPermanentWidget(slider);
    setStatusBar(statusBar);

    connect(slider, &QSlider::valueChanged, tabWidget, &TabWidget::zoom);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::sliderValueChanged);

}
/* 可移动控件 */
void MainWindow::createDocks ()
{
    buttomDock = new DockWidget(this);
    addDockWidget(Qt::BottomDockWidgetArea, buttomDock);
    buttomDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    buttomDock->setMaximumHeight(150);
    buttomDock->show ();

}
/*
 * 点击按钮组触发的槽函数
 * enum{normalMode=0, animationMode=1, addPlaceMode=2, \
            addTransMode=3,drawArcMode=4, addToken=5, subToken=6};
    仿真(animateToolButton,animationMode);
 *  */
void MainWindow::buttonGroupClicked(int id)
{
    //QTabWidget的currentWidget方法用于获取选项卡的当前显示页面的实例对象。
    PetriTabWidget* tab = qobject_cast<PetriTabWidget*>(tabWidget->currentWidget ());
    tab->setMode (id);
    updateWidgets (id);
}
/* 当窗口改变时更新按钮*/
void MainWindow::updateWidgets (int mode)
{
    bool disable;

    if(mode == animationMode)
        disable = true;
    else
        disable = false;

    saveMenuAct->setDisabled (disable);
    saveToolButton->setDisabled (disable);
    saveAsMenuAct->setDisabled (disable);
    saveAsToolButton->setDisabled (disable);
    printMenuAct->setDisabled (disable);
    printToolButton->setDisabled (disable);
    addPlaceToolButton->setDisabled (disable);
    addTransToolButton->setDisabled (disable);
    drawArcToolButton->setDisabled (disable);
    m_placeMenuAct->setDisabled(disable);
    m_transitionMenuAct->setDisabled(disable);
    m_arcMenuAct->setDisabled(disable);
    removeMenuAct->setDisabled(disable);
    removeToolButton->setDisabled(disable);
    exportMenuAct->setDisabled(disable);

    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(tabWidget->currentWidget());

    if (mode != animationMode)
    {
//        redoToolButton->setEnabled(tab->canRedo());
//        undoToolButton->setEnabled(tab->canUndo());
//        redoMenuAct->setEnabled (tab->canRedo());
//        undoMenuAct->setEnabled (tab->canUndo());
    }else
    {
        redoToolButton->setEnabled(false);
        undoToolButton->setEnabled(false);
        redoMenuAct->setEnabled (false);
        undoMenuAct->setEnabled (false);
    }
}
/*子窗口切换 */
void MainWindow::tabChanged(int index)
{

}


void MainWindow::open ()
{
    statusBar->showMessage("Open an existing PNML document ...");
    if(tabWidget->open(buttomDock->getMessageHandler()))
        statusBar->showMessage("Document loaded and opened.", 1000);
    else
        statusBar->showMessage("Document was not opened.", 1000);
}
void MainWindow::about()
{

}
void MainWindow::openRuleLibrary()
{
    editRuleLibrary* editRuleDialog=new editRuleLibrary(this);
    editRuleDialog->show();
}

MainWindow::~MainWindow()
{
    delete newToolButton;
    delete openToolButton;
    delete saveToolButton;
    delete undoToolButton;
    delete redoToolButton;
    delete removeToolButton;
    delete cursorToolButton;
    delete addPlaceToolButton;
    delete addTransToolButton;
    delete drawArcToolButton;
    delete printToolButton;
    delete animateToolButton;

    delete toolBar;
    delete tabWidget;

    delete buttomDock;
    delete slider;
    delete statusBar;
}
