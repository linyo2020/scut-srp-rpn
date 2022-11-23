#ifndef EDITMANYPROPERTY_H
#define EDITMANYPROPERTY_H

#include <QDialog>

namespace Ui {
class editmanyproperty;
}
/**
 * @brief The editmanyproperty class
 */
class editmanyproperty : public QDialog
{
    Q_OBJECT

public:
    explicit editmanyproperty(QWidget *parent = 0);
    ~editmanyproperty();

private slots:
    void on_pushButton_2_clicked();
    void initialComboBox();

    void on_pushButton_clicked();

    void on_checkBox_3_stateChanged(int arg1);

private:
    Ui::editmanyproperty *ui;
};
#endif // EDITMANYPROPERTY_H
