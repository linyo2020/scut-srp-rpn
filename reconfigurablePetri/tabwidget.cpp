#include "tabwidget.h"
#include "xmlwriter.h"
#include <QDebug>

TabWidget::TabWidget(QWidget * parent)
    :QTabWidget (parent)
{
    nets_indexes = 0;
    setMovable (true);
    setTabsClosable(false);

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
    tab->setId(nameStr);
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
    //qDebug()<<filename;

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

    //[2]! validate xml file
    if(!validateXml(file, messageHandler))
    return false;

    //[3]! parse xml file
    file.seek(0);
    QTextStream textstream(&file);
    QString xmlContent = textstream.readAll();
    file.close();

    XmlParser parser;
    if(!parser.parseXML(xmlContent))
        return false;

    //[4]! ok :)
    PTNET_ATTR net = parser.getXML_net ();
    PetriTabWidget * tab = new PetriTabWidget(net, filename);
    addTab(tab,fi.fileName());
    connectSignalAndSlot(tab);
    setTabToolTip(currentIndex(), filename);

    return true;
}
bool TabWidget::validateXml(QFile& file, MessageHandler &messageHandler)
{
    //![0] validate XML schema
    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);
    schema.load(QUrl::fromLocalFile(":/schemas/ptnet.xsd"));

    if(!schema.isValid())
        return false;

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

//    if(!tab->isSaved())
//    {
//        QMessageBox::StandardButton action;

//        action = QMessageBox::warning(this,
//                       "Save", "Save or not?",
//                        QMessageBox::Save | QMessageBox::No |
//                        QMessageBox::Cancel, QMessageBox::Save);

//      if(action == QMessageBox::Save)
//         save();
//      else if(action == QMessageBox::Cancel)
//          return;
//    }
      // 移除tab页
      removeTab(index);

//      if (count() <= 1)
//        setTabsClosable(false);
//      else
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

}
