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
    connect(&messageHandler, &MessageHandler::messageDelivred,this, &DockWidget::displayMessage);
}
void DockWidget::clearMessage()
{
    textDisplay->clear();
}
void DockWidget::displayMessage()
{
    QVariant v;
    v.setValue(messageHandler.uri());
    QString uri = v.toString();
    v.setValue(messageHandler.line());
    QString line = v.toString();
    v.setValue(messageHandler.column());
    QString column = v.toString() ;
    QString statusMessage = messageHandler.statusMessage();

    QString message(">> <span style=\"color:red;\">Error</span> in :\
                    <span style=\"color:blue;\">"+uri+"</span>, \
                    at line <span style=\"color:green;\">"+line+"</span>, \
                    column <span style=\"color:green;\">"+column+"</span> : ");

    textDisplay->insertHtml(message);
    textDisplay->insertHtml(statusMessage);
    textDisplay->insertHtml("<br>");
}

void DockWidget::showMessage (const QString &msg)
{
    textDisplay->insertHtml(msg);
    textDisplay->insertHtml("<br>");
}

MessageHandler& DockWidget::getMessageHandler ()
{
    return messageHandler;
}

DockWidget::~DockWidget()
{
  delete textDisplay;
}
