#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QAbstractMessageHandler>

class MessageHandler : public QAbstractMessageHandler
{
     Q_OBJECT
public:
    explicit MessageHandler(QObject * parent = 0);

    QUrl uri() const;
    QString statusMessage() const;
    int line() const;
    int column() const;

signals:

    void messageDelivred();

protected:

        void handleMessage(QtMsgType type, const QString &description,
             const QUrl &identifier, const QSourceLocation &sourceLocation);

private:

        QtMsgType msgType;
        QString msgDescription;
        QSourceLocation msgSourceLocation;
};

#endif // MESSAGEHANDLER_H
