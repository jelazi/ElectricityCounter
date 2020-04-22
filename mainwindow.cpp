#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDate"
#include "QDebug"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDateEdit *dateEdit = ui->dateEdit;



    QDate now = QDate::currentDate();
    dateEdit->setDate(now);
    QDate date = ui->dateEdit->date();
    QString dateString = date.toString();
    qDebug()<<dateString;
    QPushButton *button = ui->pushButton;
    if (date.year() == 2020) {
        button->setEnabled(true);
    } else {
        button->setEnabled(false);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


