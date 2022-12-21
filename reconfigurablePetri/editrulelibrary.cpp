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
    if(conditionType=="time")
    {
        ui->timeComboBox->show();
        ui->timeValueLineEdit->show();
        ui->timeUnitComboBox->show();
        ui->conditionUnitLabel->setText(tr("token(s)"));
    }
    else {
        ui->timeComboBox->hide();
        ui->timeValueLineEdit->hide();
        ui->timeUnitComboBox->hide();
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
        ui->Target2ComboBox->show();
    }
    else {
        ui->target1Label->setText(tr("target"));
        ui->target2Label->hide();
        ui->Target2ComboBox->hide();
    }
}

void editRuleLibrary::on_ConditionOperatorComboBox_currentIndexChanged(const QString &conditionOperator)
{
    if(conditionOperator=="between")
    {
        ui->conditionValue2LineEdit->show();
        ui->conditionAndLabel->show();
    }
    else {
        ui->conditionValue2LineEdit->hide();
        ui->conditionAndLabel->hide();
    }
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
