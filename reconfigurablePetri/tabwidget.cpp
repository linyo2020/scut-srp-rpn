#include "tabwidget.h"
#include <QDebug>
#include <QMessageBox>
#include"editcomponent.h"
#include"QCoreApplication"
#include<QVector>
TabWidget::TabWidget(QWidget * parent)
    :QTabWidget (parent)
{
    nets_indexes = 0;
    setMovable (true);
    setTabsClosable(false);
    Component*com=new Component();
    component_List.push_back(com);
    //点击了标签上的关闭按钮 ,移除tab页
    connect (this, &TabWidget::tabCloseRequested,this, &TabWidget::closeTab);

    createNew();
}

void TabWidget::save()
{
    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(currentWidget());
    QString filename = tab->getFilename();

    if(filename.isNull())
        saveAs();
    else
    {
      QFile file(filename);

      if(!file.open(QIODevice::WriteOnly))
          QMessageBox::critical(this, "Open File Error", \
        "The file could not be opened.");

      XmlWriter writer(tab->toXml());
      writer.writeXML(&file);
      tab->cleanUndostack();
      //tab->arcnoclicked=true;
    }
}
void TabWidget::saveAs()
{
    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(currentWidget());
    int index = currentIndex();

    QString filename = QFileDialog::getSaveFileName(this,
                          tr("Save As PNML Document"),
                                QDir::currentPath(),
                          tr("Petri Net Files (*.pnml)"));

    if(filename.isNull())
        return;

    if(QFileInfo(filename).suffix().isEmpty())
        filename.append(".pnml");

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    {
       QMessageBox::critical(this, "Save As Error", "The Petri Net" \
                          "could not be saved to: "+filename);

       return;
    }
    QFileInfo fileInfo(filename);
    QString nameStr = fileInfo.fileName();
    nameStr = nameStr.remove(nameStr.size()-5,5);
    tab->setName(nameStr);
    XmlWriter writer(tab->toXml());
    writer.writeXML(&file);

    tab->setFilename(filename);
    tab->cleanUndostack();
    setTabToolTip(index, filename);
    setTabText(index, fileInfo.fileName ());

    if(!fileNames.contains(filename))
         fileNames << filename;
}
void TabWidget::exportNet()
{

}
void TabWidget::print()
{

}

void TabWidget::saveLocalComponent()
{
    tab_copy = qobject_cast<PetriTabWidget*>(currentWidget());
    QString filename = tab_copy->getFilename();


    if(filename.isNull())
    {
        saveAsComponent();
        qDebug()<<"saveComponentFinished emit";
        emit saveComponentFinished();
    }

    //调整了信号触发时机，只有当用户第一次创建这个组件时才会触发信号，使得画板上所有元素的ID被设置
    //当该文件是已被编辑过的则不会调用setElementId这个函数
    else
    {
        qDebug()<<"fail";
        QFile file(filename);

        if(!file.open(QIODevice::WriteOnly))
            QMessageBox::critical(this, "Open Component Error", \
                                  "The Component could not be opened.");

        XmlWriter writer(tab_copy->componentToXml());
        writer.writeXML(&file);
        tab_copy->cleanUndostack();
    }

    emit startSimulation();

}
void TabWidget::openLocalComponent()
{
    setCurrentWidget(tab_copy);
    emit finishSimulation();
}
//use
void TabWidget::saveComponent()
{
    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(currentWidget());
    QString filename = tab->getFilename();


    if(filename.isNull())
    {
        saveAsComponent();
        qDebug()<<"saveComponentFinished emit";
        emit saveComponentFinished();
    }

    //调整了信号触发时机，只有当用户第一次创建这个组件时才会触发信号，使得画板上所有元素的ID被设置
    //当该文件是已被编辑过的则不会调用setElementId这个函数
    else
    {
        qDebug()<<"fail";
      QFile file(filename);

      if(!file.open(QIODevice::WriteOnly))
          QMessageBox::critical(this, "Open Component Error", \
        "The Component could not be opened.");

      XmlWriter writer(tab->componentToXml());
      writer.writeXML(&file);
      tab->cleanUndostack();
    }


}


