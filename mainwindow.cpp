#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "QDebug"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked() //КНОПКА ВЫХОД
{
    QApplication::quit();
}


void MainWindow::on_pushButton_clicked() //КНОПКА АВТОРИЗАЦИЯ
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); //ПРОВЕРКА СОЕДИНЕНИЯ С БД
      db.setHostName("127.0.0.1");
      db.setDatabaseName("carwash");
      db.setUserName("root");
      db.setPassword("root");
      bool ok = db.open();

      if(ok)
      {
          qDebug() << "mainWindow Database connected!";
          LoginWindow *loginWindow = new LoginWindow(this); //ОКНО ЛОГИНА ОТКРЫВАЕТСЯ
          loginWindow->setWindowTitle("Авторизация в систему");
          loginWindow->setWindowModality(Qt::ApplicationModal); //делает юзабельным только это окно, блокирует все под ним
          loginWindow->show();
      }
      else
      {                                 //ВЫВОДИТСЯ ОШИБКА НЕТ СОЕДИНЕНИЯ
          QMessageBox::warning(this, "Carwash", "Нет соединения с базой  данных!");
          qDebug() << "mainWindow No connection to database";
      }

}

