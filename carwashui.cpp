#include "carwashui.h"
#include "ui_carwashui.h"
#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QDebug"
#include "QMessageBox"
#include <QKeyEvent>

CarwashUI::CarwashUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CarwashUI)
{
    ui->setupUi(this);
    on_lineEdit_search_textEdited("");
    ui->stackedWidget->setCurrentWidget(0);
    ui->pageBackButton->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

CarwashUI::~CarwashUI()
{
    delete ui;
}    

void CarwashUI::on_pushButton_clicked() //РАЗДЕЛ ПОИСК
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("background-color: darkGreen; color: white");
    ui->pushButton_4->setStyleSheet("background-color: rgb(80, 80, 80); color:white");
    ui->pushButton_6->setStyleSheet("background-color: rgb(80, 80, 80); color: white");
    on_lineEdit_search_textEdited(ui->lineEdit_search->text());
}


void CarwashUI::on_pushButton_4_clicked() //РАЗДЕЛ ДОБАВИТЬ
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_4->setStyleSheet("background-color: darkGreen; color: white");
    ui->pushButton->setStyleSheet("background-color: rgb(80, 80, 80); color: white");
    ui->pushButton_6->setStyleSheet("background-color: rgb(80, 80, 80); color: white");
}

void CarwashUI::on_pushButton_6_clicked() //РАЗДЕЛ СПРАВКА
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_6->setStyleSheet("background-color: darkGreen; color: white");
    ui->pushButton->setStyleSheet("background-color: rgb(80, 80, 80); color: white");
    ui->pushButton_4->setStyleSheet("background-color: rgb(80, 80, 80); color: white");
}

void CarwashUI::on_pushButton_5_clicked() //ВЫХОД
{
    QApplication::quit();
}

void CarwashUI::on_pushButton_5_pressed() //ПОКРАСКА ВЫХОДА
{
    ui->pushButton_5->setStyleSheet("background-color: darkRed; color: white");
}

void CarwashUI::on_pushButton_5_released() //ПОКРАСКА ВЫХОДА ОБРАТНО
{
    ui->pushButton_5->setStyleSheet("background-color: rgb(80, 80, 80); color: white");
}


void CarwashUI::on_lineEdit_search_textEdited(const QString &arg1) //ДЛЯ ПОИСКА ВВОДОМ
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QString order = ui->comboBox->currentText();
    QString search = ui->lineEdit_search->text();
    search += "%";
    QSqlQuery query;
    QString queryText = "SELECT DISTINCT orders.orders_id, orders.orders_date, vehicle.*, client.* \
        FROM orders, vehicle, client WHERE orders.vehicle_id = vehicle.vehicle_id AND \
        orders.client_id = client.client_id AND (orders.orders_date LIKE :search OR orders.orders_id LIKE \
        :search OR vehicle.vehicle_id LIKE :search OR vehicle.brand LIKE :search OR vehicle.plate \
        LIKE :search OR vehicle.color LIKE :search OR client.client_id LIKE :search OR client.client_phone \
        LIKE :search OR client.card_id LIKE :search OR client.name LIKE :search OR client.surname LIKE :search)\
        ORDER BY %1";
        queryText = queryText.arg(order);
    query.prepare(queryText);
    query.bindValue(":search", search);
    query.bindValue(":order", order);
    query.exec();

    modal->setQuery(query);
    modal->setHeaderData(0, Qt::Horizontal, "ID Заказа");
    modal->setHeaderData(1, Qt::Horizontal, "Дата");
    modal->setHeaderData(2, Qt::Horizontal, "ID Авто");
    modal->setHeaderData(3, Qt::Horizontal, "Бренд");
    modal->setHeaderData(4, Qt::Horizontal, "Номера");
    modal->setHeaderData(5, Qt::Horizontal, "Цвет");
    modal->setHeaderData(6, Qt::Horizontal, "ID Клиента");
    modal->setHeaderData(7, Qt::Horizontal, "Телефон");
    modal->setHeaderData(8, Qt::Horizontal, "Карта");
    modal->setHeaderData(9, Qt::Horizontal, "Имя");
    modal->setHeaderData(10, Qt::Horizontal, "Фамилия");
    ui->tableView->setModel(modal);
    ui->tableView->setStyleSheet("QHeaderView::section { background-color:gray }");
}


