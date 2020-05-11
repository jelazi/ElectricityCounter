#include "viewresult.h"
#include "ui_viewresult.h"
#include "pdfcreator.h"


MyDate *resultDate = new MyDate();
QTableView *entriesTable;
QTableView *invoiceTable;
Invoice *invoice;
QList<User> usersList;




ViewResult::ViewResult(QWidget *parent): QDialog(parent), ui(new Ui::ViewResult) {
  ui->setupUi(this);
  entriesTable = ui->entriesTable;
  invoiceTable = ui->invoiceTable;
  entriesTable->setModel(&modelEntries);
  invoiceTable->setModel(&modelInvoice);

}

void ViewResult::reloadInvoiceTable() {
  modelInvoice.clear();
  horizontalHeaderInvoice.clear();
  horizontalHeaderInvoice.append("NT fixní částka");
  horizontalHeaderInvoice.append("VT fixní částka");
  horizontalHeaderInvoice.append("NT poměrová částka");
  horizontalHeaderInvoice.append("VT poměrová částka");
  modelInvoice.setHorizontalHeaderLabels(horizontalHeaderInvoice);
  modelInvoice.setVerticalHeaderLabels(verticalHeaderInvoice);

  QStandardItem *itemFixedRateNT = new QStandardItem(QString::number(invoice->fixedRateNT));
  modelInvoice.setItem(0, 0, itemFixedRateNT);

  QStandardItem *itemFixedRateVT = new QStandardItem(QString::number(invoice->fixedRateVT));
  modelInvoice.setItem(0, 1, itemFixedRateVT);

  QStandardItem *itemVariableRateNT = new QStandardItem(QString::number(invoice->variableRateNT));
  modelInvoice.setItem(0, 2, itemVariableRateNT);

  QStandardItem *itemVariableRateVT = new QStandardItem(QString::number(invoice->variableRateVT));
  modelInvoice.setItem(0, 3, itemVariableRateVT);

  invoiceTable->resizeRowsToContents();
  invoiceTable->resizeColumnsToContents();
}

void ViewResult::reloadEntriesTable() {
  modelEntries.clear();
  horizontalHeaderEntries.clear();
  horizontalHeaderEntries.append("Jméno");
  horizontalHeaderEntries.append("NT naměřené");
  horizontalHeaderEntries.append("poměr NT");
  horizontalHeaderEntries.append("NT fa. dle poměru");
  horizontalHeaderEntries.append("NT pevná část");
  horizontalHeaderEntries.append("VT naměřené");
  horizontalHeaderEntries.append("poměr VT");
  horizontalHeaderEntries.append("VT fa. dle poměru");
  horizontalHeaderEntries.append("VT pevná část");
  horizontalHeaderEntries.append("Celkem zaplatí");
  modelEntries.setHorizontalHeaderLabels(horizontalHeaderEntries);
  modelEntries.setVerticalHeaderLabels(verticalHeaderEntries);
  for(int i = 0; i < usersList.length();i++) {
      User user = usersList[i];
      QStandardItem *itemUserName = new QStandardItem(QString(user.name));
      modelEntries.setItem(i, 0, itemUserName);
      modelEntries.item(i,0)->setData(QBrush(Qt::yellow), Qt::BackgroundRole);


      QStandardItem *itemNTValue = new QStandardItem(QString::number(UserManager::getInstance()->getEntryValue(user, *resultDate, TypeEntry::realNT)));
      modelEntries.setItem(i, 1, itemNTValue);

      double ratioNT = UserManager::getInstance()->getRatioUserEntry(user.getEntryByDate(*resultDate, TypeEntry::realNT));

      QStandardItem *itemNTRatio = new QStandardItem(QString::number(ratioNT, 'f', 3));
      modelEntries.setItem(i, 2, itemNTRatio);

      double invoiceValueNT = invoice->variableRateNT * ratioNT;
      QStandardItem *itemNTInvoiceValue = new QStandardItem(QString::number(invoiceValueNT, 'f', 2));
      modelEntries.setItem(i, 3, itemNTInvoiceValue);

      double invoiceValueNTFixed = invoice->fixedRateNT / usersList.length();
      QStandardItem *itemNTInvoiceValueFixed = new QStandardItem(QString::number(invoiceValueNTFixed, 'f', 2));
      modelEntries.setItem(i, 4, itemNTInvoiceValueFixed);





      QStandardItem *itemVTValue = new QStandardItem(QString::number(UserManager::getInstance()->getEntryValue(user, *resultDate, TypeEntry::realVT)));
      modelEntries.setItem(i, 5, itemVTValue);

double ratioVT = UserManager::getInstance()->getRatioUserEntry(user.getEntryByDate(*resultDate, TypeEntry::realVT));

      QStandardItem *itemVTRatio = new QStandardItem(QString::number(ratioVT, 'f', 3));
      modelEntries.setItem(i, 6, itemVTRatio);

      double invoiceValueVT = invoice->variableRateVT * ratioVT;
      QStandardItem *itemVTInvoiceValue = new QStandardItem(QString::number(invoiceValueVT, 'f', 2));
      modelEntries.setItem(i, 7, itemVTInvoiceValue);

      double invoiceValueVTFixed = invoice->fixedRateVT / usersList.length();
      QStandardItem *itemVTInvoiceValueFixed = new QStandardItem(QString::number(invoiceValueVTFixed, 'f', 2));
      modelEntries.setItem(i, 8, itemVTInvoiceValueFixed);


      double sum = invoiceValueNT + invoiceValueVT + invoiceValueNTFixed + invoiceValueVTFixed;
      QStandardItem *itemSum = new QStandardItem(QString::number(sum, 'f', 2));
            modelEntries.setItem(i, 9, itemSum);


entriesTable->resizeRowsToContents();
entriesTable->resizeColumnsToContents();
    }
}

ViewResult::~ViewResult() {
  delete ui;
}

void ViewResult::setDate(MyDate *myDate) {
  resultDate = myDate;
  invoice = InvoiceManager::getInstance()->getInvoiceByDate(*resultDate);
  usersList = UserManager::getInstance()->getUsers();

  this->setWindowTitle("Výsledky pro " + resultDate->toStringWithName());
  reloadEntriesTable();
  reloadInvoiceTable();
  entriesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  entriesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  invoiceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  invoiceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}



void ViewResult::on_btnCancel_clicked() {
    close();
}

void ViewResult::on_btnCreatePdf_clicked() {
  PDFCreator pdfCreator;
  QString fileName = QFileDialog::getSaveFileName(this, "Uložit soubor", resultDate->toStringWithName(), ".pdf");
 pdfCreator.createPDF(entriesTable, fileName + ".pdf", resultDate->toStringWithName());
}

void ViewResult::on_btnSendMail_clicked() {
    close();
}
