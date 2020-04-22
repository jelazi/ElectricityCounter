#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "QString"
#include "QDoubleValidator"
#include <QMessageBox>

QLineEdit *nameLineEdit;
QDoubleSpinBox *numberLineEdit;
QString name;
float number;

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog) {
    ui->setupUi(this);
    nameLineEdit = ui->nameLineEdit;
    numberLineEdit = ui->number;
}

AddUserDialog::~AddUserDialog() {
    delete ui;
}

void AddUserDialog::addManager(UserManager userManagerRef) {
    this->userManager = &userManagerRef;
}


bool AddUserDialog::isCorrectValues() {
    name = nameLineEdit->text();
    if (name.isNull() || name.isEmpty()) return false;
    number = numberLineEdit->value();
    if (number < 0) return false;
    return true;
}

void AddUserDialog::on_okButton_clicked() {
    if (isCorrectValues()) {
        userManager->addUser(name,number);
        qDebug()<<userManager->getUsers()[4].name;
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