void CarwashUI::on_comboBox_currentTextChanged(const QString &arg1) //КОМБОБОКС ДЛЯ ПОИСКА
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QString order = ui->comboBox->currentText();
    QString search = ui->lineEdit_search->text();
    search += "%";
    QSqlQuery query;
    QString queryText = "SELECT DISTINCT orders.orders_id, orders.orders_date, vehicle.*, client.* \
        FROM orders, vehicle, client WHERE orders.vehicle_id = vehicle.vehicle_id AND \
        orders.client_id = client.client_id AND (orders.orders_date LIKE :search OR orders.orders_id LIKE \
        :search OR vehicle.vehicle_id LIKE :search OR vehicle.brand LIKE :search OR vehicle.plate \
        LIKE :search OR vehicle.color LIKE :search OR client.client_id LIKE :search OR client.client_phone \
        LIKE :search OR client.card_id LIKE :search OR client.name LIKE :search OR client.surname LIKE :search)\
        ORDER BY %1";
        queryText = queryText.arg(order);
    query.prepare(queryText);
    query.bindValue(":search", search);
    query.bindValue(":order", order);
    query.exec();

    modal->setQuery(query);
    modal->setHeaderData(0, Qt::Horizontal, "ID Заказа");
    modal->setHeaderData(1, Qt::Horizontal, "Дата");
    modal->setHeaderData(2, Qt::Horizontal, "ID Авто");
    modal->setHeaderData(3, Qt::Horizontal, "Бренд");
    modal->setHeaderData(4, Qt::Horizontal, "Номера");
    modal->setHeaderData(5, Qt::Horizontal, "Цвет");
    modal->setHeaderData(6, Qt::Horizontal, "ID Клиента");
    modal->setHeaderData(7, Qt::Horizontal, "Телефон");
    modal->setHeaderData(8, Qt::Horizontal, "Карта");
    modal->setHeaderData(9, Qt::Horizontal, "Имя");
    modal->setHeaderData(10, Qt::Horizontal, "Фамилия");
    ui->tableView->setModel(modal);
    ui->tableView->setStyleSheet("QHeaderView::section { background-color:gray }");
}

void CarwashUI::switchPage()
{
    int currentIndex = ui->stackedWidget_2->currentIndex();

    QRegExpValidator *nameVal = new QRegExpValidator(QRegExp("[А-Яа-я]+"));
    ui->lineEdit_clname->setValidator(nameVal);
    ui->lineEdit_clsurname->setValidator(nameVal);
    ui->lineEdit_carColor->setValidator(nameVal);
    QRegExpValidator *brandVal = new QRegExpValidator(QRegExp("[а-яА-Яa-zA-Z]+"));
    ui->lineEdit_carBrand->setValidator(brandVal);
    //QRegExpValidator *plateVal = new QRegExpValidator(QRegExp("^[а-яА-Я][0-9]{3}[а-яА-Я]{2}[0-9]{2,3}+"));
    QRegExpValidator *phoneVal = new QRegExpValidator(QRegExp("^(8[0-9]{10})?"));
    ui->lineEdit_clphn->setValidator(phoneVal);
    QString name = ui->lineEdit_clname->text();
    QString surname = ui->lineEdit_clsurname->text();
    int zero = 0;
    QValidator::State nameState = nameVal->validate(name, zero);
    QValidator::State surnameState = nameVal->validate(surname, zero);
    if((nameState == QValidator::Acceptable && currentIndex == 0) || (nameState == QValidator::Acceptable && surnameState == QValidator::Acceptable && currentIndex >= 1))
    {
        currentIndex++;
        qDebug() << "index->" << ui->stackedWidget_2->currentIndex();
        if(currentIndex == ui->stackedWidget_2->count() - 1)
        {
            addingTable();
        }
        if(currentIndex >= ui->stackedWidget_2->count())
        {
            if(ui->lineEdit_carBrand->text() != "" && ui->lineEdit_carPlate->text() != "")
            {
            currentIndex = 0;
            addData();
            }
            else QMessageBox::warning(0, "Ошибка!", "Поля бренда и номера не могут быть пустыми!");
        }
        ui->stackedWidget_2->setCurrentIndex(currentIndex);
        hideCheck(); //прячет кнопку назад если индекс меньше 1 и больше 6
    }
    else
    {

        ui->lineEdit_clname->setStyleSheet("QLineEdit {border-style:outset; border-width:4px; border-radius: 8px; color: rgb(255, 255, 255);\
                                            background-color: rgb(80, 80, 80); border-color: rgb(255, 0, 0);}");

    }
}

