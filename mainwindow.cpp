#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDate"
#include "QDebug"
#include <QtCore>
#include "editusers.h"
#include "entrywindow.h"

#include "usermanager.h"
#include "choicedate.h"
#include "invoicemanager.h"


QTableView *userTableMain;
QTableView *invoiceTableMain;
QList <QString> dates;
QList <Invoice> invoices;
QList <User> users;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Počítání elektřiny");

    users = UserManager::getInstance()->getUsers();
    invoices = InvoiceManager::getInstance()->getInvoices();
    userTableMain = ui->userTable;
    invoiceTableMain = ui->invoiceTable;
    createTables();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::createTables() {

     userTableMain->setModel(&modelMainUser);
     invoiceTableMain->setModel(&modelMainInvoice);
     reloadUserTable();
     reloadInvoiceTable();
     userTableMain->setSelectionBehavior(QAbstractItemView::SelectRows);
     userTableMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::reloadInvoiceTable() {
    invoices = InvoiceManager::getInstance()->getInvoices();
  modelMainInvoice.clear();
  horizontalHeaderInvoice.clear();
  verticalHeaderInvoice.clear();
  verticalHeaderInvoice.append("fixní částka");
  verticalHeaderInvoice.append("pohyblivá částka NT");
  verticalHeaderInvoice.append("pohyblivá částka VT");
  for (int i = 0; i < invoices.length();i++) {
      Invoice invoice = invoices[i];
      horizontalHeaderInvoice.append(invoice.date.toStringWithName());
      ;
      modelMainInvoice.setItem(0, i, new QStandardItem(QString::number(invoice.fixedRate, 'f', 2) + " Kč"));
      modelMainInvoice.setItem(1, i, new QStandardItem(QString::number(invoice.variableRateNT, 'f', 2) + " Kč"));
      modelMainInvoice.setItem(2, i,new QStandardItem(QString::number(invoice.variableRateVT, 'f', 2) + " Kč"));

    }
  modelMainInvoice.setHorizontalHeaderLabels(horizontalHeaderInvoice);
  modelMainInvoice.setVerticalHeaderLabels(verticalHeaderInvoice);
}


void MainWindow::reloadUserTable() {
    users = UserManager::getInstance()->getUsers();
    modelMainUser.clear();
    horizontalHeaderUser.clear();
    verticalHeaderUser.clear();
    foreach (User user, users) {
        horizontalHeaderUser.append(user.getName());
      }

    modelMainUser.setHorizontalHeaderLabels(horizontalHeaderUser);

    QList<MyDate> allDates = UserManager::getInstance()->getAllDates();

    for(int i = 0; i < allDates.length();i++) {
        MyDate date = allDates[i];
        verticalHeaderUser.append(date.toStringWithName());
        for(int j = 0; j<users.length(); j++) {
            if (users[j].containsEntry(date)) {

                QImage image("32px-Symbol_OK.svg.png");
                QImage img = image.scaled(15, 15,Qt::KeepAspectRatio);
                QStandardItem *item = new QStandardItem();
                item->setData(QVariant(QPixmap::fromImage(img)), Qt::DecorationRole);
                item->setTextAlignment(Qt::AlignCenter);
                modelMainUser.setItem(i, j, item);

              }
          }
      }

    modelMainUser.setVerticalHeaderLabels(verticalHeaderUser);


    userTableMain->resizeRowsToContents();
    userTableMain->horizontalHeader()->setFixedHeight(100);;
    userTableMain->resizeColumnsToContents();


}


void MainWindow::fillDataUserTable(User user, int ind) {

    foreach (Entry entry, user.getRealEntriesNT()) {
        fillDataUserEntry(entry, ind);
    }

    foreach (Entry entry, user.getRealEntriesNT()) {
        fillDataUserEntry(entry, ind);
    }

    foreach (Entry entry, user.getRealEntriesVT()) {
        fillDataUserEntry(entry, ind);
    }

    foreach (Entry entry, user.getRealEntriesNT()) {
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

    QString date = entry.date.toString();

    QStandardItem *itemValue = new QStandardItem(QString::number(entry.value, 'f', 2));
    modelMainUser.setItem(ind, indexRow + dates.indexOf(nameDate), itemValue);
    double ratio = UserManager::getInstance()->getRatioUserEntry(entry);
    QStandardItem *itemRatio = new QStandardItem(QString::number(ratio, 'f', 3));
    modelMainUser.setItem(ind, indexRow + dates.indexOf("% " + nameDate), itemRatio);

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
    choiceDate choiceD;
    choiceD.setModal(true);
    choiceD.setParentChoiceDate(TypeParentChoiceDate::addNewEntry);
    QObject::connect(&choiceD, SIGNAL(signalChangeData()), this, SLOT (slotChangeData()));
    choiceD.exec();

}

void MainWindow::on_addInvoice_clicked() {
    choiceDate choiceD;
    choiceD.setModal(true);
    choiceD.setParentChoiceDate(TypeParentChoiceDate::addNewInvoice);
    QObject::connect(&choiceD, SIGNAL(signalChangeData()), this, SLOT (slotChangeData()));
    choiceD.exec();
    }

void MainWindow::on_viewResultBtn_clicked() {
  choiceDate choiceD;
  choiceD.setModal(true);
  choiceD.setParentChoiceDate(TypeParentChoiceDate::viewResult);
  choiceD.exec();
}

void MainWindow::slotChangeData() {
    reloadUserTable();
    reloadInvoiceTable();
}
