#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "QSqlQuery"
#include "QDebug"
#include "QMessageBox"
#include "QSqlError"
#include "QSqlRecord"
#include "carwashui.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

//КНОПКА ОТМЕНА
void LoginWindow::on_pushButton_clicked()
{
    close();
    qDebug() << "loginWindow EXIT";
}

//КОСТЫЛЬ
void LoginWindow::on_pushButton_2_clicked()
{}

//КНОПКА АВТОРИЗАЦИЯ
void LoginWindow::on_pushButton_3_clicked()
{
    QString login = ui->lineEdit_login->text(); //логин
    QString password = ui->lineEdit_password->text(); //пароль

    QSqlQuery query;
    query.prepare("SELECT name, surname, staff_id FROM staff WHERE \
    binary login = :login AND binary staff_password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.exec();

    if(query.next())
    {
        QString name = query.value(0).toString();
        QString surname = query.value(1).toString();
        QString id = query.value(2).toString();
        //ПРАВИЛЬНЫЙ ЛОГИН И ПАРОЛЬ
        qDebug() << "loginWindow " << name << " " << surname << " вошел в сеть. Уникальный ID: " << id;

        //открывается окно
        CarwashUI *carwashUI = new CarwashUI(this);
        close();
        carwashUI->setWindowModality(Qt::ApplicationModal);
        carwashUI->setWindowTitle("CarwashUI: " + name + " " + surname);
        carwashUI->show();

    }
    else
    {
        //НЕПРАВИЛЬНЫЙ ЛОГИН ИЛИ ПАРОЛЬ
        QMessageBox::warning(0, "Ошибка!", "Неверный логин или пароль");
        qDebug() << "loginWindow Введены неправильные данные";
    }
}

