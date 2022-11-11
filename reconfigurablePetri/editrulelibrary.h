#ifndef EDITRULELIBRARY_H
#define EDITRULELIBRARY_H

#include <QDialog>

namespace Ui {
class editRuleLibrary;
}

class editRuleLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit editRuleLibrary(QWidget *parent = nullptr);
    ~editRuleLibrary();

private slots:
    void on_comboBox_activated(const QString &arg1);

private:
    Ui::editRuleLibrary *ui;
};

#endif // EDITRULELIBRARY_H
