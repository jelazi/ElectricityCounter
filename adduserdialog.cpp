#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "QString"
#include "QDoubleValidator"
#include <QMessageBox>
#include "structures.h"

QLineEdit *nameLineEdit;
QDoubleSpinBox *numberLineEditNT;
QDoubleSpinBox *numberLineEditVT;
QString name;
Entry entryNT;
Entry entryVT;


AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog) {
    ui->setupUi(this);
    nameLineEdit = ui->nameLineEdit;
    numberLineEditNT = ui->spinNT;
    numberLineEditVT = ui->spinVT;
    MyDate now = MyDate::getNowDate();
    entryNT.date = now;
    entryVT.date = now;
    entryNT.type = TypeEntry::realNT;
    entryVT.type = TypeEntry::realVT;
}

AddUserDialog::~AddUserDialog() {
    delete ui;
}


bool AddUserDialog::isCorrectValues() {

    name = nameLineEdit->text();
    if (name.isNull() || name.isEmpty()) return false;
    entryNT.value = numberLineEditNT->value();
    entryVT.value = numberLineEditVT->value();
    if (entryNT.value < 0 || entryVT.value < 0) return false;
    return true;
}

void AddUserDialog::on_okButton_clicked() {
    if (isCorrectValues()) {
        UserManager::getInstance()->addUser(name, entryNT, entryVT);

        this->close();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Špatně zadaná data");
        msgBox.exec();
    }
}

void AddUserDialog::on_cancelButton_clicked() {
    this->close();
}


