#ifndef EDITRULELIBRARY_H
#define EDITRULELIBRARY_H

#include <QDialog>
#include"rulemanager.h"
#include <QGroupBox>
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

    void on_buttonBox_accepted();

    void on_RuleNamelineEdit_textChanged(const QString &arg1);

private:
    Ui::editRuleLibrary *ui;
    RuleManager tempManager;
    int previousRow;
    static ComparisonSymbol tonum(const QString&);
    static QString tostring(ComparisonSymbol);
    CONDITION getcondition();
    void setcondition(BaseRule*);
    QList<BaseOperation*> getoperation();
    void setoperation(BaseRule*);
    void saverule(int);
    void setconnection(bool,const QString&,const QString&);
};

#endif // EDITRULELIBRARY_H
