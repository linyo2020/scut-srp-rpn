#ifndef ARCEDITDIALOG_H
#define ARCEDITDIALOG_H
#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>

//#include "mainwindow.h"
#include "graphicsedittab.h"
//#include "Simulation/plot.h"
class ArcEditDialog : public QDialog
{
  Q_OBJECT

 friend class PetriTabWidget;

 public:

    ArcEditDialog (QWidget * parent);
    ~ArcEditDialog ();

    // void showDialog(int w);
    // int getValue() const;

 public slots: /* */
 signals: /* */
 private:
    GraphicsEditTab *m_graphicsEditTab;
    QHBoxLayout * hlayout;
    QVBoxLayout * vlayout;
    QFormLayout * flayout;
    QPushButton * validateButton;
    QPushButton * cancelButton;
    QGroupBox * groupBox;
    QPushButton *outputButton;


    //RuleSet *m_pRuleSet;

    QVector<QString> l_vPlaces_ad;


public:

    /*
    void setRuleSet(RuleSet *set)
    {
        m_pRuleSet=set;
    }
    */
    void setlPlaces(QVector<QString> vStr)
    {
        l_vPlaces_ad.clear();
        int count=vStr.count();
        for(int i=0;i<count;i++)
        {
            QString temp=vStr[i];
            l_vPlaces_ad.push_back(temp);
        }
    }

};
#endif // ARCEDITDIALOG_H
