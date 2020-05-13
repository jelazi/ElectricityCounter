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
  horizontalHeaderInvoice.append("pevná částka");
  horizontalHeaderInvoice.append("NT poměrová částka");
  horizontalHeaderInvoice.append("VT poměrová částka");
  modelInvoice.setHorizontalHeaderLabels(horizontalHeaderInvoice);
  modelInvoice.setVerticalHeaderLabels(verticalHeaderInvoice);

  QStandardItem *itemFixedRate = new QStandardItem(QString::number(invoice->fixedRate) + " Kč");
  modelInvoice.setItem(0, 0, itemFixedRate);

  QStandardItem *itemVariableRateNT = new QStandardItem(QString::number(invoice->variableRateNT) + " Kč");
  modelInvoice.setItem(0, 1, itemVariableRateNT);

  QStandardItem *itemVariableRateVT = new QStandardItem(QString::number(invoice->variableRateVT) + " Kč");
  modelInvoice.setItem(0, 2, itemVariableRateVT);

  invoiceTable->resizeRowsToContents();
  invoiceTable->resizeColumnsToContents();
}

void ViewResult::reloadEntriesTable() {
  modelEntries.clear();
  horizontalHeaderEntries.clear();
  horizontalHeaderEntries.append("Jméno");
  horizontalHeaderEntries.append("NT naměřené");
  horizontalHeaderEntries.append("procento NT");
  horizontalHeaderEntries.append("NT fa. dle poměru");
  horizontalHeaderEntries.append("VT naměřené");
  horizontalHeaderEntries.append("procento VT");
  horizontalHeaderEntries.append("VT fa. dle poměru");
  horizontalHeaderEntries.append("pevná část");
  horizontalHeaderEntries.append("Celkem zaplatí");
  horizontalHeaderEntries.append("Poměr VT a NT");
  modelEntries.setHorizontalHeaderLabels(horizontalHeaderEntries);
  modelEntries.setVerticalHeaderLabels(verticalHeaderEntries);

  double sumNTValue = 0;
  double sumVTValue = 0;
  double sumNTRatio = 0;
  double sumVTRatio = 0;
  double sumNTInvoice = 0;
  double sumVTInvoice = 0;
  double sumFixed = 0;
  double sumSum = 0;


  for(int i = 0; i < usersList.length();i++) {
      User user = usersList[i];
      QStandardItem *itemUserName = new QStandardItem(QString(user.name));
      modelEntries.setItem(i, 0, itemUserName);



      QStandardItem *itemNTValue = new QStandardItem(QString::number(UserManager::getInstance()->getEntryValue(user, *resultDate, TypeEntry::realNT))+ " kWh");
      modelEntries.setItem(i, 1, itemNTValue);


      double ratioNT = UserManager::getInstance()->getRatioUserEntry(user.getEntryByDate(*resultDate, TypeEntry::realNT));
      sumNTRatio +=ratioNT;

      QStandardItem *itemNTRatio = new QStandardItem(QString::number(ratioNT * 100, 'f', 1) + " %");
      modelEntries.setItem(i, 2, itemNTRatio);

      double invoiceValueNT = invoice->variableRateNT * ratioNT;
      sumNTInvoice +=invoiceValueNT;
      QStandardItem *itemNTInvoiceValue = new QStandardItem(QString::number(invoiceValueNT, 'f', 2) + " Kč");
      modelEntries.setItem(i, 3, itemNTInvoiceValue);



      QStandardItem *itemVTValue = new QStandardItem(QString::number(UserManager::getInstance()->getEntryValue(user, *resultDate, TypeEntry::realVT))+ " kWh");
      modelEntries.setItem(i, 4, itemVTValue);

double ratioVT = UserManager::getInstance()->getRatioUserEntry(user.getEntryByDate(*resultDate, TypeEntry::realVT));
        sumVTRatio +=ratioVT;
      QStandardItem *itemVTRatio = new QStandardItem(QString::number(ratioVT * 100, 'f', 1) + " %");
      modelEntries.setItem(i, 5, itemVTRatio);

      double invoiceValueVT = invoice->variableRateVT * ratioVT;
      sumVTInvoice +=invoiceValueVT;
      QStandardItem *itemVTInvoiceValue = new QStandardItem(QString::number(invoiceValueVT, 'f', 2) + " Kč");
      modelEntries.setItem(i, 6, itemVTInvoiceValue);

      double invoiceValueFixed = invoice->fixedRate / usersList.length();
      sumFixed += invoiceValueFixed;
      QStandardItem *itemInvoiceValueFixed = new QStandardItem(QString::number(invoiceValueFixed, 'f', 2) + " Kč");
      modelEntries.setItem(i, 7, itemInvoiceValueFixed);


      double sum = invoiceValueNT + invoiceValueVT +  invoiceValueFixed;
      sumSum += sum;
      QStandardItem *itemSum = new QStandardItem(QString::number(sum, 'f', 2) + " Kč");
      modelEntries.setItem(i, 8, itemSum);

      double nt = (UserManager::getInstance()->getEntryValue(user, *resultDate, TypeEntry::realNT));
      sumNTValue += nt;
      double vt = (UserManager::getInstance()->getEntryValue(user, *resultDate, TypeEntry::realVT));
      sumVTValue += vt;

      double percent = ((nt + vt) / 100);
      double ratioNTVT = 0;
      double ratioVTNT = 0;
      if (percent != 0) {
          ratioNTVT = nt / percent;
          ratioVTNT = vt / percent;
      }


      QStandardItem *itemRatioNTVT = new QStandardItem(QString::number(ratioVTNT, 'f', 0) + "% / " + QString::number(ratioNTVT, 'f', 0) + "%");
      modelEntries.setItem(i, 9, itemRatioNTVT);

modelEntries.item(i,0)->setData(QBrush((QColor(242, 245, 16))), Qt::BackgroundRole);
modelEntries.item(i,8)->setData(QBrush((QColor(151, 245, 16))), Qt::BackgroundRole);



entriesTable->resizeRowsToContents();
entriesTable->resizeColumnsToContents();
    }

  int lastRow = usersList.length();

  QStandardItem *lbl = new QStandardItem("Součty");
  modelEntries.setItem(lastRow, 0, lbl);

  QStandardItem *sumNTValueItem = new QStandardItem(QString::number(sumNTValue, 'f', 2) + " kWh");
  modelEntries.setItem(lastRow, 1, sumNTValueItem);
  QStandardItem *sumVTValueItem = new QStandardItem(QString::number(sumVTValue, 'f', 2) + " kWh");
  modelEntries.setItem(lastRow, 4, sumVTValueItem);
  QStandardItem *sumNTRatioItem = new QStandardItem(QString::number(sumNTRatio * 100, 'f', 1) + " %");
  modelEntries.setItem(lastRow, 2, sumNTRatioItem);
  QStandardItem *sumVTRatioItem = new QStandardItem(QString::number(sumVTRatio * 100, 'f', 1) + " %");
  modelEntries.setItem(lastRow, 5, sumVTRatioItem);
  QStandardItem *sumNTInvoiceItem = new QStandardItem(QString::number(sumNTInvoice, 'f', 2) + " Kč");
  modelEntries.setItem(lastRow, 3, sumNTInvoiceItem);
  QStandardItem *sumVTInvoiceItem = new QStandardItem(QString::number(sumVTInvoice, 'f', 2) + " Kč");
  modelEntries.setItem(lastRow, 6, sumVTInvoiceItem);
  QStandardItem *sumFixedItem = new QStandardItem(QString::number(sumFixed, 'f', 2) + " Kč");
  modelEntries.setItem(lastRow, 7, sumFixedItem);
  QStandardItem *sumSumItem = new QStandardItem(QString::number(sumSum, 'f', 2) + " Kč");
  modelEntries.setItem(lastRow, 8, sumSumItem);

  for (int i = 1; i<9;i++) {
      modelEntries.item(lastRow,i)->setData(QBrush((QColor(39, 226, 232))), Qt::BackgroundRole);
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
  pdfCreator.addPath(fileName + ".pdf");
  pdfCreator.addTitle(resultDate->toStringWithName());
  pdfCreator.addTable(entriesTable, "Měření");
  pdfCreator.addTable(invoiceTable, "Faktura");
  pdfCreator.createPDF();
}

void ViewResult::on_btnSendMail_clicked() {
 /*   // This is a first demo application of the SmtpClient for Qt project

        // First we need to create an SmtpClient object
        // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser("lzizka@gmail.com");
        smtp.setPassword("honzicek1");

        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;

        message.setSender(new EmailAddress("lzizka@gmail.com", "Lubomír Žižka"));
        message.addRecipient(new EmailAddress("lzizka@gmail.com", "Recipient's Name"));
        message.setSubject("SmtpClient for Qt - Demo");

        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText("Hi,\nThis is a simple email message.\n");

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        smtp.connectToHost();
        smtp.login();
        smtp.sendMail(message);
        smtp.quit();*/
    close();
}
