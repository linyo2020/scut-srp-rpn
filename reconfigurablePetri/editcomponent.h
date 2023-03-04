#ifndef EDITCOMPONENT_H
#define EDITCOMPONENT_H

#include <QDialog>
#include <QString>
#include <QDebug>
namespace Ui {
class editComponent;
}

class editComponent : public QDialog
{
    Q_OBJECT

public:
    explicit editComponent(QWidget *parent = nullptr);
    ~editComponent();

    Ui::editComponent *ui;
signals:
    void editComponentInfo(QString componentName,double componentStep);

private slots:
    void on_buttonBox_accepted();
};

#endif // EDITCOMPONENT_H