void CarwashUI::hideCheck()
{
    int currentIndex = ui->stackedWidget_2->currentIndex();
    if(currentIndex >= 1 && currentIndex <= 6)
    {
        ui->pageBackButton->show();
    }
    else ui->pageBackButton->hide();
}

void CarwashUI::on_pageBackButton_clicked()
{
    int currentIndex = ui->stackedWidget_2->currentIndex();
    currentIndex--;
    ui->stackedWidget_2->setCurrentIndex(currentIndex);
    hideCheck(); //прячет кнопку назад если индекс меньше 1 и больше 6
}

void CarwashUI::on_pushButton_3_clicked()
{
    int currentIndex = ui->stackedWidget_2->currentIndex();
    currentIndex--;
    ui->stackedWidget_2->setCurrentIndex(currentIndex);
    hideCheck(); //прячет кнопку назад если индекс меньше 1 и больше 6
}

void CarwashUI::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        if(ui->stackedWidget->currentIndex() == 1)
        {
        switchPage();
        qDebug() << "enter pressed";
        }
    }
}

void CarwashUI::addingTable()
{
    QString name = ui->lineEdit_clname->text();
    QString surname = ui->lineEdit_clsurname->text();
    QString phone = ui->lineEdit_clphn->text();
    QString loyCard = ui->lineEdit_clcard->text();
    QString carBrand = ui->lineEdit_carBrand->text();
    QString carColor = ui->lineEdit_carColor->text();
    QString carPlate = ui->lineEdit_carPlate->text();
    QStringList headers = {"Имя", "Фамилия", "Телефон", "Карта", "Бренд", "Цвет", "Номера"};

    ui->tableAdding->setColumnCount(7);
    ui->tableAdding->setRowCount(1);
    ui->tableAdding->setShowGrid(true);
    ui->tableAdding->setHorizontalHeaderLabels(headers);
    ui->tableAdding->setItem(0, 0, new QTableWidgetItem(name));
    ui->tableAdding->setItem(0, 1, new QTableWidgetItem(surname));
    ui->tableAdding->setItem(0, 2, new QTableWidgetItem(phone));
    ui->tableAdding->setItem(0, 3, new QTableWidgetItem(loyCard));
    ui->tableAdding->setItem(0, 4, new QTableWidgetItem(carBrand));
    ui->tableAdding->setItem(0, 5, new QTableWidgetItem(carColor));
    ui->tableAdding->setItem(0, 6, new QTableWidgetItem(carPlate));
    ui->tableAdding->setStyleSheet("QHeaderView::section { background-color:gray }");
}

