#ifndef CARWASHUI_H
#define CARWASHUI_H

#include <QMainWindow>
#include "QStackedWidget"

namespace Ui {
class CarwashUI;
}

class CarwashUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit CarwashUI(QWidget *parent = nullptr);
    ~CarwashUI();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_search_textEdited(const QString &arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void switchPage();

    void addingTable();

    void addData();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void hideCheck();

    void on_pageBackButton_clicked();

    void on_pushButton_3_clicked();

protected:

    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::CarwashUI *ui;
    QStackedWidget QStackedWidget_2;
};

#endif // CARWASHUI_H
