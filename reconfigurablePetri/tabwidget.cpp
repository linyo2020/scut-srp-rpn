#include "tabwidget.h"
#include <QDebug>

TabWidget::TabWidget()
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

}
void TabWidget::saveAs()
{

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