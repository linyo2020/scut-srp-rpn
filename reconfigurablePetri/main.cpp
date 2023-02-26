#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     MainWindow w;
    w.setWindowTitle("变结构Petri网建模工具软件");
    w.setMinimumSize(1440,900);
    w.showMaximized();
    w.show();
    return a.exec();
}
