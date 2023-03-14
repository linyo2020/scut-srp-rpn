#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QUrl>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QTextStream>

#include"componentlist.h"
#include "xmlparser.h"
#include "xmlwriter.h"
#include "messagehandler.h"
#include "petritabwidget.h"
#include "ptnscene.h"
#include"component.h"
#include"compoundcomponentlist.h"
#include"QVector"
#include"rulemanager.h"

class TabWidget : public QTabWidget
{
     Q_OBJECT
public:
     explicit TabWidget (QWidget * parent = 0);
    /*
     * QTabWidget是带标签页的窗口，可以存储多个子窗口，
     * 每个子窗口的显示可以通过对应的标签index进行切换。
     */
     bool validateXml(QFile& file, MessageHandler &messageHandler);
    //槽函数
    void closeTab(int index);//关闭子窗口
    void removeItems ();
    void undo ();
    void redo ();
    void zoom (int val);
    //新建窗口
    void createNew ();
    //打开子网
    bool open (MessageHandler &messageHandler);
    //打开组件
    bool openComponent (MessageHandler &messageHandler);
    bool addComponent(COMPONENT_ATTR component_Attr);
    //添加组件
    void addExistedComponent (QString componentName);
    //解除组件，绑定组件
    void unbindComponent();
    void bindComponent();
    //更新窗口名
    void updateTitle (bool changed);

    void save ();
    void saveAs ();
    void exportNet ();
    void print();

    //保存组件
    void saveComponent ();
    void saveAsComponent ();
    //点击仿真按钮时执行的保存操作
    //void saveLocalComponent();
    //仿真结束后重新读取本地保存文件
    //void openLocalComponent();
    //还没写
    //把复合组件的内容写到Scene
    void writeToScene(CompoundComponent* comp_com,PTNscene*scene);
    //获取组件名
    QStringList getFileNames ();
    QVector<Component*> getcom_arry();
    QList<Connector*> init_cl();
    //关于组件id的设置
    void setComponentType(QString type);
    void setElementId();
    int componentTypeNum;
    void setImportComponentID();
    bool componentIdEdited(QString ori_ID);
    void setImportComponentId_AND_classsifyComponenet();
    QString getComponenttype(QString id);
    RuleManager &getRuleManager();

    //2023.03.14
    bool isComponentUsed(QString componentName);

//    void saveModel();
    void gets(PTNscene*scene);
signals:
//    void addComponentTreeNode (QString componentName,QString componentPath);
    void canRedoChange (bool canRedo);
    void canUndoChange (bool canUndo);
    void tabChanged (int index);
    void errorMessage (const QString &msg);
    //2023.0313
//    void addComponentTreeNode(COMPONENT_ATTR componentAttr);
    void addComponentTreeNode(QString componentName);
//    void ElementIdEditFinished();
//    void addComponentFinished();
//    void saveComponentFinished();
//    void startSimulation(PTNscene*scene);
//    void finishSimulation();
protected:
    //连接具体页面的信号和槽，用于传递Undo，Redo，netChanged，error信息
    void connectSignalAndSlot(PetriTabWidget * tab);

private:
    int nets_indexes;
    QStringList fileNames;
    QVector<Component*>component_List;//bug
    ComponentList*com_list;
    QVector<Component*>com_arry;
    QMap<QString,int>type_count;
    //todo，保存的Pertritabwidget复制
    PetriTabWidget*tab_copy;
    //2023.03.13
    QMap<QString,COMPONENT_ATTR>m_mCompName2Attr;
};

#endif // TABWIDGET_H