void TabWidget::saveAsComponent()
{
    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(currentWidget());
    int index = currentIndex();

    QString filename = QFileDialog::getSaveFileName(this,
                          tr("Save As Component.PNML Document"),
                                QDir::currentPath(),
                          tr("Petri Net Files (*.pnml)"));

    if(filename.isNull())
        return;

    if(QFileInfo(filename).suffix().isEmpty())
        filename.append(".pnml");

    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly))
    {
       QMessageBox::critical(this, "Save As Error", "The Petri Net" \
                          "could not be saved to: "+filename);

       return;
    }
    QFileInfo fileInfo(filename);
    QString nameStr = fileInfo.fileName();
    nameStr = nameStr.remove(nameStr.size()-5,5);
    tab->setName(nameStr);
    //!important
    tab->setId(nameStr);
    XmlWriter writer(tab->componentToXml());
    writer.writeXML(&file);

    tab->setFilename(filename);
    tab->cleanUndostack();
    setTabToolTip(index, filename);
    setTabText(index, fileInfo.fileName ());

    if(!fileNames.contains(filename))
         fileNames << filename;
}

QVector<Component*> TabWidget::getcom_arry()
{
    return com_arry;
}

 QStringList TabWidget::getFileNames ()
 {
     return fileNames;
 }

//bug,需要更改
//废弃函数
 void TabWidget::setComponentType(QString type)
 {
     this->component_List[0]->setComponent_type(type);
     qDebug()<<"component_List[0]_type"<<component_List[0]->getComponent_type();
 }

 //将网中所有元素的id增加组件前缀
 void TabWidget::setElementId()
 {

     //元素id格式：文件名&num&p\t\a
     // tab id 格式：文件名&num

     //已经将这个函数的响应时机放到了用户输入完文件名之后
     PetriTabWidget*tab=qobject_cast<PetriTabWidget*>(currentWidget ());
     //test
     qDebug()<<"filename:"<<tab->getName();

     QString name=tab->getName();
     tab->setId(name+"&"+"1");
     PTNscene*s=tab->getSCene();

     //qDebug()<<"set"<<component_List[0]->getComponent_type()+"&"+"1";
     qDebug()<<"tabId in set"<<tab->getId();


     //这里强写成一了
     //qDebug()<<"tab componentTypeNum"<<componentTypeNum;

     //偷懒了没改变变量名
     componentTypeNum=1;
     foreach(QGraphicsItem * item , s->items())
     {
         if(item->type() == Place::Type)
         {
             Place * place = qgraphicsitem_cast<Place*>(item);
             QString num=QString::number(componentTypeNum,10);
             place->setPlaceID(name+"&"+num+"&"+place->getId());
             qDebug()<<place->getId();
         }
         else if(item->type()==Transition::Type)
         {
             QString num=QString::number(componentTypeNum,10);
             Transition*trans=qgraphicsitem_cast<Transition*>(item);
             trans->setID(name+"&"+num+"&"+trans->getId());
         }
         else if(item->type()==Arc::Type)
         {
             QString num=QString::number(componentTypeNum,10);
             Arc*arc=qgraphicsitem_cast<Arc*>(item);
             arc->setsourceId(name+"&"+num+"&"+arc->getSourceId());
             arc->setTargetId(name+"&"+num+"&"+arc->getTargetId());
             arc->setID(name+"&"+num+"&"+arc->getId());
         }
     }
     qDebug()<<"000ElementIdEditFinished";
     //需要将画板上被新分配的id重新写入文件中
     saveComponent();
 }

 //废弃函数
