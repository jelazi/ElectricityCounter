#include "addnewinvoice.h"
#include "ui_addnewinvoice.h"
#include "QDoubleSpinBox"
#include "usermanager.h"
#include "QMessageBox"
#include "invoicemanager.h"

QLabel *dateLabel;
QVBoxLayout * dataLayout;
QDoubleSpinBox *fixedRateSpinBox;
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

  QLabel *coinLblFlex = new QLabel();
  coinLblFlex->setText("Kč");
  QLabel *coinLblVarVT = new QLabel();
  coinLblVarVT->setText("Kč");
  QLabel *coinLblVarNT = new QLabel();
  coinLblVarNT->setText("Kč");



  QHBoxLayout *fixedlayoutNT = new QHBoxLayout();
  QLabel *fixedRateLblNT = new QLabel();
  fixedRateLblNT->setText("Pevná sazba");
  fixedlayoutNT->addWidget(fixedRateLblNT);

  fixedRateSpinBox = new QDoubleSpinBox();
  fixedRateSpinBox->setValue(0);
  fixedRateSpinBox->setRange(0, 9999999);


  fixedlayoutNT->addWidget(fixedRateSpinBox);
fixedlayoutNT->addWidget(coinLblFlex);
  dataLayout->addLayout(fixedlayoutNT);



  QHBoxLayout *flexiblelayoutNT = new QHBoxLayout();
  QLabel *flexibleRateLblNT = new QLabel();
  flexibleRateLblNT->setText("Pohyblivá sazba NT");
  flexiblelayoutNT->addWidget(flexibleRateLblNT);

  flexibleRateSpinBoxNT = new QDoubleSpinBox();
  flexibleRateSpinBoxNT->setValue(0);
  flexibleRateSpinBoxNT->setRange(0, 9999999);
  flexiblelayoutNT->addWidget(flexibleRateSpinBoxNT);

  flexiblelayoutNT->addWidget(coinLblVarNT);

  dataLayout->addLayout(flexiblelayoutNT);

  QHBoxLayout *flexiblelayoutVT = new QHBoxLayout();
  QLabel *flexibleRateLblVT = new QLabel();
  flexibleRateLblVT->setText("Pohyblivá sazba VT");
  flexiblelayoutVT->addWidget(flexibleRateLblVT);

  flexibleRateSpinBoxVT = new QDoubleSpinBox();
  flexibleRateSpinBoxVT->setValue(0);
  flexibleRateSpinBoxVT->setRange(0, 9999999);

  flexiblelayoutVT->addWidget(flexibleRateSpinBoxVT);

  flexiblelayoutVT->addWidget(coinLblVarVT);

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
      newInvoice->fixedRate = fixedRateSpinBox->value();
      newInvoice->variableRateNT = flexibleRateSpinBoxNT->value();
      newInvoice->variableRateVT = flexibleRateSpinBoxVT->value();
      InvoiceManager::getInstance()->addInvoice(*newInvoice);
    close();
    signalChangeData();
    }



}
