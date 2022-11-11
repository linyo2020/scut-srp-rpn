/********************************************************************************
** Form generated from reading UI file 'editrulelibrary.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRULELIBRARY_H
#define UI_EDITRULELIBRARY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editRuleLibrary
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QFrame *gridFrame;
    QGridLayout *gridLayout_4;
    QPushButton *addRulesButton;
    QSpacerItem *horizontalSpacer_4;
    QScrollArea *rulesScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *treeWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QFrame *ruleSettingsFrame;
    QVBoxLayout *verticalLayout;
    QFrame *gridFrame1;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLabel *label;
    QFrame *triggerGridFrame;
    QGridLayout *gridLayout_2;
    QLabel *TriggerLabel;
    QLabel *conditionTypeLabel;
    QComboBox *conditionTypeComboBox;
    QLabel *monitiorObjectLabel;
    QComboBox *monitorObjectComboBox;
    QLabel *conditionLabel;
    QComboBox *ConditionOperatorComboBox;
    QLineEdit *conditionValueLineEdit;
    QLabel *conditionUnitLabel;
    QLabel *durationLabel;
    QLineEdit *durationValueLineEdit;
    QComboBox *durationUnitComboBox;
    QFrame *actionGridFrame;
    QGridLayout *actionGridLayout;
    QLabel *actionTypeLabel;
    QLabel *ActionLabel;
    QSpacerItem *horizontalSpacer;
    QComboBox *Target2ComboBox;
    QLabel *target2Label;
    QComboBox *Target1ComboBox;
    QComboBox *actionTypeComboBox;
    QLabel *target1Label;
    QFrame *connectionGridFrame;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *connectionLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *editRuleLibrary)
    {
        if (editRuleLibrary->objectName().isEmpty())
            editRuleLibrary->setObjectName(QString::fromUtf8("editRuleLibrary"));
        editRuleLibrary->resize(925, 575);
        verticalLayout_3 = new QVBoxLayout(editRuleLibrary);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridFrame = new QFrame(editRuleLibrary);
        gridFrame->setObjectName(QString::fromUtf8("gridFrame"));
        gridLayout_4 = new QGridLayout(gridFrame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        addRulesButton = new QPushButton(gridFrame);
        addRulesButton->setObjectName(QString::fromUtf8("addRulesButton"));

        gridLayout_4->addWidget(addRulesButton, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        rulesScrollArea = new QScrollArea(gridFrame);
        rulesScrollArea->setObjectName(QString::fromUtf8("rulesScrollArea"));
        rulesScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 350, 477));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        treeWidget = new QTreeWidget(scrollAreaWidgetContents_2);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout_4->addWidget(treeWidget);

        rulesScrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_4->addWidget(rulesScrollArea, 1, 0, 1, 3);


        horizontalLayout->addWidget(gridFrame);

        scrollArea = new QScrollArea(editRuleLibrary);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 538, 514));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        ruleSettingsFrame = new QFrame(scrollAreaWidgetContents);
        ruleSettingsFrame->setObjectName(QString::fromUtf8("ruleSettingsFrame"));
        verticalLayout = new QVBoxLayout(ruleSettingsFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridFrame1 = new QFrame(ruleSettingsFrame);
        gridFrame1->setObjectName(QString::fromUtf8("gridFrame1"));
        gridLayout = new QGridLayout(gridFrame1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(gridFrame1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        textEdit = new QTextEdit(gridFrame1);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 2, 1, 1, 2);

        lineEdit = new QLineEdit(gridFrame1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(gridFrame1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(gridFrame1);

        triggerGridFrame = new QFrame(ruleSettingsFrame);
        triggerGridFrame->setObjectName(QString::fromUtf8("triggerGridFrame"));
        gridLayout_2 = new QGridLayout(triggerGridFrame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        TriggerLabel = new QLabel(triggerGridFrame);
        TriggerLabel->setObjectName(QString::fromUtf8("TriggerLabel"));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        TriggerLabel->setFont(font);

        gridLayout_2->addWidget(TriggerLabel, 0, 0, 1, 1);

        conditionTypeLabel = new QLabel(triggerGridFrame);
        conditionTypeLabel->setObjectName(QString::fromUtf8("conditionTypeLabel"));

        gridLayout_2->addWidget(conditionTypeLabel, 1, 0, 1, 1);

        conditionTypeComboBox = new QComboBox(triggerGridFrame);
        conditionTypeComboBox->addItem(QString());
        conditionTypeComboBox->addItem(QString());
        conditionTypeComboBox->addItem(QString());
        conditionTypeComboBox->setObjectName(QString::fromUtf8("conditionTypeComboBox"));

        gridLayout_2->addWidget(conditionTypeComboBox, 1, 1, 1, 1);

        monitiorObjectLabel = new QLabel(triggerGridFrame);
        monitiorObjectLabel->setObjectName(QString::fromUtf8("monitiorObjectLabel"));

        gridLayout_2->addWidget(monitiorObjectLabel, 2, 0, 1, 1);

        monitorObjectComboBox = new QComboBox(triggerGridFrame);
        monitorObjectComboBox->setObjectName(QString::fromUtf8("monitorObjectComboBox"));

        gridLayout_2->addWidget(monitorObjectComboBox, 2, 1, 1, 2);

        conditionLabel = new QLabel(triggerGridFrame);
        conditionLabel->setObjectName(QString::fromUtf8("conditionLabel"));

        gridLayout_2->addWidget(conditionLabel, 3, 0, 1, 1);

        ConditionOperatorComboBox = new QComboBox(triggerGridFrame);
        ConditionOperatorComboBox->addItem(QString());
        ConditionOperatorComboBox->addItem(QString());
        ConditionOperatorComboBox->addItem(QString());
        ConditionOperatorComboBox->addItem(QString());
        ConditionOperatorComboBox->addItem(QString());
        ConditionOperatorComboBox->addItem(QString());
        ConditionOperatorComboBox->setObjectName(QString::fromUtf8("ConditionOperatorComboBox"));

        gridLayout_2->addWidget(ConditionOperatorComboBox, 3, 1, 1, 1);

        conditionValueLineEdit = new QLineEdit(triggerGridFrame);
        conditionValueLineEdit->setObjectName(QString::fromUtf8("conditionValueLineEdit"));

        gridLayout_2->addWidget(conditionValueLineEdit, 3, 2, 1, 1);

        conditionUnitLabel = new QLabel(triggerGridFrame);
        conditionUnitLabel->setObjectName(QString::fromUtf8("conditionUnitLabel"));

        gridLayout_2->addWidget(conditionUnitLabel, 3, 3, 1, 1);

        durationLabel = new QLabel(triggerGridFrame);
        durationLabel->setObjectName(QString::fromUtf8("durationLabel"));

        gridLayout_2->addWidget(durationLabel, 4, 0, 1, 1);

        durationValueLineEdit = new QLineEdit(triggerGridFrame);
        durationValueLineEdit->setObjectName(QString::fromUtf8("durationValueLineEdit"));

        gridLayout_2->addWidget(durationValueLineEdit, 4, 1, 1, 1);

        durationUnitComboBox = new QComboBox(triggerGridFrame);
        durationUnitComboBox->addItem(QString());
        durationUnitComboBox->addItem(QString());
        durationUnitComboBox->addItem(QString());
        durationUnitComboBox->addItem(QString());
        durationUnitComboBox->setObjectName(QString::fromUtf8("durationUnitComboBox"));

        gridLayout_2->addWidget(durationUnitComboBox, 4, 2, 1, 1);


        verticalLayout->addWidget(triggerGridFrame);

        actionGridFrame = new QFrame(ruleSettingsFrame);
        actionGridFrame->setObjectName(QString::fromUtf8("actionGridFrame"));
        actionGridLayout = new QGridLayout(actionGridFrame);
        actionGridLayout->setObjectName(QString::fromUtf8("actionGridLayout"));
        actionTypeLabel = new QLabel(actionGridFrame);
        actionTypeLabel->setObjectName(QString::fromUtf8("actionTypeLabel"));

        actionGridLayout->addWidget(actionTypeLabel, 1, 0, 1, 1);

        ActionLabel = new QLabel(actionGridFrame);
        ActionLabel->setObjectName(QString::fromUtf8("ActionLabel"));
        ActionLabel->setFont(font);

        actionGridLayout->addWidget(ActionLabel, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        actionGridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        Target2ComboBox = new QComboBox(actionGridFrame);
        Target2ComboBox->setObjectName(QString::fromUtf8("Target2ComboBox"));

        actionGridLayout->addWidget(Target2ComboBox, 3, 1, 1, 2);

        target2Label = new QLabel(actionGridFrame);
        target2Label->setObjectName(QString::fromUtf8("target2Label"));

        actionGridLayout->addWidget(target2Label, 3, 0, 1, 1);

        Target1ComboBox = new QComboBox(actionGridFrame);
        Target1ComboBox->setObjectName(QString::fromUtf8("Target1ComboBox"));

        actionGridLayout->addWidget(Target1ComboBox, 2, 1, 1, 2);

        actionTypeComboBox = new QComboBox(actionGridFrame);
        actionTypeComboBox->addItem(QString());
        actionTypeComboBox->addItem(QString());
        actionTypeComboBox->addItem(QString());
        actionTypeComboBox->setObjectName(QString::fromUtf8("actionTypeComboBox"));

        actionGridLayout->addWidget(actionTypeComboBox, 1, 1, 1, 1);

        target1Label = new QLabel(actionGridFrame);
        target1Label->setObjectName(QString::fromUtf8("target1Label"));

        actionGridLayout->addWidget(target1Label, 2, 0, 1, 1);


        verticalLayout->addWidget(actionGridFrame);

        connectionGridFrame = new QFrame(ruleSettingsFrame);
        connectionGridFrame->setObjectName(QString::fromUtf8("connectionGridFrame"));
        gridLayout_3 = new QGridLayout(connectionGridFrame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton = new QPushButton(connectionGridFrame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_3->addWidget(pushButton, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        connectionLabel = new QLabel(connectionGridFrame);
        connectionLabel->setObjectName(QString::fromUtf8("connectionLabel"));
        connectionLabel->setFont(font);

        gridLayout_3->addWidget(connectionLabel, 0, 0, 1, 1);


        verticalLayout->addWidget(connectionGridFrame);


        verticalLayout_2->addWidget(ruleSettingsFrame);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        verticalLayout_3->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(editRuleLibrary);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(editRuleLibrary);
        QObject::connect(buttonBox, SIGNAL(accepted()), editRuleLibrary, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), editRuleLibrary, SLOT(reject()));

        QMetaObject::connectSlotsByName(editRuleLibrary);
    } // setupUi

    void retranslateUi(QDialog *editRuleLibrary)
    {
        editRuleLibrary->setWindowTitle(QApplication::translate("editRuleLibrary", "Dialog", nullptr));
        addRulesButton->setText(QApplication::translate("editRuleLibrary", "add", nullptr));
        label_2->setText(QApplication::translate("editRuleLibrary", "comments", nullptr));
        label->setText(QApplication::translate("editRuleLibrary", "ruleName", nullptr));
        TriggerLabel->setText(QApplication::translate("editRuleLibrary", "Trigger", nullptr));
        conditionTypeLabel->setText(QApplication::translate("editRuleLibrary", "condition type", nullptr));
        conditionTypeComboBox->setItemText(0, QApplication::translate("editRuleLibrary", "state", nullptr));
        conditionTypeComboBox->setItemText(1, QApplication::translate("editRuleLibrary", "event", nullptr));
        conditionTypeComboBox->setItemText(2, QApplication::translate("editRuleLibrary", "time", nullptr));

        monitiorObjectLabel->setText(QApplication::translate("editRuleLibrary", "monitor object", nullptr));
        conditionLabel->setText(QApplication::translate("editRuleLibrary", "condition", nullptr));
        ConditionOperatorComboBox->setItemText(0, QApplication::translate("editRuleLibrary", ">", nullptr));
        ConditionOperatorComboBox->setItemText(1, QApplication::translate("editRuleLibrary", "<", nullptr));
        ConditionOperatorComboBox->setItemText(2, QApplication::translate("editRuleLibrary", "=", nullptr));
        ConditionOperatorComboBox->setItemText(3, QApplication::translate("editRuleLibrary", "\342\211\245", nullptr));
        ConditionOperatorComboBox->setItemText(4, QApplication::translate("editRuleLibrary", "\342\211\244", nullptr));
        ConditionOperatorComboBox->setItemText(5, QApplication::translate("editRuleLibrary", "\342\211\240", nullptr));

        conditionUnitLabel->setText(QApplication::translate("editRuleLibrary", "token(s)", nullptr));
        durationLabel->setText(QApplication::translate("editRuleLibrary", "duration", nullptr));
        durationUnitComboBox->setItemText(0, QApplication::translate("editRuleLibrary", "ms", nullptr));
        durationUnitComboBox->setItemText(1, QApplication::translate("editRuleLibrary", "s", nullptr));
        durationUnitComboBox->setItemText(2, QApplication::translate("editRuleLibrary", "min", nullptr));
        durationUnitComboBox->setItemText(3, QApplication::translate("editRuleLibrary", "h", nullptr));

        actionTypeLabel->setText(QApplication::translate("editRuleLibrary", "action type", nullptr));
        ActionLabel->setText(QApplication::translate("editRuleLibrary", "Action", nullptr));
        target2Label->setText(QApplication::translate("editRuleLibrary", "to", nullptr));
        actionTypeComboBox->setItemText(0, QApplication::translate("editRuleLibrary", "create", nullptr));
        actionTypeComboBox->setItemText(1, QApplication::translate("editRuleLibrary", "delete", nullptr));
        actionTypeComboBox->setItemText(2, QApplication::translate("editRuleLibrary", "update", nullptr));

        target1Label->setText(QApplication::translate("editRuleLibrary", "target", nullptr));
        pushButton->setText(QApplication::translate("editRuleLibrary", "Add", nullptr));
        connectionLabel->setText(QApplication::translate("editRuleLibrary", "Connections", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editRuleLibrary: public Ui_editRuleLibrary {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRULELIBRARY_H
