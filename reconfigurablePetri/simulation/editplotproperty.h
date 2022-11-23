#ifndef EDITPLOTPROPERTY_H
#define EDITPLOTPROPERTY_H

#include <QDialog>

namespace Ui {
class editplotproperty;
}
/**
 * @brief The editplotproperty class
 */
class editplotproperty : public QDialog
{
    Q_OBJECT

public:
    explicit editplotproperty(QWidget *parent = 0);
    ~editplotproperty();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void showColor();
    void initialComboBox();
    void getNewData();

private:
    Ui::editplotproperty *ui;
};

#endif // EDITPLOTPROPERTY_H