// void TabWidget::setImportComponentID()
// {
//     //遍历全部元素，id设置方式id=type+&+C+type_count[type]+X
//     PetriTabWidget*tab=qobject_cast<PetriTabWidget*>(currentWidget ());
//     PTNscene*s=tab->getSCene();
//     //原始id的格式  type&C?&p0/t0
//     QMap<QGraphicsItem*,bool>isEdit;
//     int t=1;
//     foreach(QGraphicsItem * item , s->items())
//     {
//         //如果当前元素被编辑过，则不处理
//         if(isEdit.contains(item))
//         {

//             qDebug()<<t++;
//             continue;
//         }
//         //如果未编辑
//         else
//         {
//             if(item->type() == Place::Type)
//             {
//                 Place * place = qgraphicsitem_cast<Place*>(item);
//                 QString ori_id=place->getId();
//                 QStringList list=ori_id.split("&");
//                 //Q_ASSERT_X(list[0]!=NULL,"ERROR","list[0] represents component_type,this variable shouldnot become null.please check mainwindow line:333-336");
//                 //如果此时页面上已经添加过该类的
//                 if(type_count.contains(list[0]))
//                 {
//                     int nums=type_count.value(list[0])+1;
//                     QString num=QString::number(nums);
//                     place->setPlaceID(list[0]+"&"+num+"&"+list[2]);
//                     type_count.insert(list[0],nums);
//                 }
//                 //页面上尚未出现过该组件类型
//                 else
//                 {
//                     int nums=1;
//                     QString num=QString::number(nums);
//                     place->setPlaceID(list[0]+"&"+num+"&"+list[2]);
//                     type_count.insert(list[0],nums);
//                 }
//             }
//             else if(item->type()==Transition::Type)
//             {
//                 Transition * trans = qgraphicsitem_cast<Transition*>(item);
//                 QString ori_id=trans->getId();
//                 QStringList list=ori_id.split("&");
//                 //Q_ASSERT_X(list[0]!=NULL,"ERROR","list[0] represents component_type,this variable shouldnot become null.please check mainwindow line:333-336");
//                 //如果此时页面上已经添加过该类的
//                 if(type_count.contains(list[0]))
//                 {
//                     int nums=type_count.value(list[0])+1;
//                     QString num=QString::number(nums);
//                     trans->setID(list[0]+"&"+num+"&"+list[2]);
//                     type_count.insert(list[0],nums);
//                 }
//                 //页面上尚未出现过该组件类型
//                 else
//                 {
//                     int nums=1;
//                     QString num=QString::number(nums);
//                     trans->setID(list[0]+"&"+num+"&"+list[2]);
//                     type_count.insert(list[0],nums);
//                 }
//             }
//             else if(item->type()==Arc::Type)
//             {
//                 QString num=QString::number(componentTypeNum,10);



//                 Arc*arc=qgraphicsitem_cast<Arc*>(item);
//                 QString ori_id=arc->getId();
//                 QStringList list=ori_id.split("&");
//                 //Q_ASSERT_X(list[0]!=NULL,"ERROR","list[0] represents component_type,this variable shouldnot become null.please check mainwindow line:333-336");
//                 //如果此时页面上已经添加过该类的
//                 if(type_count.contains(list[0]))
//                 {
//                     int nums=type_count.value(list[0])+1;
//                     QString num=QString::number(nums);

//                     QString source=arc->getSourceId();
//                     QStringList souceList=source.split("&");

//                     QString target=arc->getTargetId();
//                     QStringList targetList=source.split("&");

//                     arc->setsourceId(list[0]+"&"+num+"&"+source[2]);
//                     arc->setTargetId(list[0]+"&"+num+"&"+targetList[2]);
//                     arc->setID(list[0]+"&"+num+"&"+list[2]);

//                     type_count.insert(list[0],nums);
//                 }
//                 //页面上尚未出现过该组件类型
//                 else
//                 {
//                     int nums=1;
//                     QString num=QString::number(nums);
//                     QString source=arc->getSourceId();
//                     QStringList souceList=source.split("&");

//                     QString target=arc->getTargetId();
//                     QStringList targetList=source.split("&");

