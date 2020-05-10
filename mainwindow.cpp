#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDate"
#include "QDebug"
#include <QtCore>
#include "editusers.h"
#include "addnewentry.h"

#include "usermanager.h"
#include "choicedate.h"
#include "invoicemanager.h"


QTableView *userTableMain;
QList <QString> dates;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Počítání elektřiny");

    QList <User> users = UserManager::getInstance()->getUsers();
    QList <Invoice> invoices = InvoiceManager::getInstance()->getInvoices();
    userTableMain = ui->userTable;
    createUserTable();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::createUserTable() {

     userTableMain->setModel(&modelMain);
     reloadUserTable();
     userTableMain->setSelectionBehavior(QAbstractItemView::SelectRows);
     userTableMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::reloadUserTable() {
    QList<User> usersList = UserManager::getInstance()->getUsers();
    modelMain.clear();
    horizontalHeader.clear();
    horizontalHeader.append("Jméno");
    horizontalHeader.append("Start NT");
    horizontalHeader.append("Start VT");
    dates = UserManager::getInstance()->getAllDates();
    foreach(QString date, dates) {
        horizontalHeader.append(date);
    }

    modelMain.setHorizontalHeaderLabels(horizontalHeader);
    modelMain.setVerticalHeaderLabels(verticalHeader);

    for(int i = 0; i < usersList.length();i++) {
        User user = usersList[i];
        QStandardItem *itemUserName = new QStandardItem(QString(user.name));
        modelMain.setItem(i, 0, itemUserName);
        QStandardItem *itemUserInitialDesicionNT = new QStandardItem(QString::number(user.initialDesicionNT.value, 'f', 2));
        modelMain.setItem(i, 1, itemUserInitialDesicionNT);
        QStandardItem *itemUserInitialDesicionVT = new QStandardItem(QString::number(user.initialDesicionVT.value, 'f', 2));
        modelMain.setItem(i, 2, itemUserInitialDesicionVT);
        fillDataUserTable(user, i);
    }
    userTableMain->resizeRowsToContents();
  // userTableMain->horizontalHeader()->setDefaultAlignment(QtCore.AlignHCenter | Qt.Alignment(QtCore.Qt.TextWordWrap))
    userTableMain->horizontalHeader()->setFixedHeight(100);;
    userTableMain->resizeColumnsToContents();

}


void MainWindow::fillDataUserTable(User user, int ind) {

    foreach (Entry entry, user.realEntriesNT) {
        fillDataUserEntry(entry, ind);
    }

    foreach (Entry entry, user.realEntriesNT) {
        fillDataUserEntry(entry, ind);
    }

    foreach (Entry entry, user.realEntriesVT) {
        fillDataUserEntry(entry, ind);
    }

    foreach (Entry entry, user.realEntriesNT) {
        fillDataUserEntry(entry, ind);
    }
}

void MainWindow::fillDataUserEntry (Entry entry, int ind) {
    int indexRow = 3;
    QString nameDate;
    if (entry.type == TypeEntry::realNT) {
        nameDate = "Sk NT: " + entry.date.toStringWithName();
    }
    if (entry.type == TypeEntry::realVT) {
        nameDate = "Sk VT: " + entry.date.toStringWithName();
    }
    if (entry.type == TypeEntry::invoiceNT) {
        nameDate = "Fa NT: " + entry.date.toStringWithName();
    }
    if (entry.type == TypeEntry::invoiceVT) {
        nameDate = "Fa VT: " + entry.date.toStringWithName();
    }
    QString date = entry.date.toString();

    QStandardItem *itemValue = new QStandardItem(QString::number(entry.value, 'f', 2));
    modelMain.setItem(ind, indexRow + dates.indexOf(nameDate), itemValue);
    double ratio = UserManager::getInstance()->getRatioUserEntry(entry);
    QStandardItem *itemRatio = new QStandardItem(QString::number(ratio, 'f', 3));
    modelMain.setItem(ind, indexRow + dates.indexOf("% " + nameDate), itemRatio);

}






void MainWindow::on_editUserBtn_clicked() {
    EditUsers editUsers;
    editUsers.setModal(true);
    int result = editUsers.exec();
    if(result==QDialog::Accepted) {
        reloadUserTable();
    }
    else {
        reloadUserTable();
    }
}

void MainWindow::on_btnAddEntry_clicked() {
    AddNewEntry addNewEntry;
    addNewEntry.setModal(true);
    int result = addNewEntry.exec();
    if(result==QDialog::Accepted) {
        createUserTable();
    }
    else {
        createUserTable();
    }
}

void MainWindow::on_addInvoice_clicked() {
    choiceDate choiceD;
    choiceD.setModal(true);
    int result = choiceD.exec();
}
