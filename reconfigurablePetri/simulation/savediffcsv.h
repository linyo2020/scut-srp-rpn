#ifndef SAVEDIFFCSV_H
#define SAVEDIFFCSV_H

#include <QDialog>
#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>

namespace Ui {
class savediffcsv;
}

class savediffcsv : public QDialog
{
    Q_OBJECT

public:
    explicit savediffcsv(QWidget *parent = 0);
    ~savediffcsv();
    void setId(QString id)
    {
        PlotId=id;
    }

private slots:
    /**
     * @brief on_pushButton_clicked
     */
    void on_pushButton_clicked();
    /**
     * @brief on_pushButton_3_clicked
     */
    void on_pushButton_3_clicked();
    /**
     * @brief on_pushButton_2_clicked
     */
    void on_pushButton_2_clicked();

private:
    QString PlotId;
    Ui::savediffcsv *ui;
};

#endif // SAVEDIFFCSV_H
