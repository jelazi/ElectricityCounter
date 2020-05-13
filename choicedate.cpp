#include "choicedate.h"
#include "ui_choicedate.h"
#include "mydate.h"
#include "addnewinvoice.h"
#include "invoicemanager.h"
#include <QMessageBox>
#include "viewresult.h"


QComboBox *monthComboBoxChoiceDate;
QComboBox *yearComboBoxChoiceDate;
QPushButton *okButtonChoiceDate;
QPushButton *cancelButtonChoiceDate;
TypeParentChoiceDate typeParent;



QList<QString> yearsChoiceDate;

int selectedMonth;
int selectedYear;


choiceDate::choiceDate(QWidget *parent): QDialog(parent), ui(new Ui::choiceDate) {
  ui->setupUi(this);

  okButtonChoiceDate = ui->okBtn;
  cancelButtonChoiceDate = ui->cancelBtn;
  monthComboBoxChoiceDate = ui->month;
  yearComboBoxChoiceDate = ui->year;
  fillYearsList();
}

choiceDate::~choiceDate() {
  delete ui;
}

void choiceDate::fillYearsList () {
    MyDate now = MyDate::getCurrentDate();
    selectedMonth = now.getMonth();
    selectedYear = now.getYear();
    int nowYear = now.getYear();
    for (int i = nowYear - 1; i < nowYear + 30; i++) {
        yearsChoiceDate.push_back(QString::number(i));
    }
    foreach (QString month, MyDate::getListNameMonths()) {
        monthComboBoxChoiceDate->addItem(month);
    }
    monthComboBoxChoiceDate->setCurrentIndex(now.getMonth() - 1);
    int width = monthComboBoxChoiceDate->minimumSizeHint().width();
    monthComboBoxChoiceDate->setMinimumWidth(width);
    foreach (QString year, yearsChoiceDate) {
        yearComboBoxChoiceDate->addItem(year, QVariant(year.toInt()));
    }
    yearComboBoxChoiceDate->setCurrentIndex(1);
}

void choiceDate::setParentChoiceDate(TypeParentChoiceDate type) {
  typeParent = type;
  if (typeParent == TypeParentChoiceDate::addNewInvoice) {
      this->setWindowTitle("Vyberte datum faktury");
    }
  if (typeParent == TypeParentChoiceDate::viewResult) {
      this->setWindowTitle("Vyberte datum pro výpočet");
    }
}

void choiceDate::on_cancelBtn_clicked() {
    close();
}

void choiceDate::on_okBtn_clicked() {
  MyDate *choice = new MyDate(selectedMonth, selectedYear);
close();
  if (typeParent == TypeParentChoiceDate::addNewInvoice) {
      this->setWindowTitle("Vyberte datum faktury");
      if (InvoiceManager::getInstance()->containsInvoiceByDate(*choice)) {
          QMessageBox msgBox;
          msgBox.setWindowTitle("Chybná data");
          msgBox.setText("Na toto datum je již vystavená faktura");
          msgBox.exec();
        } else {
          AddNewInvoice addNewInvoice;
          addNewInvoice.setModal(true);
          addNewInvoice.setDate(choice);
          QObject::connect(&addNewInvoice, SIGNAL(signalChangeData()), this, SLOT(slotChangeData()));
          addNewInvoice.exec();

        }
    }
  if (typeParent == TypeParentChoiceDate::viewResult) {

      if (InvoiceManager::getInstance()->containsInvoiceByDate((*choice))) {
          ViewResult viewResult;
          viewResult.setModal(true);
          viewResult.setDate(choice);

          viewResult.exec();


        } else {
          QMessageBox msgBox;
          msgBox.setWindowTitle("Nenalezená data");
          msgBox.setText("Na toto datum nebyla ještě vystavena faktura");
          msgBox.exec();
        }
    }
}



void choiceDate::on_month_currentIndexChanged(int index) {
    selectedMonth = index + 1;
}

void choiceDate::on_year_currentIndexChanged(int index) {
    selectedYear = yearsChoiceDate[index].toInt();
}

void choiceDate::slotChangeData() {
    signalChangeData();
}

