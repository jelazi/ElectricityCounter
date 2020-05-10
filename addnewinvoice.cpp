#include "addnewinvoice.h"
#include "ui_addnewinvoice.h"
#include "QDoubleSpinBox"
#include "usermanager.h"
#include "QMessageBox"
#include "invoicemanager.h"

QLabel *dateLabel;
QVBoxLayout * dataLayout;
QDoubleSpinBox *fixedRateSpinBoxNT;
QDoubleSpinBox *fixedRateSpinBoxVT;
QDoubleSpinBox *flexibleRateSpinBoxNT;
QDoubleSpinBox *flexibleRateSpinBoxVT;

MyDate currentDate = MyDate::getCurrentDate();

AddNewInvoice::AddNewInvoice(QWidget *parent): QDialog(parent), ui(new Ui::AddNewInvoice) {
  ui->setupUi(this);
  dateLabel = ui->dateLabel;
  dateLabel->setText("Faktura pro: " + currentDate.toStringWithName());
  dataLayout = ui->dataLayout;
  addItems();
}

void AddNewInvoice::setDate(MyDate *myDate) {
  currentDate = *myDate;
}

void AddNewInvoice::addItems() {
  QList<User> usersList = UserManager::getInstance()->getUsers();
  QString usersString = "Faktura bude rozdělena mezi: ";
  foreach (User user, usersList) {
      usersString += user.getName();
      if (user.getID() != usersList.last().getID()) {
          usersString += ", ";
        } else {
          usersString += ".";
        }
    }

  QLabel *usersLbl = new QLabel();
  usersLbl->setText(usersString);
  dataLayout->addWidget(usersLbl);


  QHBoxLayout *fixedlayoutNT = new QHBoxLayout();
  QLabel *fixedRateLblNT = new QLabel();
  fixedRateLblNT->setText("Pevná sazba NT");
  fixedlayoutNT->addWidget(fixedRateLblNT);

  fixedRateSpinBoxNT = new QDoubleSpinBox();
  fixedRateSpinBoxNT->setValue(0);
  fixedRateSpinBoxNT->setRange(0, 9999999);
  fixedlayoutNT->addWidget(fixedRateSpinBoxNT);

  dataLayout->addLayout(fixedlayoutNT);


  QHBoxLayout *fixedlayoutVT = new QHBoxLayout();
  QLabel *fixedRateLblVT = new QLabel();
  fixedRateLblVT->setText("Pevná sazba VT");
  fixedlayoutVT->addWidget(fixedRateLblVT);

  fixedRateSpinBoxVT = new QDoubleSpinBox();
  fixedRateSpinBoxVT->setValue(0);
  fixedRateSpinBoxVT->setRange(0, 9999999);
  fixedlayoutVT->addWidget(fixedRateSpinBoxVT);

  dataLayout->addLayout(fixedlayoutVT);


  QHBoxLayout *flexiblelayoutNT = new QHBoxLayout();
  QLabel *flexibleRateLblNT = new QLabel();
  flexibleRateLblNT->setText("Pohyblivá sazba NT");
  flexiblelayoutNT->addWidget(flexibleRateLblNT);

  flexibleRateSpinBoxNT = new QDoubleSpinBox();
  flexibleRateSpinBoxNT->setValue(0);
  flexibleRateSpinBoxNT->setRange(0, 9999999);
  flexiblelayoutNT->addWidget(flexibleRateSpinBoxNT);

  dataLayout->addLayout(flexiblelayoutNT);

  QHBoxLayout *flexiblelayoutVT = new QHBoxLayout();
  QLabel *flexibleRateLblVT = new QLabel();
  flexibleRateLblVT->setText("Pohyblivá sazba VT");
  flexiblelayoutVT->addWidget(flexibleRateLblVT);

  flexibleRateSpinBoxVT = new QDoubleSpinBox();
  flexibleRateSpinBoxVT->setValue(0);
  flexibleRateSpinBoxVT->setRange(0, 9999999);
  flexiblelayoutVT->addWidget(flexibleRateSpinBoxVT);

  dataLayout->addLayout(flexiblelayoutVT);

}



AddNewInvoice::~AddNewInvoice() {
  delete ui;
}



void AddNewInvoice::on_cancelBtn_clicked() {
    close();
}

void AddNewInvoice::on_okBtn_clicked() {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Uložení" + currentDate.toStringWithName());
  msgBox.setText("Chcete tuto fakturu za " + currentDate.toStringWithName() + "uložit?");
  msgBox.addButton(("Storno"), QMessageBox::NoRole);
  QAbstractButton *okButton = msgBox.addButton(("Ok"), QMessageBox::YesRole);
  msgBox.exec();
  if (msgBox.clickedButton() == okButton) {
      Invoice *newInvoice = new Invoice (currentDate);
      newInvoice->fixedRateNT = fixedRateSpinBoxNT->value();
      newInvoice->fixedRateVT = fixedRateSpinBoxVT->value();
      newInvoice->variableRateNT = flexibleRateSpinBoxNT->value();
      newInvoice->variableRateVT = flexibleRateSpinBoxVT->value();
      InvoiceManager::getInstance()->addInvoice(*newInvoice);
    close();
    }

}
