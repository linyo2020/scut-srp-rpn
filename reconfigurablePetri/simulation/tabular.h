#ifndef TABULAR_H
#define TABULAR_H

#include <QWidget>
#include<QTableWidget>
#include<QWidgetItem>
#include<QHeaderView>

namespace Ui {
class Tabular;
}

class Tabular : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Tabular
     * @param parent
     */
    explicit Tabular(QWidget *parent = 0);
    ~Tabular();
    /**
     * @brief setId
     * @param id
     */
    void setId(QString id)
    {
        PlotId=id;
    }
    /**
     * @brief initialTablev
     */
    void initialTablev();
private slots:
    /**
     * @brief addNewTableItem
     */
    void addNewTableItem();
    //void initialTablev();

private:
    QString PlotId;
    Ui::Tabular *ui;
};

#endif


