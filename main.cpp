#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/pic/image/icon.png")); //иконка
    MainWindow w;
    w.setWindowTitle("CarwashUI");

    w.show();
    return a.exec();
}
