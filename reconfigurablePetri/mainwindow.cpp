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
      tabWidget = new TabWidget(this);
      setCentralWidget (tabWidget);

      this->comType="A";
       //editcommenu=new neweditcom(this);

      //初始化
      createToolBar ();
      createMenuBar();
      createDocks ();
      createStatusBar ();
      connect(this,&MainWindow::passComponnetController,tabWidget,&TabWidget::setComponent);
      createComponentDock();
      component_controller=new ComponentController();
      //test
      //component_controller->WriteListFile();
      //component_controller->ReadListFile();
      connect(tabWidget, &TabWidget::currentChanged,this,&MainWindow::tabChanged);
      connect (tabWidget, &TabWidget::addComponentTreeNode,this, &MainWindow::setComponentTreeNode);
      connect(tabWidget,&TabWidget::errorMessage,buttomDock,&DockWidget::showMessage);
      //不要调整顺序
      //PetriTabWidget*tab=qobject_cast<PetriTabWidget*>(tabWidget->currentWidget ());
      connect(tabWidget,&TabWidget::addComponentFinished,tabWidget,&TabWidget::setImportComponentId_AND_classsifyComponenet);
      connect(this,&MainWindow::addComponentController,tabWidget,&TabWidget::addComponent);
}

/*
 * 初始化工具栏
 *  */
