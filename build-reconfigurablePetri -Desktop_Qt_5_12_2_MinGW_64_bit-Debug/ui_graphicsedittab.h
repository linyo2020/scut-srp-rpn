/********************************************************************************
** Form generated from reading UI file 'graphicsedittab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSEDITTAB_H
#define UI_GRAPHICSEDITTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicsEditTab
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *m_PenColor_l;
    QPushButton *m_PenColor_b;
    QPushButton *m_PenColorReset_b;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_BrushColor_l;
    QPushButton *m_BrushColor_b;
    QPushButton *m_BrushColorReset_b;

    void setupUi(QWidget *GraphicsEditTab)
    {
        if (GraphicsEditTab->objectName().isEmpty())
            GraphicsEditTab->setObjectName(QString::fromUtf8("GraphicsEditTab"));
        GraphicsEditTab->resize(400, 300);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        GraphicsEditTab->setFont(font);
        formLayout = new QFormLayout(GraphicsEditTab);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_PenColor_l = new QLabel(GraphicsEditTab);
        m_PenColor_l->setObjectName(QString::fromUtf8("m_PenColor_l"));

        horizontalLayout->addWidget(m_PenColor_l);

        m_PenColor_b = new QPushButton(GraphicsEditTab);
        m_PenColor_b->setObjectName(QString::fromUtf8("m_PenColor_b"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_PenColor_b->sizePolicy().hasHeightForWidth());
        m_PenColor_b->setSizePolicy(sizePolicy);
        m_PenColor_b->setMinimumSize(QSize(80, 0));
        m_PenColor_b->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        m_PenColor_b->setFlat(true);

        horizontalLayout->addWidget(m_PenColor_b);

        m_PenColorReset_b = new QPushButton(GraphicsEditTab);
        m_PenColorReset_b->setObjectName(QString::fromUtf8("m_PenColorReset_b"));

        horizontalLayout->addWidget(m_PenColorReset_b);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_BrushColor_l = new QLabel(GraphicsEditTab);
        m_BrushColor_l->setObjectName(QString::fromUtf8("m_BrushColor_l"));

        horizontalLayout_2->addWidget(m_BrushColor_l);

        m_BrushColor_b = new QPushButton(GraphicsEditTab);
        m_BrushColor_b->setObjectName(QString::fromUtf8("m_BrushColor_b"));
        m_BrushColor_b->setMinimumSize(QSize(80, 0));
        m_BrushColor_b->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);"));
        m_BrushColor_b->setFlat(true);

        horizontalLayout_2->addWidget(m_BrushColor_b);

        m_BrushColorReset_b = new QPushButton(GraphicsEditTab);
        m_BrushColorReset_b->setObjectName(QString::fromUtf8("m_BrushColorReset_b"));

        horizontalLayout_2->addWidget(m_BrushColorReset_b);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);


        retranslateUi(GraphicsEditTab);

        QMetaObject::connectSlotsByName(GraphicsEditTab);
    } // setupUi

    void retranslateUi(QWidget *GraphicsEditTab)
    {
        GraphicsEditTab->setWindowTitle(QApplication::translate("GraphicsEditTab", "Form", nullptr));
        m_PenColor_l->setText(QApplication::translate("GraphicsEditTab", "Pen Color:", nullptr));
        m_PenColor_b->setText(QApplication::translate("GraphicsEditTab", "Select Color", nullptr));
        m_PenColorReset_b->setText(QApplication::translate("GraphicsEditTab", "Default", nullptr));
        m_BrushColor_l->setText(QApplication::translate("GraphicsEditTab", "Brush Color:", nullptr));
        m_BrushColor_b->setText(QApplication::translate("GraphicsEditTab", "Select Color", nullptr));
        m_BrushColorReset_b->setText(QApplication::translate("GraphicsEditTab", "Default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphicsEditTab: public Ui_GraphicsEditTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSEDITTAB_H
