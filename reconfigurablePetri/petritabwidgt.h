#ifndef PETRITABWIDGT_H
#define PETRITABWIDGT_H

#include <QWidget>
#include <QGraphicsView>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <vector>
//对应#include "ptntab.h"是具体的子窗口

class PetriTabwidgt : public QWidget
{
    Q_OBJECT
public:
    explicit PetriTabwidgt(const QString &id, QWidget * parent = 0);
     ~PetriTabwidgt ();

    QString getId()
    {
        return id;
    }

    //槽函数
    void nodeInserted(const QPointF &itemPos, const QString &id);
    void nodesInserted (const QStringList& names);
    void itemDoubleClicked (QGraphicsItem* item);
signals:
    void canRedoChange (bool canRedo);
    void canUndoChange (bool canUndo);
    void netChanged (bool changed);
    void errorMessage (const QString &msg);
private:
    QString id, name;
    void createTab ();
    void connect_sigs_slots ();
};

#endif // PETRITABWIDGT_H
