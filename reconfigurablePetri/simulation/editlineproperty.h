#ifndef EDITLINEPROPERTY_H
#define EDITLINEPROPERTY_H

#include <QWidget>
#include<QDialog>

namespace Ui {
class editlineproperty;
}

/**
 * @brief The editlineproperty class
 */
class editlineproperty : public QWidget
{
    Q_OBJECT

public:
    explicit editlineproperty(QWidget *parent = 0);
    ~editlineproperty();

private slots:
    void on_pushButton_3_clicked();
    void showColor();
    void initialComboBox();
    void getNewData();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::editlineproperty *ui;
};

#endif // EDITLINEPROPERTY_H
