#include "viewresult.h"
#include "ui_viewresult.h"


MyDate *resultDate = new MyDate();
QTableView *entriesTable;
QTableView *invoiceTable;




ViewResult::ViewResult(QWidget *parent): QDialog(parent), ui(new Ui::ViewResult) {
  ui->setupUi(this);
  entriesTable = ui->entriesTable;
  invoiceTable = ui->invoiceTable;
  entriesTable->setModel(&modelEntries);
  invoiceTable->setModel(&modelInvoice);
  reloadEntriesTable();
  reloadInvoiceTable();
  entriesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  entriesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  invoiceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  invoiceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ViewResult::reloadInvoiceTable() {
  modelInvoice.clear();
}

void ViewResult::reloadEntriesTable() {
  modelEntries.clear();
  horizontalHeaderEntries.clear();
  horizontalHeaderEntries.append("Jméno");
  horizontalHeaderEntries.append("NT");
  horizontalHeaderEntries.append("VT");
  modelEntries.setHorizontalHeaderLabels(horizontalHeaderEntries);
  modelEntries.setVerticalHeaderLabels(verticalHeaderEntries);
}

ViewResult::~ViewResult() {
  delete ui;
}

void ViewResult::setDate(MyDate *myDate) {
  resultDate = myDate;
  this->setWindowTitle("Výsledky pro " + resultDate->toStringWithName());
}



void ViewResult::on_btnCancel_clicked() {
    close();
}

void ViewResult::on_btnCreatePdf_clicked() {
    close();
}

void ViewResult::on_btnSendMail_clicked() {
    close();
}
