#include "mainwindow.h"
#include "editrulelibrary.h"
#include "simulation/plot.h"
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

      this->comType="A";
       //editcommenu=new neweditcom(this);

      //初始化
      createToolBar ();
      createMenuBar();
      createDocks ();
      createStatusBar ();
      createComponentDock();
      component_controller=new componentController();
      //test
      //component_controller->WriteListFile();
      //component_controller->ReadListFile();
      connect(tabWidget, &TabWidget::currentChanged,this,&MainWindow::tabChanged);
      connect (tabWidget, &TabWidget::addComponentTreeNode,this, &MainWindow::setComponentTreeNode);
      connect(tabWidget,&TabWidget::errorMessage,buttomDock,&DockWidget::showMessage);
      //不要调整顺序
      connect(tabWidget,&TabWidget::addComponentFinished,tabWidget,&TabWidget::setImportComponentId_AND_classsifyComponenet);
      connect(this,&MainWindow::addComponentController,tabWidget,&TabWidget::addComponent);
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
    //仿真操作要在这个信号上面
    //初始化
    connect(this->tabWidget,&TabWidget::startSimulation,this->tabWidget->com_list,&ComponentList::getPTNScene);
    connect(this->tabWidget,&TabWidget::startSimulation,this->tabWidget->com_list,[=](){tabWidget->com_list->intiCom_list(tabWidget->getcom_arry());});
    //connect(this->tabWidget,&TabWidget::startSimulation,this->tabWidget,&TabWidget::gets);
    connect(animateToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->saveModel();});
    //connect(animateToolButton,&QToolButton::clicked,this,[=](){emit passCom_arry(this->tabWidget->getcom_arry());});
    //connect(this,&MainWindow::passCom_arry,compound_component_list,&CompoundComponentList::getCompoundComponentList);


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
         connect(openComponentAction,&QAction::triggered,this,[=](){this->openComponent();});
               componentMenu->addSeparator();
     openComponentDockAction = componentMenu->addAction(tr("&Open ComponentDock"));
         connect(openComponentDockAction,&QAction::triggered,this,[=](){this->openComponentDock();});

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
//组件库浮动窗口
void MainWindow::createComponentDock()
{
    componentDock = new QDockWidget(tr("组件库"),this);
    addDockWidget(Qt::RightDockWidgetArea, componentDock);
    componentDock->setAllowedAreas(Qt::RightDockWidgetArea);
    componentDock->setMinimumWidth(475);
    newComponent=new QToolButton();
    deleteComponent=new QToolButton();
    addComponent=new QToolButton();
    unbindComponent=new QToolButton();
    componentTree=new QTreeWidget();

    //---------不要调整下面connect顺序，会报错--------------------
    newComponent->setText(tr("保存"));
    connect(tabWidget,&TabWidget::saveComponentFinished,tabWidget,&TabWidget::setElementId);
    //connect(tabWidget,&TabWidget::ElementIdEditFinished,tabWidget,&TabWidget::saveComponent);
    //connect(editcommenu,&neweditcom::editFinished,editcommenu,[=](){editcommenu->close();});
    //connect(this,&MainWindow::createComponentFinished,this,[=](){

        //获取用户输入的type
        //this->component_controller->newtype=this->comType;
        //不再需要文件操作了
//        this->component_controller->ReadListFile();
//        this->component_controller->WriteListFile();
//        this->component_controller->ReadListFile();
        //this->component_controller->type_list.insert()
        //tabWidget->componentTypeNum=1;
    //});
    //connect(editcommenu,&neweditcom::editFinished,tabWidget,&TabWidget::ElementIdEditFinished);
    //connect(editcommenu,&neweditcom::typechange,this,&MainWindow::changecomType);
    //connect(editcommenu,&neweditcom::typechange,tabWidget,&TabWidget::setComponentType);
    //connect(newComponent,&QToolButton::clicked,this,[=](){this->editcommenucreate();});
    connect(newComponent,&QToolButton::clicked,tabWidget,&TabWidget::saveComponent);

    deleteComponent->setText(tr("删除"));
    deleteComponent->setToolTip(tr("Delete a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(deleteComponent,&QToolButton::clicked,this,[=](){this->deleteComponentTreeNode(componentTree);});
    addComponent->setText(tr("导入"));
    addComponent->setToolTip(tr("Open and add a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(this,&MainWindow::importComponentFinished,tabWidget,&TabWidget::setImportComponentId_AND_classsifyComponenet);//bug
    connect(addComponent,&QToolButton::clicked,this,[=](){this->openComponent();});

    unbindComponent->setText(tr("解除绑定"));
    unbindComponent->setToolTip(tr("Unbind  a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(unbindComponent,&QToolButton::clicked,this,[=](){this->unbindingComponent();});

    componentBar=new QToolBar();

    componentBar->addWidget(newComponent);
    componentBar->addWidget(deleteComponent);
    componentBar->addWidget(addComponent);
     componentBar->addWidget(unbindComponent);
    componentBar->setAllowedAreas(Qt::TopToolBarArea);
    addToolBar(componentBar);

    component_controller=new componentController();
    component_controller->componentTreeInitial(componentTree);
    componentTree->expandAll();
    componentEditMenu=new QMenu();
    editComponentAction=componentEditMenu->addAction(tr("编辑"));
    addComponentAction=componentEditMenu->addAction(tr("添加组件"));

    QVBoxLayout* VerticalLayout=new QVBoxLayout(componentDock);
    QWidget *mywid1 = new QWidget();
    VerticalLayout->addWidget(componentBar);
    VerticalLayout->addWidget(componentTree);
    mywid1->setLayout(VerticalLayout);
    emit passComponnetController(component_controller);
    connect(componentTree,&QTreeWidget::itemPressed,this,[=](){this->componentPopMenu();});

    connect(editComponentAction,&QAction::triggered,this,[=](){this->openEditComponent();});
    connect(addComponentAction,&QAction::triggered,this,[=](){this->addEditComponent(componentTree);
    connect(this,&MainWindow::passComponnetController,this->tabWidget->com_list,&ComponentList::getComponent);

    });
    componentDock->setWidget(mywid1);
    componentDock->show ();
}

void MainWindow::componentPopMenu()
{
    componentEditMenu->exec(QCursor::pos());
}

void MainWindow::Tex(QString tex)
{
    qDebug()<<tex;
}

//void MainWindow::editcommenucreate()
//{

//    editcommenu->show();
//}
//当且仅当用户新建组件时触发
void MainWindow::changecomType(QString text)
{
    this->comType=text;
    emit createComponentFinished();
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

    if(id == animationMode)
    {
        buttomDock->show();
        if(!tab->checkNet())
        {
            tab->setMode (normalMode);
                return;
        }
        else
        {
            tab->setMode (animationMode);

            //清空原页面数据
            e_mInputVaraible2Value[tab->getId()].clear();
            e_vFunDef[tab->getId()].clear();
            //加载当前页面数据
            PTNET_ATTR net=tab->toXml();
            QList<ARC_ATTR>arcs=net.pages[0].arcs;
            QList<TRANSITION_ATTR>transitionNodes=net.pages[0].transitionNodes;
            QList<PLACE_ATTR>placeNodes=net.pages[0].placeNodes;
            /*
            *输出每条边的来源和去向
            for(int i=0;i<arcs.size();i++)
            {
                qDebug()<<"ARC "<<arcs[i].id<<" FROM "<<arcs[i].source<<" TO "<<arcs[i].target<<endl;
            }*/

            //用l_mtemp记录弧和其来源(包含权重信息，完整为(来源库所名字+"^"+权重))
            map<QString,QString>l_mtemp;
            for(int i=0;i<arcs.size();i++)
            {
                //qDebug()<<arcs.size();
                QString l_stemp;
                for(int j=0;j<placeNodes.size();j++)
                {
                    if(placeNodes[j].id==arcs[i].source)
                    {
                        l_stemp.append(placeNodes[j].name);
                        //qDebug()<<placeNodes[j].name;
                        break;
                    }
                }
                //记录ode中前置库所对应的指数
                l_stemp.append("^("+QString::number(arcs[i].weight)+")");
                //保存反应物和系数
                l_mtemp[arcs[i].id]=l_stemp;
            }
            QVector<QString> samename;
            int recordpos;
            //对于每个PLACE
            for(int i=0;i<placeNodes.size();i++)
            {
                int havesame=0;
                //qDebug()<<"the size of samename is "<<samename.size();
                //检测库所名字是否重复
                for(int j=0;j<samename.size();j++)
                {
                    if(samename[j]==placeNodes[i].name)
                    {
                        havesame=1;
                        break;
                    }
                }
                e_mInputVaraible2Value[tab->getId()][placeNodes[i].name.toStdString()]=placeNodes[i].initmark;
                FUNCTIONDEF l_FunDef;
                if(havesame==0)
                {
                    l_FunDef.m_sDifferentialName=placeNodes[i].name.toStdString();
                    l_FunDef.m_sFunctionExp="";
                }
                else
                {
                    for(unsigned j=0;j<e_vFunDef[tab->getId()].size();j++)
                    {
                        if(e_vFunDef[tab->getId()][j].m_sDifferentialName==placeNodes[i].name.toStdString())
                        {
                            l_FunDef=e_vFunDef[tab->getId()][j];
                            recordpos=int(j);
                            break;
                        }
                    }
                }
                //查找与PLACE相连的N条ARC
                for(int j=0;j<arcs.size();j++)
                {
                    //PLACE为该ARC起点
                    if(arcs[j].source==placeNodes[i].id)
                    {
                        //qDebug()<<placeNodes[i].name<<"is the source of"<<arcs[j].id;
                        for(int k=0;k<transitionNodes.size();k++)
                        {
                            //找到该ARC的终点TRANSITION
                            if(transitionNodes[k].id==arcs[j].target)
                            {
                                //向函数表达式中增加负项因子
                                l_FunDef.m_sFunctionExp.append("-1*(");
                                l_FunDef.m_sFunctionExp.append(QString::number(arcs[j].weight).toStdString());
                                l_FunDef.m_sFunctionExp.append(")*(");
                                //如果变迁（反应）速率符合质量作用定律
                                if(transitionNodes[k].self_function.contains("MassAction"))
                                    {
                                        QString temp=(transitionNodes[k].self_function.split("MassAction"))[1];
                                        for(int m=0;m<transitionNodes.size();m++)
                                        {
                                            //？？？同名变迁同步
                                            if(transitionNodes[m].name==transitionNodes[k].name&&m!=k)
                                            {
                                                //通过寻找前置弧来寻找该反应（变迁）对应的反应物（消耗的库所）
                                                for(int p=0;p<arcs.size();p++)
                                                {
                                                    //找到反应物后继续补充反应速率因子
                                                    if(arcs[p].target==transitionNodes[m].id)
                                                    {
                                                        temp.append("*(");
                                                        temp.append(l_mtemp[arcs[p].id]);
                                                        temp.append(")");
                                                    }
                                                }
                                            }
                                        }
                                        //通过寻找前置弧来寻找该反应（变迁）对应的反应物（消耗的库所）
                                        for(int m=0;m<arcs.size();m++)
                                        {
                                            //找到反应物后继续补充反应速率因子
                                            if(arcs[m].target==transitionNodes[k].id)
                                            {
                                                temp.append("*(");
                                                temp.append(l_mtemp[arcs[m].id]);
                                                temp.append(")");
                                            }
                                        }
                                        l_FunDef.m_sFunctionExp.append(temp.toStdString());
                                    }
                                //否则反应速率为参数*反应物名字（其余为非法结构,之后在解析表达式时需要对此进行检测）
                                else
                                    {
                                        l_FunDef.m_sFunctionExp.append(transitionNodes[k].self_function.toStdString());
                                    }
                                l_FunDef.m_sFunctionExp.append(")");
                                break;
                            }
                        }
                    }
                    //PLACE为该ARC终点
                    else if(arcs[j].target==placeNodes[i].id)
                    {
                        //qDebug()<<placeNodes[i].name<<"is the target of"<<arcs[j].id;
                        for(int k=0;k<transitionNodes.size();k++)
                        {
                            //找到该ARC的起点TRANSITION
                            if(transitionNodes[k].id==arcs[j].source)
                            {
                                {
                                    //如果该库所只作为生成物
                                    if(l_FunDef.m_sFunctionExp=="")
                                        l_FunDef.m_sFunctionExp.append("1*(");
                                    //如果该库所为反应物和生成物
                                    else
                                        l_FunDef.m_sFunctionExp.append("+1*(");
                                    l_FunDef.m_sFunctionExp.append(QString::number(arcs[j].weight).toStdString());
                                    l_FunDef.m_sFunctionExp.append(")*(");
                                    if(transitionNodes[k].self_function.contains("MassAction"))
                                    {
                                        QString temp=(transitionNodes[k].self_function.split("MassAction"))[1];
                                        for(int m=0;m<transitionNodes.size();m++)
                                        {
                                            if(transitionNodes[m].name==transitionNodes[k].name&&m!=k)
                                            {
                                                for(int p=0;p<arcs.size();p++)
                                                {
                                                    if(arcs[p].target==transitionNodes[m].id)
                                                    {
                                                        temp.append("*(");
                                                        temp.append(l_mtemp[arcs[p].id]);
                                                        temp.append(")");
                                                    }
                                                }
                                            }
                                        }
                                        for(int m=0;m<arcs.size();m++)
                                        {
                                            if(arcs[m].target==transitionNodes[k].id)
                                            {
                                                temp.append("*(");
                                                temp.append(l_mtemp[arcs[m].id]);
                                                temp.append(")");
                                            }
                                        }
                                        l_FunDef.m_sFunctionExp.append(temp.toStdString());
                                    }
                                    else
                                    {
                                        l_FunDef.m_sFunctionExp.append(transitionNodes[k].self_function.toStdString());
                                    }
                                    l_FunDef.m_sFunctionExp.append(")");
                                }
                            }
                        }
                    }
                }
                if(l_FunDef.m_sFunctionExp=="")
                    l_FunDef.m_sFunctionExp="0";
                if(havesame==0)
                {
                    e_vFunDef[tab->getId()].push_back(l_FunDef);
                    samename.push_back(placeNodes[i].name);
                }
                else
                {
                    e_vFunDef[tab->getId()][recordpos]=l_FunDef;
                }
            }
            Plot* view = new Plot();
            view->setPlotId(tab->getId());
            /*
            QString e = tab->getId();
            QFile file("./used_to_record_the_id.txt");
            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                file.write(e.toUtf8());
                file.close();
            }
            else
            {
                QMessageBox::information(this,QString("Error!"),QString("Unable to write the file."));
            }*/
            view->show();
         }
        tabWidget->openLocalComponent();
    }

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
void MainWindow::openComponent()
{
    statusBar->showMessage("Open an existing Component ...");
    if(tabWidget->openComponent(buttomDock->getMessageHandler()))
        statusBar->showMessage("Component loaded and opened.", 1000);
    else
        statusBar->showMessage("Component was not opened.", 1000);
    emit importComponentFinished();
}
void MainWindow::unbindingComponent()
{
    tabWidget->unbindComponent();
}

void MainWindow::openComponentDock()
{
    componentDock->show ();
}
void MainWindow::about()
{

}
void MainWindow::openRuleLibrary()
{
    editRuleLibrary* editRuleDialog=new editRuleLibrary(this);
    editRuleDialog->show();
}
void MainWindow::setComponentTreeNode(QString componentName,QString componentPath)
{
    component_controller->addComponentTreeNode(componentTree,componentName,componentPath);
}
//删除当前组件库浮动窗口上的组件
void MainWindow::deleteComponentTreeNode(QTreeWidget* tree)
{
    QTreeWidgetItem * currentItem = tree->currentItem();//获取当前节点
    component_controller->removeComponentTreeNode(currentItem);
}
//点击当前组件浮动窗口上的组件弹出编辑窗口，暂时只有修改组件类型和组件名操作，并且未与文件操作联通
//后期可在编辑界面加入多个merge和delete操作
void MainWindow::openEditComponent()
{
    editComponent* editComponentDialog=new editComponent(this);
    editComponentDialog->show();
    connect(editComponentDialog,&editComponent::editComponentInfo,this,&MainWindow::editComponentInfo);
}
void MainWindow::addEditComponent(QTreeWidget* tree)
{
    QTreeWidgetItem * currentItem = tree->currentItem();//获取当前节点
    QString component_path=currentItem->text(1);
    emit addComponentController(component_path);

}
void MainWindow::editComponentInfo(QString componentName)
{
    QTreeWidgetItem * currentItem = componentTree->currentItem();//获取当前节点
    currentItem->setText(0,componentName);
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
    delete componentDock;

    delete newComponent;
    delete addComponent;
    delete deleteComponent;
    delete componentBar;
    //delete editcommenu;
}
