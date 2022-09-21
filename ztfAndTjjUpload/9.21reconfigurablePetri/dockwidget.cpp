#include "dockwidget.h"

DockWidget::DockWidget(QWidget * parent)
    :QDockWidget(parent)
{
    //只读文本
    textDisplay  = new QTextEdit;
    textDisplay->setReadOnly(true);
    //字体设置
    QFont font;
    font.setFamily("Arial");
    this->setFont(font);

    //拖拉窗口设置
    setWidget(textDisplay);
    setAllowedAreas(Qt::BottomDockWidgetArea);
    setWindowTitle("output");
}

DockWidget::~DockWidget()
{
  delete textDisplay;
}
