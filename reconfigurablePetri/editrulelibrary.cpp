#include "editrulelibrary.h"
#include "ui_editrulelibrary.h"
#include <QGroupBox>
#include<QScrollBar>

editRuleLibrary::editRuleLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editRuleLibrary)
{
    ui->setupUi(this);
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
        ui->timeValueLineEdit->show();
        ui->TimeOperatorComboBox->show();
        ui->conditionUnitLabel->setText(tr("token(s)"));
    }
    else {
        ui->timeValueLineEdit->hide();
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
        ui->conditionValue1LineEdit->hide();
        ui->ConditionOperatorComboBox->hide();
        ui->conditionUnitLabel->hide();
    }
    else {
        ui->monitiorObjectLabel->show();
        ui->monitorObjectLineEdit->show();
        ui->conditionLabel->show();
        ui->conditionValue1LineEdit->show();
        ui->ConditionOperatorComboBox->show();
        ui->conditionUnitLabel->show();
    }
}

void editRuleLibrary::on_addRulesPushButton_clicked()
{
    ui->listWidget->addItem(QString("rule")+QVariant(ui->listWidget->count()).toString());
}

void editRuleLibrary::on_deleteRulePushButton_clicked()
{
    ui->listWidget->takeItem(ui->listWidget->currentRow());
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
    }
}

void editRuleLibrary::on_listWidget_currentRowChanged(int currentRow)
{

}
