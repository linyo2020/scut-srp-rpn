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

    void on_conditionTypeComboBox_currentIndexChanged(const QString &arg1);

    void on_actionTypeComboBox_currentIndexChanged(const QString &arg1);

    void on_ConditionOperatorComboBox_currentIndexChanged(const QString &arg1);

    void on_addConnectionPushButton_clicked();

private:
    Ui::editRuleLibrary *ui;
};

#endif // EDITRULELIBRARY_H