//                     arc->setsourceId(list[0]+"&"+num+"&"+source[2]);
//                     arc->setTargetId(list[0]+"&"+num+"&"+targetList[2]);
//                     arc->setID(list[0]+"&"+num+"&"+list[2]);

//                     type_count.insert(list[0],nums);
//                 }



//             }
//             isEdit.insert(item,true);
//         }

//     }

// }






 void TabWidget::setImportComponentId_AND_classsifyComponenet()
 {
     //每导入一次就扫描页面上的所有元素，对该元素进行判断，判断是否读取过了，并将满足条件的元素塞入组件列表中
     //每进行导入操作时，这个函数就被调用一次，com_arry.size()就+1
     //QVector<Componenent*>com_arry;//管理页面上的所有组件,注意必须保持唯一性
     //QMap<QString ,int>type_count;//计数器//必须保证唯一

     //元素id格式：文件名&num&p\t\a
     // tab id 格式：文件名&num
     //拿到所有元素
     PetriTabWidget*tab=qobject_cast<PetriTabWidget*>(currentWidget ());
     //扫描页面上所有元素
     PTNscene*s=tab->getSCene();
     Component*com=new Component();
     QStringList tabIDList=tab->getId().split("&");

     qDebug()<<"list[0] is type :"<<tabIDList[0];
     //QString comType=tabIDList[0];

     QString comName=tabIDList[0];

     qDebug()<<"tabName: "<<comName;

     qDebug()<<"1: "<<tab->getId()<<": "<<tab->getId();

     //QString type=getComponenttype(tab->getId());
     //这里偷懒了，应该把type变量名换为name的
     QString type=comName;
     qDebug()<<"2:"<<tab->getId()<<": "<<type;

     //这个名称的组件之前已经添加过了
     if(type_count.contains(comName))
     {
         qDebug()<<"3:"<<tab->getId()<<": "<<type_count[comName];
         type_count[comName]+=1;

     }
     else
     {
         type_count.insert(comName,1);
         qDebug()<<"4"<<tab->getId()<<": "<<type_count[comName];
     }
     QString s1=QString::number(type_count[comName]);
     qDebug()<<"s1:"<<tab->getId()<<": "<<s1;
     tab->setId(type+"&"+s1);
     qDebug()<<"5:"<<tab->getId()<<": "<<tab->getId();
     //对于所有原始组件中的元素而言，原始id的格式 一定是 type&C1&p0/t0
     int count=0;
     foreach(QGraphicsItem * item , s->items())
     {
         count+=1;
         qDebug()<<"5.5 count:"<<tab->getId()<<": "<<count;
         if(item->type() == Place::Type)
         {
             Place * place = qgraphicsitem_cast<Place*>(item);
             QStringList list=place->getId().split("&");
             qDebug()<<"6: "<<tab->getId()<<": "<<place->getId();
             qDebug()<<"7:"<<tab->getId()<<": "<<place->isInComponent();
             //这个元素已经被包含在组件内了
             if(place->isInComponent())
             {
                 qDebug()<<"10:"<<tab->getId()<<": "<<place->getId();
                 continue;
             }
             else
             {

                 //设置id
                 QString newId=type+"&"+s1+"&"+list[2];
                 qDebug()<<"8:"<<tab->getId()<<": "<<newId;
                 place->setPlaceID(newId);
                 place->setIncomponent(true);
                 com->mynet->AddPlace(place);


             }
         }
         else if(item->type() == Transition::Type)
         {
             Transition * trans = qgraphicsitem_cast<Transition*>(item);
             QStringList list=trans->getId().split("&");
             qDebug()<<"11"<<trans->getId();
             qDebug()<<"14"<<tab->getId()<<": "<<trans->isInComponent();
             //这个元素已经被包含在组件内了
             if(trans->isInComponent())
             {
                 qDebug()<<"12"<<tab->getId()<<": "<<trans->getId();
                 continue;
             }
             else
             {

                 //设置id
                 QString newId=type+"&"+s1+"&"+list[2];
                 qDebug()<<"9:"<<tab->getId()<<": "<<newId;
                 trans->setID(newId);
                 trans->setIncomponent(true);
                 com->mynet->AddTransition(trans);


             }
         }
         else if(item->type() == Arc::Type)
         {
             Arc * arc = qgraphicsitem_cast<Arc*>(item);
             QStringList list=arc->getId().split("&");
             qDebug()<<"15: "<<tab->getId()<<": "<<arc->getId();
             qDebug()<<"16 "<<tab->getId()<<": "<<arc->isInComponent();
             //这个元素已经被包含在组件内了
             if(arc->isInComponent())
             {
                 qDebug()<<"17"<<tab->getId()<<": "<<arc->isInComponent();
                 continue;
             }
             else
             {

                 //设置id
                 QString newId=type+"&"+s1+"&"+list[2];
                 QString source=arc->getSourceId();
                 QStringList sl=source.split("&");

                 QString target=arc->getTargetId();
                 QStringList gl=target.split("&");

                 arc->setsourceId(type+"&"+s1+"&"+sl[2]);
                 arc->setTargetId(type+"&"+s1+"&"+gl[2]);
                 qDebug()<<"18:"<<tab->getId()<<": "<<newId;
                 arc->setID(newId);
                 arc->setIncomponent(true);
                 com->mynet->AddArc(arc);
             }
         }
     }

     com->setID(tab->getId());
     qDebug()<<"13"<<com->getID();
     com_arry.push_back(com);
 }

 QString TabWidget::getComponenttype(QString id)
 {
     QStringList list=id.split("&");
     return list[0];
 }
