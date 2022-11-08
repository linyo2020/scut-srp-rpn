#include "messagehandler.h"
#include <QDebug>

MessageHandler::MessageHandler(QObject * parent)
    :QAbstractMessageHandler(parent)
{

}

QString MessageHandler::statusMessage() const
{
  return msgDescription;
}

int MessageHandler::line() const
{
  return msgSourceLocation.line();
}

int MessageHandler::column() const
{
  return msgSourceLocation.column();
}

QUrl MessageHandler::uri() const
{
  return msgSourceLocation.uri();
}

void MessageHandler::handleMessage(QtMsgType type, const QString &description,
    const QUrl &identifier, const QSourceLocation &sourceLocation)
{
  Q_UNUSED(type);
  Q_UNUSED(identifier);

  msgType = type;
  msgDescription = description;
  msgSourceLocation = sourceLocation;

  emit messageDelivred();
}


