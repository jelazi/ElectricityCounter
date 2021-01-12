#include "invoicewindow.h"
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
QPushButton *deleteButton;

MyDate currentDate = MyDate::getCurrentDate();

InvoiceWindow::InvoiceWindow(QWidget *parent): QDialog(parent), ui(new Ui::AddNewInvoice) {
  ui->setupUi(this);
  dateLabel = ui->dateLabel;
  dateLabel->setText("Faktura pro: " + currentDate.toStringWithName());
  dataLayout = ui->dataLayout;
  deleteButton = ui->pushButton;
  addItems();
}

void InvoiceWindow::setDate(MyDate *myDate) {
  currentDate = *myDate;
}

void InvoiceWindow::addItems() {
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

void InvoiceWindow::loadEditableData() {
    Invoice *invoice = InvoiceManager::getInstance()->getInvoiceByDate(currentDate);
    fixedRateSpinBox->setValue(invoice->fixedRate);
    flexibleRateSpinBoxNT->setValue(invoice->variableRateNT);
    flexibleRateSpinBoxVT->setValue(invoice->variableRateVT);

}

void InvoiceWindow::setIsEditInvoice(bool value)
{
    isEditInvoice = value;
    deleteButton->setVisible(isEditInvoice);
    if (isEditInvoice) {
        loadEditableData();
    }
}



InvoiceWindow::~InvoiceWindow() {
    delete ui;
}



void InvoiceWindow::on_cancelBtn_clicked() {
    close();
}

void InvoiceWindow::on_okBtn_clicked() {
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
      if (isEditInvoice) {
          InvoiceManager::getInstance()->editInvoice(*newInvoice);
      } else {
          InvoiceManager::getInstance()->addInvoice(*newInvoice);
      }

    close();
    signalChangeData();
    }
}

void InvoiceWindow::on_pushButton_clicked() {
    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Vymazání faktury", "Opravdu chcete fakturu vymazat?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (msgBox == QMessageBox::Yes) {
        Invoice *newInvoice = new Invoice (currentDate);
        newInvoice->fixedRate = fixedRateSpinBox->value();
        newInvoice->variableRateNT = flexibleRateSpinBoxNT->value();
        newInvoice->variableRateVT = flexibleRateSpinBoxVT->value();
        InvoiceManager::getInstance()->deleteInvoice(*newInvoice);
      }
    close();
    signalChangeData();
}
