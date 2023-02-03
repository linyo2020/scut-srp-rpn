#include "editrulelibrary.h"
#include "ui_editrulelibrary.h"
#include <QGroupBox>
#include<QScrollBar>
#include"mainwindow.h"
#include"petritabwidget.h"
#include"defs.h"
#include"rule/timerule.h"
#include"rule/eventrule.h"
#include"rule/staterule.h"
editRuleLibrary::editRuleLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRuleLibrary)
{
    ui->setupUi(this);
    previousRow=-1;
    if(parent!=NULL)
    {
        tempManager=dynamic_cast<PetriTabWidget*>(dynamic_cast<MainWindow*>(parent)->getTabwidget()->currentWidget())->getRuleManager();
        ui->rulesSettingsScrollArea->hide();
        for(BaseRule* rule:*tempManager.getRuleList())
            ui->listWidget->addItem(rule->getName());
    }
}

editRuleLibrary::~editRuleLibrary()
{
    delete ui;
}

void editRuleLibrary::on_conditionTypeComboBox_currentIndexChanged(const QString &conditionType)
{
    ui->subtypeComboBox->setCurrentIndex(0);
    if(conditionType=="time")
    {
        ui->subtypeLabel->show();
        ui->subtypeComboBox->show();
        ui->timeValueSpinBox->show();
        ui->TimeOperatorComboBox->show();
        ui->conditionUnitLabel->setText(tr("token(s)"));
    }
    else {
        ui->timeValueSpinBox->hide();
        ui->subtypeLabel->hide();
        ui->subtypeComboBox->hide();
        ui->TimeOperatorComboBox->hide();
        if(conditionType=="state")
            ui->conditionUnitLabel->setText(tr("token(s)"));
        else {
            ui->conditionUnitLabel->setText(tr("firing(s)"));
        }
    }
}

void editRuleLibrary::on_actionTypeComboBox_currentIndexChanged(const QString &actionType)
{
    if(actionType=="update")
    {
        ui->target1Label->setText(tr("From"));
        ui->target2Label->show();
        ui->target2LineEdit->show();
    }
    else {
        ui->target1Label->setText(tr("target"));
        ui->target2Label->hide();
        ui->target2LineEdit->hide();
    }
}

void editRuleLibrary::on_ConditionOperatorComboBox_currentIndexChanged(const QString &conditionOperator)
{

}

void editRuleLibrary::on_addConnectionPushButton_clicked()
{
    QGridLayout* connectionGridLayout=dynamic_cast<QGridLayout*>(ui->connectionGridFrame->layout());
    QGroupBox* ruleGroupBox=new QGroupBox;
    QGridLayout* groupBoxLayout=new QGridLayout;
    QComboBox* connectionType=new QComboBox;
    connectionType->addItem(tr("connect"));
    connectionType->addItem(tr("disconnect"));
    QComboBox* connectionSource=new QComboBox;
    QLabel* connectionAndLabel=new QLabel;
    connectionAndLabel->setText(tr("and"));
    QComboBox* connectionTarget=new QComboBox;
    QPushButton* deleteRulePushButton=new QPushButton;
    deleteRulePushButton->setText(tr("delete"));
    groupBoxLayout->addWidget(connectionType,0,0);
    groupBoxLayout->addWidget(connectionSource,0,1,1,3);
    groupBoxLayout->addWidget(connectionAndLabel,1,0);
    groupBoxLayout->addWidget(connectionTarget,1,1,1,3);
    groupBoxLayout->addWidget(deleteRulePushButton,2,3);
    ruleGroupBox->setLayout(groupBoxLayout);
    connectionGridLayout->addWidget(ruleGroupBox,connectionGridLayout->rowCount(),0,1,connectionGridLayout->columnCount());
    connect(deleteRulePushButton,&QPushButton::clicked,ruleGroupBox,&QGroupBox::deleteLater);
}

void editRuleLibrary::on_subtypeComboBox_currentIndexChanged(const QString &subtype)
{
    ui->subtypeLabel->setText(subtype);
    if(subtype=="Global time")
    {
        ui->monitiorObjectLabel->hide();
        ui->monitorObjectLineEdit->hide();
        ui->conditionLabel->hide();
        ui->conditionValueSpinBox->hide();
        ui->ConditionOperatorComboBox->hide();
        ui->conditionUnitLabel->hide();
    }
    else {
        ui->monitiorObjectLabel->show();
        ui->monitorObjectLineEdit->show();
        ui->conditionLabel->show();
        ui->conditionValueSpinBox->show();
        ui->ConditionOperatorComboBox->show();
        ui->conditionUnitLabel->show();
    }
}

