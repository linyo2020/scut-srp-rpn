#ifndef EDITRULELIBRARY_H
#define EDITRULELIBRARY_H

#include <QDialog>
#include"rulemanager.h"

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

    void on_subtypeComboBox_currentIndexChanged(const QString &arg1);

    void on_addRulesPushButton_clicked();

    void on_deleteRulePushButton_clicked();

    void on_moveUpPushButton_clicked();

    void on_moveDownPushButton_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::editRuleLibrary *ui;
    QList<BaseRule*>ruleList;
};

#endif // EDITRULELIBRARY_H
