#ifndef TRANSITIONEDITDIALOG_H
#define TRANSITIONEDITDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QToolTip>
#include <QTabWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QTableWidget>

#include "graphicsedittab.h"

class TransitionEditDialog : public QDialog
{
    Q_OBJECT

friend class PetriTabWidget;

public:
    explicit TransitionEditDialog(QWidget *parent = 0);
    ~TransitionEditDialog();

signals:

public slots:

   void showRotDegree(int d);

private:
    GraphicsEditTab *m_graphicsEditTab;

   QHBoxLayout * hlayout;
   QVBoxLayout * vlayout;
   QFormLayout * flayout;
   QLineEdit   * inputLabel;
   QLineEdit   * inputLabel1;
   //QLineEdit   * inputLabel2;
   QSlider     * slider;
   QPushButton * validateButton;
   QPushButton * cancelButton;
   QGroupBox * groupBox;

   QTabWidget  * m_tabWidget;
   QWidget     * m_tab1;
   //QWidget     * m_tab2;
   GraphicsEditTab     * m_tab3;
   QLabel      * m_transitionID;
   QTextEdit * m_plainTextEdit;
   QCheckBox   * m_showComment;
   QLabel      * m_commentLabel;
   QHBoxLayout * m_commentHlayout;
   //QFormLayout * m_tab2Flayout;
   //QPushButton * m_checkFunction;
   //QPushButton * m_functionAssistant;
   //QPushButton * m_functionOverview;
   //QPlainTextEdit * m_functionEdit;
};

#endif // TRANSITIONEDITDIALOG_H