void editRuleLibrary::on_addRulesPushButton_clicked()
{
    ui->listWidget->addItem(QString("rule")+QVariant(ui->listWidget->count()).toString());
    tempManager.appendRule(NULL);
}

void editRuleLibrary::on_deleteRulePushButton_clicked()
{
    int currentRow=ui->listWidget->currentRow();
    ui->listWidget->takeItem(currentRow);
    tempManager.deleteRule(currentRow);
}

void editRuleLibrary::on_moveUpPushButton_clicked()
{
    int currentRow=ui->listWidget->currentRow();
    if(currentRow>0)
    {
        QString str=ui->listWidget->item(currentRow)->text();
        ui->listWidget->takeItem(currentRow);
        ui->listWidget->insertItem(currentRow-1,str);
        ui->listWidget->setCurrentRow(currentRow-1);
        tempManager.moveRule(currentRow,currentRow-1);
    }
}

void editRuleLibrary::on_moveDownPushButton_clicked()
{
    int currentRow=ui->listWidget->currentRow();
    if(currentRow>=0&&currentRow<ui->listWidget->count()-1)
    {
        QString str=ui->listWidget->item(currentRow)->text();
        ui->listWidget->takeItem(currentRow);
        ui->listWidget->insertItem(currentRow+1,str);
        ui->listWidget->setCurrentRow(currentRow+1);
        tempManager.moveRule(currentRow,currentRow+1);
    }
}