void TabWidget::undo()
{
    qobject_cast<PetriTabWidget*>(currentWidget ())->undo ();
}
void TabWidget::redo()
{
    qobject_cast<PetriTabWidget*>(currentWidget ())->redo ();
}
void TabWidget::removeItems()
{
    qobject_cast<PetriTabWidget*>(currentWidget ())->removeItems ();
}


void TabWidget::createNew()
{
    //新建子窗口
    QVariant v_num(nets_indexes);
    PetriTabWidget * tab = new PetriTabWidget("PN "+v_num.toString(), 0);
    addTab(tab, QString("PN "+v_num.toString()));
    connectSignalAndSlot(tab);
    nets_indexes ++;
}
void TabWidget::updateTitle (bool changed)
{
    int index = currentIndex();
    QString text = tabText(index);
    //更改窗口标题
    if (!changed && (!text.endsWith("*")))
            setTabText(index, QString(text+"*"));
    else
    {
        text.remove(text.size()-1, 1);
        setTabText(index, text);
    }
}
/* 打开子网 */
bool TabWidget::open (MessageHandler &messageHandler)
{
    //![0] get file name
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open PNML Document"), QDir::currentPath(),
              tr("Petri Net Files (*.pnml)"));

    if(filename.isNull())
        return false;

    //![1] check if the file is already opened
    if(fileNames.contains(filename))
    {
        for(int i=0; i<count(); i++)
        {
            PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(widget(i));
            if(tab->getFilename() == filename)
            {
                setCurrentWidget(tab);
                return true;
            }
        }
    }else
    {
        fileNames << filename;
    }

    QFile file(filename);
    QFileInfo fi(file);
    //qDebug()<<fi.fileName();

    //![2] validate xml file
    if(!validateXml(file, messageHandler))
    {
        QMessageBox::critical(0,"Warning!",QString("Validate failed!"),
                              QMessageBox::Ok,0,0);
        return false;
    }

    //![3] parse xml file
    file.seek(0);
    QTextStream textstream(&file);
    QString xmlContent = textstream.readAll();
    file.close();

    XmlParser parser;
    if(!parser.parseXML(xmlContent))
        return false;

    //![4] ok :)
    PTNET_ATTR net = parser.getXML_net ();
    PetriTabWidget * tab = new PetriTabWidget(net, filename);
    addTab(tab,fi.fileName());
    connectSignalAndSlot(tab);
    setTabToolTip(currentIndex(), filename);

    return true;
}
//打开组件
bool TabWidget::openComponent(MessageHandler &messageHandler)
{
    //![0] get Component name
    QString componentName = QFileDialog::getOpenFileName(this,
        tr("Open PNML Document"), QDir::currentPath(),
              tr("Petri Net Files (*.pnml)"));

    if(componentName.isNull())
        return false;

    //![1]

    QFile file(componentName);
    QFileInfo fi(file);
    emit addComponentTreeNode(fi.baseName(),componentName);

    //![2] validate xml file
    if(!validateXml(file, messageHandler))
    {
        QMessageBox::critical(0,"Warning!",QString("Validate failed!"),
                              QMessageBox::Ok,0,0);
        return false;
    }

    //![3] parse xml file
    file.seek(0);
    QTextStream textstream(&file);
    QString xmlContent = textstream.readAll();
    file.close();

    XmlParser parser;
    if(!parser.parseXML(xmlContent))
        return false;

    //![4] ok :)
    PTNET_ATTR net = parser.getXML_net ();
    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(currentWidget());
    tab->setComponent(net, componentName);

    return true;
}
//添加已有组件
void TabWidget::addComponent(QString componentPath)
{
    QFile file(componentPath);
    QFileInfo fi(file);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //![3] parse xml file
    file.seek(0);
    QTextStream textstream(&file);
    QString xmlContent = textstream.readAll();
    file.close();

    XmlParser parser;
    parser.parseXML(xmlContent);

    PTNET_ATTR net = parser.getXML_net ();
    PetriTabWidget * tab = qobject_cast<PetriTabWidget*>(currentWidget());
    tab->setComponent(net, componentPath);
    emit addComponentFinished();
}


