#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDate"
#include "QDebug"
#include "editusers.h"
#include "addnewentry.h"
#include "user.h"
#include "usermanager.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QDateEdit *dateEdit = ui->dateEdit;

    QDate now = QDate::currentDate();
    dateEdit->setDate(now);
    QDate date = ui->dateEdit->date();
    QString dateString = date.toString();
    QList <User> users = UserManager::getInstance()->getUsers();
    qDebug()<<users.first().name;
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::on_editUserBtn_clicked() {
    EditUsers editUsers;
    editUsers.setModal(true);
    editUsers.exec();
}

void MainWindow::on_btnAddEntry_clicked()
{
    AddNewEntry addNewEntry;
    addNewEntry.setModal(true);
    addNewEntry.exec();
}