void editRuleLibrary::on_listWidget_currentRowChanged(int currentRow)
{
    if(previousRow!=-1)
        saverule(previousRow);
    previousRow=currentRow;
    if(currentRow<0)
        return;
    ui->rulesSettingsScrollArea->show();
    BaseRule* currentrule=tempManager.getRuleList()->at(currentRow);
    if(currentrule==NULL)
    {
        ui->RuleNamelineEdit->setText(ui->listWidget->currentItem()->text());
        ui->commentTextEdit->clear();
        ui->ConditionOperatorComboBox->setCurrentIndex(0);
        ui->conditionValueSpinBox->setValue(0);
        ui->TimeOperatorComboBox->setCurrentIndex(0);
        ui->timeValueSpinBox->setValue(0);
        ui->conditionTypeComboBox->setCurrentIndex(0);
        ui->subtypeComboBox->setCurrentIndex(0);
        ui->monitorObjectLineEdit->clear();
    }
    else {
        setcondition(currentrule);
        setoperation(currentrule);
    }
}
ComparisonSymbol editRuleLibrary::tonum(const QString& symbol)
{
    if(symbol=="<")
        return LESS;
    else if(symbol=="=")
        return EQUAL;
    else if(symbol==">")
        return GREATER;
    else if(symbol=="≥")
        return GREATER_EQUAL;
    else if(symbol=="≤")
        return LESS_EQUAL;
    else
        return NOT_EQUAL;
}
CONDITION editRuleLibrary::getcondition()
{
    QString type=ui->conditionTypeComboBox->currentText();
    if(type=="time")
    {
        QString subtype=ui->subtypeComboBox->currentText();
        if(subtype=="Duration")
        {
            QString monitorObject=ui->monitorObjectLineEdit->text();
            ComparisonSymbol ConditionOperator=tonum(ui->ConditionOperatorComboBox->currentText());
            QVariant ConditionValue=ui->conditionValueSpinBox->value();
            ComparisonSymbol timeOperator=tonum(ui->TimeOperatorComboBox->currentText());
            QVariant timeValue=ui->timeValueSpinBox->value();
            return CONDITION(CERTAIN_TOKEN_DURATION,monitorObject,ConditionOperator,ConditionValue,
                                new CONDITION(CERTAIN_TOKEN_DURATION,QString(),timeOperator,timeValue));
        }
        else if(subtype=="Time to reach")
        {
            QString monitorObject=ui->monitorObjectLineEdit->text();
            ComparisonSymbol ConditionOperator=tonum(ui->ConditionOperatorComboBox->currentText());
            QVariant ConditionValue=ui->conditionValueSpinBox->value();
            ComparisonSymbol timeOperator=tonum(ui->TimeOperatorComboBox->currentText());
            QVariant timeValue=ui->timeValueSpinBox->value();
            return CONDITION(TIME_TO_REACH_CERTAIN_TOKEN,monitorObject,ConditionOperator,ConditionValue,
                                new CONDITION(TIME_TO_REACH_CERTAIN_TOKEN,QString(),timeOperator,timeValue));
        }
        else if(subtype=="Global time")
        {
            ComparisonSymbol timeOperator=tonum(ui->TimeOperatorComboBox->currentText());
            QVariant timeValue=ui->timeValueSpinBox->value();
            return CONDITION(TIME_POINT_COMPARE,QString(),timeOperator,timeValue);
        }
    }
    else if(ui->conditionTypeComboBox->currentText()=="event")
    {

    }
    else if(ui->conditionTypeComboBox->currentText()=="state")
    {
        QString monitorObject=ui->monitorObjectLineEdit->text();
        ComparisonSymbol ConditionOperator=tonum(ui->ConditionOperatorComboBox->currentText());
        QVariant ConditionValue=ui->conditionValueSpinBox->value();
        return CONDITION(TOKEN_COMPARE,monitorObject,ConditionOperator,ConditionValue);
    }
}
void editRuleLibrary::setcondition(BaseRule * currentrule)
{
    ui->RuleNamelineEdit->setText(currentrule->getName());
    ui->commentTextEdit->setText(currentrule->getComment());
    CONDITION condition=currentrule->getConditionList().front().front();
    if(condition.conditionOption==CERTAIN_TOKEN_DURATION)
    {
        ui->monitorObjectLineEdit->setText(condition.monitorFactor);
        ui->conditionTypeComboBox->setCurrentText("time");
        ui->subtypeComboBox->setCurrentText("Duration");
        ui->ConditionOperatorComboBox->setCurrentText(tostring(condition.symbol));
        ui->conditionValueSpinBox->setValue(condition.value.toInt());
        ui->TimeOperatorComboBox->setCurrentText(tostring(condition.rearPart->symbol));
        ui->timeValueSpinBox->setValue(condition.rearPart->value.toInt());
    }
    else if(condition.conditionOption==TIME_TO_REACH_CERTAIN_TOKEN)
    {
        ui->monitorObjectLineEdit->setText(condition.monitorFactor);
        ui->conditionTypeComboBox->setCurrentText("time");
        ui->subtypeComboBox->setCurrentText("Time to reach");
        ui->ConditionOperatorComboBox->setCurrentText(tostring(condition.symbol));
        ui->conditionValueSpinBox->setValue(condition.value.toInt());
        ui->TimeOperatorComboBox->setCurrentText(tostring(condition.rearPart->symbol));
        ui->timeValueSpinBox->setValue(condition.rearPart->value.toInt());
    }
    else if(condition.conditionOption==TIME_POINT_COMPARE)
    {
        ui->conditionTypeComboBox->setCurrentText("time");
        ui->subtypeComboBox->setCurrentText("Global time");
        ui->TimeOperatorComboBox->setCurrentText(tostring(condition.symbol));
        ui->timeValueSpinBox->setValue(condition.value.toInt());
    }
    else if(condition.conditionOption==TOKEN_COMPARE)
    {
        ui->monitorObjectLineEdit->setText(condition.monitorFactor);
        ui->conditionTypeComboBox->setCurrentText("state");
        ui->ConditionOperatorComboBox->setCurrentText(tostring(condition.symbol));
        ui->conditionValueSpinBox->setValue(condition.value.toInt());
    }
}
QString editRuleLibrary::tostring(ComparisonSymbol symbol)
{
    if(symbol==LESS)
        return "<";
    else if(symbol==EQUAL)
        return "=";
    else if(symbol==GREATER)
        return ">";
    else if(symbol==LESS_EQUAL)
        return "≤";
    else if(symbol==GREATER_EQUAL)
        return "≥";
    else return "≠";
}
QList<BaseOperation*> editRuleLibrary::getoperation()
{
    return {};
}
void editRuleLibrary::setoperation(BaseRule * currentrule)
{

}

void editRuleLibrary::on_buttonBox_accepted()
{
   saverule(ui->listWidget->currentRow());
   dynamic_cast<PetriTabWidget*>(dynamic_cast<MainWindow*>(this->parent())->getTabwidget()->currentWidget())->setRuleManager(tempManager);
}
void editRuleLibrary::saverule(int row)
{
    QString name=ui->RuleNamelineEdit->text();
    QString comment=ui->commentTextEdit->toPlainText();
    CONDITION condition=getcondition();
    QList<BaseOperation*> operation=getoperation();
    QString type=ui->conditionTypeComboBox->currentText();
    BaseRule* saverule;
    if(type=="time")
        saverule=new TimeRule(name,comment,{{condition}},operation);
    else if(type=="event")
        saverule=new EventRule(name,comment,{{condition}},operation);
    else if(type=="state")
        saverule=new StateRule(name,comment,{{condition}},operation);
    else saverule=NULL;
    if(saverule!=NULL)
       tempManager.replaceRule(row,saverule);
}

void editRuleLibrary::on_RuleNamelineEdit_textChanged(const QString &arg1)
{
    ui->listWidget->item(previousRow)->setText(arg1);
}
