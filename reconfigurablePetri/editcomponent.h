#ifndef EDITCOMPONENT_H
#define EDITCOMPONENT_H

#include <QDialog>

namespace Ui {
class editComponent;
}

class editComponent : public QDialog
{
    Q_OBJECT

public:
    explicit editComponent(QWidget *parent = nullptr);
    ~editComponent();

private:
    Ui::editComponent *ui;
};

#endif // EDITCOMPONENT_H
