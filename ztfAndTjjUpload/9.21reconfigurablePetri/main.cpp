#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     MainWindow w;
    w.setWindowTitle("reconfigurable petri nets tool");
    w.setMinimumSize(1440,900);
    w.showMaximized();
    w.show();

    return a.exec();
}
