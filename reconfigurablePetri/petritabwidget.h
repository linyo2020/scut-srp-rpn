#ifndef PETRITABWIDGET_H
#define PETRITABWIDGET_H

#include <QGraphicsView>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include "undostack.h"
//#include "graphvisualizer.h"
#include"component.h"
#include "placeeditdialog.h"
#include "transitioneditdialog.h"
#include "arceditdialog.h"
#include <vector>
#include"ptnet.h"

class PetriTabWidget : public QWidget
{
    Q_OBJECT

public:

    explicit PetriTabWidget(const QString &id, QWidget * parent = 0);
    PetriTabWidget(const PTNET_ATTR &ptnet, const QString& file);
    ~PetriTabWidget ();
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
    PTNET_ATTR toXml() const;
    PTNET_ATTR componentToXml() const;
    bool checkNet ();
    bool checkMarking();
    bool checkNodesConnections();
    void checkNodesNames();
    PTNscene* getSCene();

//    GraphVisualizer * createGraphVis ();
//    GraphVisualizer * getGraphVis ();

    void placeDoubleClicked (QGraphicsItem* item);
    void transitionDoubleClicked (QGraphicsItem* item);
    void arcDoubleClicked (QGraphicsItem* item);
    void setName(QString);
    void setId(QString);
    void setComponent(const PTNET_ATTR &ptnet, const QString& file);
    //bool arcnoclicked=true;
    void PushBack(Component*com);
    QString getComponentType(int i);
    int getComponentSize();
signals:

    void canRedoChange (bool canRedo);
    void canUndoChange (bool canUndo);
    void netChanged (bool changed);
    void errorMessage (const QString &msg);

public slots:

    void nodeInserted(const QPointF &itemPos, const QString &id);
    void nodesInserted (const QStringList& names);
    void itemDoubleClicked (QGraphicsItem* item);
    void save();
    void componentSave();

private:

    // xml attributes
    QString id, name;

    PTNscene * scene;
    QVector<Component*>component_vector;
    QGraphicsView * view;
    UndoStack  * undostack;
//    GraphVisualizer * graphVis;
//    QHBoxLayout * layout;

    int mode;
    qreal scaleVal;
    QStringList nodes_names;
    QString filename;

    PlaceEditDialog * placeEditDialog;
    TransitionEditDialog * transEditDialog;
    ArcEditDialog * arcEditDialog;
    //vector<Place> m_PlaceVector;
    //vector<Transition> m_TransitionVector;

    void createTab ();
    //用于连接场景和撤销栈的信号和槽函数连接，传递恢复、撤销、删除功能信息
    void connect_sigs_slots ();


    PTNet *mynet;//赋值给undostack
};

#endif // PETRITABWIDGET_H
