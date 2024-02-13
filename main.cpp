#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("C:/Study/untitled1/image/icon.png")); //иконка
    MainWindow w;
    w.setWindowTitle("CarwashUI");

    w.show();
    return a.exec();
}
