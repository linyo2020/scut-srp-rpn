#ifndef NEWEDITCOM_H
#define NEWEDITCOM_H

#include <QDialog>
#include<QLineEdit>
#include"QDebug"
#include"QPushButton"
class neweditcom : public QDialog
{
    Q_OBJECT
public:
    explicit neweditcom(QWidget *parent = nullptr);
    ~neweditcom();
    QString type;
    QString name;
    QPushButton*mybutton;
    QLineEdit*line_type;

    void typeedit();
signals:
    void typechange(QString tex);
    void editFinished();
};

#endif // NEWEDITCOM_H