void MainWindow::createToolBar ()
{
    //增加新widget页面按钮
    newToolButton = new QToolButton(this);
    newToolButton->setIconSize(QSize(50, 50));
    newToolButton->setIcon(QIcon(QPixmap(":/images/widow-new.png")));
    newToolButton->setToolTip(tr("Create a new Petri Net <span style=\"color:gray;\">Ctrl+N</span>"));
    connect(newToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->createNew();});
    //打开文件
    openToolButton = new QToolButton(this);
    openToolButton->setIconSize(QSize(50, 50));
    openToolButton->setIcon(QIcon(QPixmap(":/images/folder-open.png")));
    openToolButton->setToolTip(tr("Open a Petri Net document <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(openToolButton,&QToolButton::clicked,this,[=](){this->open();});

    saveToolButton = new QToolButton(this);
    saveToolButton->setIconSize(QSize(50, 50));
    saveToolButton->setIcon(QIcon(QPixmap(":/images/document-save.png")));
    saveToolButton->setToolTip(tr("Save the current Petri Net <span style=\"color:gray;\">Ctrl+S</span>"));
    connect(saveToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->save();});


    saveAsToolButton = new QToolButton(this);
    saveAsToolButton->setIconSize(QSize(50, 50));
    saveAsToolButton->setIcon(QIcon(QPixmap(":/images/saveAs.png")));
    saveAsToolButton->setToolTip(tr("Save the current Petri Net as <span style=\"color:gray;\">F12</span>"));
    connect(saveAsToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->saveAs();});
    printToolButton = new QToolButton(this);
    printToolButton->setIconSize(QSize(50, 50));
    printToolButton->setIcon(QIcon(QPixmap(":/images/printer.png")));
    printToolButton->setToolTip(tr("Print <span style=\"color:gray;\">Ctrl+P</span>"));
    connect(printToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->print();});

    undoToolButton = new QToolButton(this);
    undoToolButton->setIconSize(QSize(50, 50));
    undoToolButton->setIcon(QIcon(QPixmap(":/images/undo.png")));
    undoToolButton->setToolTip(tr("Undo the last action <span style=\"color:gray;\">Ctrl+Z</span>"));
    undoToolButton->setEnabled(false);
    connect(undoToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->undo();});
    connect(tabWidget, &TabWidget::canUndoChange, undoToolButton, &QToolButton::setEnabled);

    redoToolButton = new QToolButton(this);
    redoToolButton->setIconSize(QSize(50, 50));
    redoToolButton->setIcon(QIcon(QPixmap(":/images/redo.png")));
    redoToolButton->setToolTip(tr("Redo the last undone action <span style=\"color:gray;\">Ctrl+Shift+Z</span>"));
    redoToolButton->setEnabled(false);
    connect(redoToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->redo();});
    connect(tabWidget, &TabWidget::canRedoChange, redoToolButton, &QToolButton::setEnabled);

    removeToolButton = new QToolButton(this);
    removeToolButton->setIconSize(QSize(50, 50));
    removeToolButton->setIcon(QIcon(QPixmap(":/images/edit-delete.png")));
    removeToolButton->setToolTip(tr("Remove the selected items <span style=\"color:gray;\">Del</span> "));
    connect(removeToolButton,&QToolButton::clicked,this,[=](){this->tabWidget->removeItems();});

    cursorToolButton = new QToolButton(this);
    cursorToolButton->setIconSize(QSize(50, 50));
    cursorToolButton->setCheckable(true);
    cursorToolButton->setIcon(QIcon(QPixmap(":/images/cursor.png")));
    cursorToolButton->setToolTip(tr("Normal cursor"));

    addPlaceToolButton = new QToolButton(this);
    addPlaceToolButton->setIconSize(QSize(50, 50));
    addPlaceToolButton->setCheckable(true);
    addPlaceToolButton->setIcon(QIcon(QPixmap(":/images/place.png")));
    addPlaceToolButton->setToolTip(tr("Add places"));

    addTransToolButton = new QToolButton(this);
    addTransToolButton->setIconSize(QSize(50, 50));
    addTransToolButton->setCheckable(true);
    addTransToolButton->setIcon(QIcon(QPixmap(":/images/transition.png")));
    addTransToolButton->setToolTip(tr("Add transitions"));

    drawArcToolButton = new QToolButton(this);
    drawArcToolButton->setIconSize(QSize(50, 50));
    drawArcToolButton->setCheckable(true);
    drawArcToolButton->setIcon(QIcon(QPixmap(":/images/arc.png")));
    drawArcToolButton->setToolTip(tr("Draw Polylines Arcs"));

    drawConnectorToolButton= new QToolButton(this);
    drawConnectorToolButton->setIconSize(QSize(50,50));
    drawConnectorToolButton->setCheckable(true);
    drawConnectorToolButton->setIcon(QIcon(QPixmap(":/images/connector.png")));
    drawConnectorToolButton->setToolTip(tr("Draw Connectors"));

    //仿真
    animateToolButton = new QToolButton(this);
    animateToolButton->setIconSize(QSize(50, 50));
    animateToolButton->setCheckable(true);
    animateToolButton->setIcon(QIcon(QPixmap(":/images/animate.png")));
    animateToolButton->setToolTip(tr("Simulation"));
    //仿真操作要在这个信号上面
    //初始化
    //PetriTabWidget*tab=qobject_cast<PetriTabWidget*>(tabWidget->currentWidget ());
    connect(this->tabWidget,&TabWidget::startSimulation,tabWidget->com_list,&ComponentList::getPTNScene);
    connect(this->tabWidget,&TabWidget::startSimulation,tabWidget->com_list,[&](){
        tabWidget->com_list->intiCom_list(tabWidget->getcom_arry());
        tabWidget->com_list->initConnector_list(tabWidget->init_cl());
        ///将component_controller传入com_list中
        tabWidget->com_list->setComponentController(component_controller);
    });
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
    buttonGroup->addButton(drawConnectorToolButton,drawConnectorMode);
    buttonGroup->addButton(animateToolButton,animationMode);
    //设定按钮组互斥,设置为true，按钮组中的按钮每次都只能够有一个被选中
    buttonGroup->setExclusive(true);
    void (QButtonGroup::*btnClicked)(int)=&QButtonGroup::buttonClicked;
    void (MainWindow::*btnOnClicked)(int)=&MainWindow::buttonGroupClicked;
    connect(buttonGroup, btnClicked,this, btnOnClicked);


    //默认选中光标按钮
    cursorToolButton->setChecked (true);

    //添加工具栏按钮
    toolBar = new QToolBar(this);
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
    toolBar->addWidget(drawConnectorToolButton);
        toolBar->addSeparator();
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
    statusBar = new QStatusBar(this);
    slider = new QSlider(Qt::Horizontal,this);
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
    newComponent=new QToolButton(this);
    deleteComponent=new QToolButton(this);
    addComponent=new QToolButton(this);
    bindComponent=new QToolButton(this);
    unbindComponent=new QToolButton(this);
    componentTree=new QTreeWidget();

    //---------不要调整下面connect顺序，会报错--------------------
    newComponent->setText(tr("保存新组件"));

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
    addComponent->setText(tr("导入组件"));
    addComponent->setToolTip(tr("Open and add a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(this,&MainWindow::importComponentFinished,tabWidget,&TabWidget::setImportComponentId_AND_classsifyComponenet);
    connect(addComponent,&QToolButton::clicked,this,[=](){this->openComponent();});
    bindComponent->setText(tr("绑定组件"));
    bindComponent->setToolTip(tr("Bbind  a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(bindComponent,&QToolButton::clicked,this,[=](){this->bindingComponent();});
    unbindComponent->setText(tr("解除绑定"));
    unbindComponent->setToolTip(tr("Unbind  a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(unbindComponent,&QToolButton::clicked,this,[=](){this->unbindingComponent();});

    componentBar=new QToolBar(this);

    componentBar->addWidget(newComponent);
    componentBar->addWidget(deleteComponent);
    componentBar->addWidget(addComponent);
    componentBar->addWidget(bindComponent);
    componentBar->addWidget(unbindComponent);
    componentBar->setAllowedAreas(Qt::TopToolBarArea);
    addToolBar(componentBar);

    component_controller=new ComponentController();
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
    //$
    connect(editComponentAction,&QAction::triggered,this,[=](){this->openEditComponent();});
    connect(addComponentAction,&QAction::triggered,this,[=](){

        this->addEditComponent(componentTree);

        connect(this,&MainWindow::passComponnetController,tabWidget->com_list,&ComponentList::getComponent);

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

        /***
         * 测试组件的数据
         */
        //发现：this的component_list无有效数据

        //现在
        ComponentList*comList=tabWidget->getCom_list();
        QVector<Component*>l_vTestComp=comList->getComponentList();

        //原来
        //QVector<Component*>l_vTestComp=tabWidget->com_list->getComponentList();

        //
//        for(int i=0;i<l_vTestComp.size();i++)
//        {
//            qDebug()<<l_vTestComp[i]->getID()<<" 's step is "<<l_vTestComp[i]->getStep();
//        }

//        for(int i=0;i<l_vTestComp.size();i++)
//        {
//            qDebug()<<"sdlkfsdf";
//            for(int j=0;j<l_vTestComp[i]->getArc_ATTRList().size();j++)
//            {
//                qDebug()<<l_vTestComp[i]->getArc_ATTRList()[j].id;
//            }
//            for(int p=0;p<l_vTestComp[i]->getPlace_ATTRList().size();p++)
//            {
//                qDebug()<<l_vTestComp[i]->getPlace_ATTRList()[p].id;
//            }
//            for(int t=0;t<l_vTestComp[i]->getTransition_ATTRList().size();t++)
//            {
//                qDebug()<<l_vTestComp[i]->getTransition_ATTRList()[t].id;
//            }
//            qDebug()<<"sdlkfsdf";
//        }

        //QWidget *QTabWidget::widget(int index) const


        if(!tab->checkNet())
        {
            tab->setMode (normalMode);
                return;
        }
        else
        {
            tab->setMode (animationMode);

            //创建仿真窗口
            Plot* view = new Plot();
            RuleManager *ruleManager =&tab->getRuleManager();
            view->setPlotId(tab->getId());
            //将com_list传入plot
            view->setComList(comList);
            //view->setComList(tabWidget->com_list);

            //将规则管理器传入plot
            view->setRuleManager(ruleManager);
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
    Ptab=tabWidget->getPetritab();
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
    drawConnectorToolButton->setDisabled(disable);
    drawArcToolButton->setDisabled (disable);
    m_placeMenuAct->setDisabled(disable);
    m_transitionMenuAct->setDisabled(disable);
    m_arcMenuAct->setDisabled(disable);
    removeMenuAct->setDisabled(disable);
    removeToolButton->setDisabled(disable);
    exportMenuAct->setDisabled(disable);

    //qDebug()<<"change page";
//    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(tabWidget->currentWidget());
//    PTNscene*s=tab->getSCene();
//    foreach(QGraphicsItem *item,s->items())
//    {
//        if(item->type()==Place::Type)
//        {
//            Place*p=qgraphicsitem_cast<Place*>(item);
//            qDebug()<<p->getId();
//        }
//        else if(item->type()==Transition::Type)
//        {
//            Transition*p=qgraphicsitem_cast<Transition*>(item);
//            qDebug()<<p->getId();
//        }
//    }
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
void MainWindow::bindingComponent()
{
    tabWidget->bindComponent();
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
    editRuleLibrary editRuleDialog(this);
    editRuleDialog.exec();
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
    connect(editComponentDialog,&editComponent::editComponentStep,this,&MainWindow::editComponentStep);
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
    QString oldComponentName=currentItem->text(0);
    currentItem->setText(0,componentName);
    foreach(Component* com,tabWidget->getPetritab()->getcom_arry())
    {
        if(com->getComponentFileName()==oldComponentName)
        {
            com->setID(componentName+'&'+com->getID().split("&")[1]);
        }
    }
    QMapIterator<QString,QString>iterator(this->component_controller->itemsFile);
    while(iterator.hasNext())
    {
        iterator.next();
        if(oldComponentName==iterator.key())
        {
            this->component_controller->itemsFile[componentName]=iterator.value();
            this->component_controller->itemsFile.remove(oldComponentName);
            break;
        }
    }
}
void MainWindow::editComponentStep(QString componentName,double componentStep)
{

     //qDebug()<<"change component name:"<<componentName<<" and change component step" <<componentStep;
     foreach(Component* com,this->tabWidget->getcom_arry())
    {
        if(com->getComponentFileName()==componentName)
         {
             com->setStep(componentStep);
//             qDebug()<<"change component name:"<<componentName<<" and change component step" <<componentStep;
         }
    }
}
TabWidget* MainWindow::getTabwidget()
{
    return tabWidget;
}
MainWindow::~MainWindow()
{
    //delete editcommenu;
}