bool TabWidget::validateXml(QFile& file, MessageHandler &messageHandler)
{
    //![0] validate XML schema
    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);

    //TODO:update xsd
    schema.load(QUrl::fromLocalFile(":/schemas/ptnet.xsd"));

    if(!schema.isValid())
    {
        QMessageBox::critical(0,"Warning!",QString("Xsd invalid!"),
                              QMessageBox::Ok,0,0);
        return false;
    }

    //![1] open file
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Loading File Error", file.errorString ());
        return false;
    }

    //![2] validate file against XML schema
    QXmlSchemaValidator validator(schema);
    validator.setMessageHandler(&messageHandler);

    if(!validator.validate(&file, QUrl::fromLocalFile(file.fileName())))
    {
        file.close();
        return false;
    }

  return true;
}

void TabWidget::closeTab(int index)
{
    auto * tab = qobject_cast<PetriTabWidget *>(widget(index));
    setCurrentWidget(tab);

    if(!tab->isSaved())
    {
        QMessageBox::StandardButton action;

        action = QMessageBox::warning(this,
                       "Save", "Save or not?",
                        QMessageBox::Save | QMessageBox::No |
                        QMessageBox::Cancel, QMessageBox::Save);

      if(action == QMessageBox::Save)
         save();
      else if(action == QMessageBox::Cancel)
          return;
    }

      removeTab(index);

      if (count() <= 1)
        setTabsClosable(false);
      else
        setTabsClosable(true);

}

void TabWidget::connectSignalAndSlot(PetriTabWidget * tab)
{
    connect (tab, &PetriTabWidget::canRedoChange,this, &TabWidget::canRedoChange);
    connect (tab, &PetriTabWidget::canUndoChange,this, &TabWidget::canUndoChange);
    connect (tab, &PetriTabWidget::netChanged,this, &TabWidget::updateTitle);
    connect (tab, &PetriTabWidget::errorMessage,this, &TabWidget::errorMessage);

    if(count() > 1)
        setTabsClosable(true);

    setCurrentWidget(tab);
}



/*
 * 缩放
 *  */
void TabWidget::zoom (int val)
{
    qobject_cast<PetriTabWidget*>(currentWidget ())->scaleView (val);
}
