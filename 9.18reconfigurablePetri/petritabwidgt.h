#ifndef PETRITABWIDGT_H
#define PETRITABWIDGT_H

#include <QWidget>
#include <QGraphicsView>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <vector>

//对应#include "ptntab.h"是用于具体建模的子窗口

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
    void setMode (int mode);
    int  getMode () const;
    void setCursorShape ();
    void removeItems ();
    void undo ();
    void redo ();
    bool canRedo ();
    bool canUndo ();
    void cleanUndostack();
    void scaleView (qreal val);
    qreal scaleValue ();
    void showErrorMessage (const QString &title, const QString &errorMsg);
    const QString& getFilename ();
    void setFilename (const QString& filenm);
    void exportNet (const QString &imagefile);
    bool isNetEmpty();
    bool isSaved ();

    bool checkNet ();
    bool checkMarking();
    bool checkNodesConnections();
    void checkNodesNames();

    //#include "graphvisualizer.h"（其余成员编写相关代码）
//    GraphVisualizer * createGraphVis ();
//    GraphVisualizer * getGraphVis ();
//    三元素按钮的点击
//    void placeDoubleClicked (QGraphicsItem* item);
//    void transitionDoubleClicked (QGraphicsItem* item);
//    void arcDoubleClicked (QGraphicsItem* item);
//    void setName(QString);
//    void setId(QString);

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
