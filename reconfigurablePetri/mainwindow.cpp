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

      //初始化
      createToolBar ();
      createMenuBar();
      createDocks ();
      createStatusBar ();
      createComponentDock();
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
         connect(openComponentAction,&QAction::triggered,this,[=](){this->openComponent();});
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
    componentTree=new QTreeWidget();
    newComponent->setText(tr("新建"));
    connect(newComponent,&QToolButton::clicked,tabWidget,&TabWidget::saveComponent);
    newComponent->setToolTip(tr("Add a component <span style=\"color:gray;\">Ctrl+O</span>"));
    deleteComponent->setText(tr("删除"));
    deleteComponent->setToolTip(tr("Delete a component <span style=\"color:gray;\">Ctrl+O</span>"));
    addComponent->setText(tr("添加"));
    addComponent->setToolTip(tr("Open and add a component <span style=\"color:gray;\">Ctrl+O</span>"));
    connect(addComponent,&QToolButton::clicked,this,[=](){this->openComponent();});
    componentBar=new QToolBar();

    componentBar->addWidget(newComponent);
    componentBar->addWidget(deleteComponent);
    componentBar->addWidget(addComponent);
    componentBar->setAllowedAreas(Qt::TopToolBarArea);
    addToolBar(componentBar);
    componentController *component_controller=new componentController();
    component_controller->componentTreeInitial(componentTree);
    component_controller->addComponentTreeNode(componentTree,"A","cell1");
    component_controller->addComponentTreeNode(componentTree,"B","cell1");
    componentTree->expandAll();
    QVBoxLayout* VerticalLayout=new QVBoxLayout(componentDock);
    VerticalLayout->addWidget(componentBar);
    VerticalLayout->addWidget(componentTree);
    QWidget *mywid1 = new QWidget();
    mywid1->setLayout(VerticalLayout);
    componentDock->setWidget(mywid1);
    componentDock->show ();



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

            //清空原有数据和加载新数据
            e_mInputVaraible2Value[tab->getId()].clear();
            e_vFunDef[tab->getId()].clear();
            PTNET_ATTR net=tab->toXml();
            QList<ARC_ATTR>arcs=net.pages[0].arcs;
            QList<TRANSITION_ATTR>transitionNodes=net.pages[0].transitionNodes;
            QList<PLACE_ATTR>placeNodes=net.pages[0].placeNodes;
            //for(int i=0;i<arcs.size();i++)
            //{
            //    qDebug()<<"ARC "<<arcs[i].id<<" FROM "<<arcs[i].source<<" TO "<<arcs[i].target<<endl;
            //}

            //用l_mtemp记录弧和指向它的库所
            map<QString,QString>l_mtemp;
            for(int i=0;i<arcs.size();i++)
            {
                //qDebug()<<arcs.size();
                QString l_stemp;
                l_stemp.clear();
                for(int j=0;j<placeNodes.size();j++)
                {
                    if(placeNodes[j].id==arcs[i].source)
                    {
                        l_stemp.append(placeNodes[j].name);
                        //qDebug()<<placeNodes[j].name;
                        break;
                    }
                }
                l_mtemp[arcs[i].id]=l_stemp;
            }
            QVector<QString> samename;
            int recordpos;
            //对于每个PLACE
            for(int i=0;i<placeNodes.size();i++)
            {
                int havesame=0;
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
                    //fisRecord fisR;
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

                                l_FunDef.m_sFunctionExp.append("-1*(");
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
                                            //temp.append("*");
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
                                break;
                            }
                        }
                    }
                    else if(arcs[j].target==placeNodes[i].id)//PLACE为该ARC终点
                    {
                        //qDebug()<<placeNodes[i].name<<"is the target of"<<arcs[j].id;
                        for(int k=0;k<transitionNodes.size();k++)
                        {
                            if(transitionNodes[k].id==arcs[j].source)//找到该ARC的起点TRANSITION
                            {
                                {
                                    if(l_FunDef.m_sFunctionExp=="")
                                        l_FunDef.m_sFunctionExp.append("1*(");
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
                                                    //temp.append("*");
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
                                            //temp.append("*");
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
    delete componentDock;

    delete newComponent;
    delete addComponent;
    delete deleteComponent;
    delete componentBar;
}
