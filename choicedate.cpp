#include "choicedate.h"
#include "ui_choicedate.h"
#include "mydate.h"
#include "invoicewindow.h"
#include "invoicemanager.h"
#include <QMessageBox>
#include "viewresult.h"
#include "entrywindow.h"


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
    for (int i = nowYear - 10; i < nowYear + 30; i++) {
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
    yearComboBoxChoiceDate->setCurrentIndex(10);
}

void choiceDate::setUsers(const QList<User> &value)
{
    users = value;
}

void choiceDate::setParentChoiceDate(TypeParentChoiceDate type) {
    typeParent = type;
  if (typeParent == TypeParentChoiceDate::addNewInvoice) {
      this->setWindowTitle("Vyberte datum faktury");
    }
  if (typeParent == TypeParentChoiceDate::viewResult) {
      this->setWindowTitle("Vyberte datum pro výpočet");
    }
  if (typeParent == TypeParentChoiceDate::addNewEntry) {
      this->setWindowTitle("Vyberte datum měření");
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
          QMessageBox::StandardButton msgBox;
          msgBox = QMessageBox::question(this, "Možná editace", "Na toto datum je již vystavená faktura. Chcete fakturu editovat?",
                                          QMessageBox::Yes|QMessageBox::No);
          if (msgBox == QMessageBox::Yes) {
              qDebug() << "Yes was clicked";
              InvoiceWindow addNewInvoice;
              addNewInvoice.setModal(true);
              addNewInvoice.setDate(choice);
              addNewInvoice.setIsEditInvoice(true);
              QObject::connect(&addNewInvoice, SIGNAL(signalChangeData()), this, SLOT(slotChangeData()));
              addNewInvoice.exec();

            }
        } else {
          InvoiceWindow addNewInvoice;
          addNewInvoice.setModal(true);
          addNewInvoice.setDate(choice);
          addNewInvoice.setIsEditInvoice(false);
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

  if (typeParent == TypeParentChoiceDate::addNewEntry) {
      QList<QString>nameUserUsesEntries = QList<QString>();
      for(int i = 0; i < users.length(); i++) {
          if (users[i].containsEntry(*choice)) {
              nameUserUsesEntries.append(users[i].getName());
          }
      }
      EntryWindow addNewEntry;
      addNewEntry.setModal(true);
      if (nameUserUsesEntries.isEmpty()) {
      } else {
          QMessageBox::StandardButton msgBox;
          QString messageString = "Na toto datum jsou již vložena měření pro tyto jména: ";
          for (int i = 0; i < nameUserUsesEntries.length(); i++) {
              messageString += nameUserUsesEntries[i];
              if (i != nameUserUsesEntries.length() - 1) {
                  messageString +=", ";
              } else {
                  messageString +=".";
              }
          }
          messageString += " Chcete tyto měření editovat?";

          msgBox = QMessageBox::question(this, "Možná editace", messageString, QMessageBox::Yes|QMessageBox::No);
          if (msgBox == QMessageBox::Yes) {
            } else {
              return;
          }
      }
      addNewEntry.fillDateLabel(choice);
      QObject::connect(&addNewEntry, SIGNAL(signalChangeData()), this, SLOT (slotChangeData()));
      addNewEntry.setIsEditable(!nameUserUsesEntries.isEmpty());
      addNewEntry.exec();

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