void CarwashUI::addData()
{
    QString name = ui->lineEdit_clname->text();
    QString surname = ui->lineEdit_clsurname->text();
    QString phone = ui->lineEdit_clphn->text();
    QString loyCard = ui->lineEdit_clcard->text();
    QString carBrand = ui->lineEdit_carBrand->text();
    QString carColor = ui->lineEdit_carColor->text();
    QString carPlate = ui->lineEdit_carPlate->text();

    //ПОЛУЧЕНИЕ ID КЛИЕНТА
    QSqlQuery query;
    QString clientId;
    query.prepare("SELECT client_id FROM Client WHERE name = :name AND surname = :surname AND client_phone = :phone;");
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":phone", phone);
    query.exec();
    if(query.next())
    {
        clientId = query.value(0).toString();
    }
    else
    {
        QString clientInsert = "INSERT INTO Client (client_phone, name, surname) VALUES (:phone, :name, :surname);";
        QSqlQuery clientInsertQ;
        clientInsertQ.prepare(clientInsert);
        clientInsertQ.bindValue(":name", name);
        clientInsertQ.bindValue(":surname", surname);
        clientInsertQ.bindValue(":phone", phone);
        clientInsertQ.exec();
        QSqlQuery clientCheckAgain;
        clientCheckAgain.prepare("SELECT getclientid();");
        clientCheckAgain.bindValue(":name", name);
        clientCheckAgain.bindValue(":surname", surname);
        clientCheckAgain.bindValue(":phone", phone);
        clientCheckAgain.exec();
        clientCheckAgain.next();
        clientId = clientCheckAgain.value(0).toString();
    }

    //ПОЛУЧЕНИЕ ID МАШИНЫ
    QSqlQuery getVehicleId;
    QString vehicleId;
    getVehicleId.prepare("SELECT vehicle_id FROM Vehicle WHERE plate = :plate;");
    getVehicleId.bindValue(":plate", carPlate);
    getVehicleId.exec();
    if(getVehicleId.next())
    {
        vehicleId = getVehicleId.value(0).toString();
    }
    else
    {
        QString vehicleInsert = "INSERT INTO Vehicle (brand, plate, color) VALUES (:brand, :plate, :color);";
        QSqlQuery vehicleInsertQ;
        vehicleInsertQ.prepare(vehicleInsert);
        vehicleInsertQ.bindValue(":brand", carBrand);
        vehicleInsertQ.bindValue(":plate", carPlate);
        vehicleInsertQ.bindValue(":color", carColor);
        vehicleInsertQ.exec();
        QSqlQuery vehicleCheckAgain;
        vehicleCheckAgain.prepare("SELECT vehicle_id FROM Vehicle WHERE plate = :plate;");
        vehicleCheckAgain.bindValue(":plate", carPlate);
        vehicleCheckAgain.exec();
        vehicleCheckAgain.next();
        vehicleId = vehicleCheckAgain.value(0).toString();
    }

    //ПОЛУЧЕНИЕ ID ПЛАТЕЖА
    QSqlQuery getPaymentId;
    QString paymentId;
    QString arr[] = {"Наличные", "Банковская карта"};
    QString payMethod = arr[rand() % 2];
    QSqlQuery insertPayment;
    insertPayment.prepare("INSERT INTO Payment VALUES (:id, :method);");
    insertPayment.bindValue(":id", paymentId);
    insertPayment.bindValue(":method", payMethod);
    insertPayment.exec();
    getPaymentId.prepare("SELECT getpaymentid();"); //функция
    getPaymentId.exec();
    getPaymentId.next();
    paymentId = getPaymentId.value(0).toString();

    //ПОЛУЧЕНИЕ ID МОЙЩИКА И ТИПА МОЙКИ
    QString arrWash[] = {"1", "2", "3"};
    QString washType = arrWash[rand() % 3];
    QString arrWasher[] = {"1", "2"};
    QString washer = arrWasher[rand() % 2];

    //ИНСЕРТ ОРДЕРС
    QString date;
    QSqlQuery getDate;
    getDate.prepare("SELECT CURDATE();");
    getDate.exec();
    getDate.next();
    date = getDate.value(0).toString();
    QString insertOrder = "INSERT INTO Orders (orders_date, client_id, payment_id, washer_id, cashier_id, vehicle_id, wash_id) VALUES \
                (:date, :clientId, :paymentId, :washerId, :cashierId, :vehicleId, :washId);";
    QSqlQuery insertOrderQ;
    insertOrderQ.prepare(insertOrder);
    insertOrderQ.bindValue(":clientId", clientId);
    insertOrderQ.bindValue(":paymentId", paymentId);
    insertOrderQ.bindValue(":washerId", washer);
    insertOrderQ.bindValue(":cashierId", 1);
    insertOrderQ.bindValue(":vehicleId", vehicleId);
    insertOrderQ.bindValue(":washId", washType);
    insertOrderQ.bindValue(":date", date);
    insertOrderQ.exec();

    qDebug() << "ДОБАВЛЕНИЕ" << clientId << "clientid " << vehicleId << "vehcileid " << paymentId <<
             "paymentid " << washer << "washer " << washType << "wT " << date << "d ";

    ui->lineEdit_clname->clear();
    ui->lineEdit_clsurname->clear();
    ui->lineEdit_clphn->clear();
    ui->lineEdit_clcard->clear();
    ui->lineEdit_carBrand->clear();
    ui->lineEdit_carColor->clear();
    ui->lineEdit_carPlate->clear();
}

void CarwashUI::on_pushButton_2_clicked() //ОТМЕНА
{
    qDebug() << "Отмена";
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->lineEdit_clname->clear();
    ui->lineEdit_clsurname->clear();
    ui->lineEdit_clphn->clear();
    ui->lineEdit_clcard->clear();
    ui->lineEdit_carBrand->clear();
    ui->lineEdit_carColor->clear();
    ui->lineEdit_carPlate->clear();
}
