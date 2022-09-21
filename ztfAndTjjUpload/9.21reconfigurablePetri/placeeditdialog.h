#ifndef PLACEEDITDIALOG_H
#define PLACEEDITDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QTabWidget>
#include <QPlainTextEdit>

#include "graphicsedittab.h"

class PlaceEditDialog : public QDialog
{
    Q_OBJECT

 friend class PetriTabwidgt;

 public:

    PlaceEditDialog (QWidget * parent = 0);
    ~PlaceEditDialog ();

    //void show (const QString& nm, int t, int c);
    //QString getName () const;
    //int getTokens() const;
    //int getCapacity() const;
    //bool showAttributes();

 public slots:
 signals:
 private:
     GraphicsEditTab *m_graphicsEditTab;
    QTabWidget  * m_tabwidget;//tabwidget,make dialog tidy
    QHBoxLayout * hlayout;
    QHBoxLayout * hlayout2;
    QVBoxLayout * vlayout;
    QVBoxLayout * vlayout2;
    QFormLayout * flayout;
    QLineEdit   * inputLabel;
    QLineEdit   * inputTokens;
    QSpinBox   * inputCapacity;
    QCheckBox   * chckBox;
    QLabel      * label;
    QPushButton * validateButton;
    QPushButton * cancelButton;
    QGroupBox   * groupBox;
    QLabel      * m_placeID;
    QTextEdit * m_plainTextEdit;
    QCheckBox   * m_showComment;
    QLabel      * m_commentLabel;
    QHBoxLayout * m_commentHlayout;
    //QGroupBox   * m_groupBox_1;
    //QFormLayout * m_flayout_1;
    //QSpinBox    * m_radiusSpinBox;
};

#endif // PLACEEDITDIALOG_H

