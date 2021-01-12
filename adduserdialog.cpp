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
bool isNew = true;
int userId = 0;


AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog) {
    ui->setupUi(this);
    this->setWindowTitle("Přidání uživatele");
    nameLineEdit = ui->nameLineEdit;
    numberLineEditNT = ui->spinNT;
    numberLineEditVT = ui->spinVT;
    MyDate now = MyDate::getCurrentDate();
    entryNT.date = now;
    entryVT.date = now;
    entryNT.type = TypeEntry::realNT;
    entryVT.type = TypeEntry::realVT;

}

AddUserDialog::~AddUserDialog() {
    delete ui;
}

void AddUserDialog::setUser (User user) {
    isNew = false;
    userId = user.getID();
    name = user.getName();
    entryNT = user.getInitialDesicionNT();
    entryVT = user.getInitialDesicionVT();
    nameLineEdit->setText(name);
    numberLineEditNT->setValue(entryNT.value);
    numberLineEditVT->setValue(entryVT.value);
    this->setWindowTitle("Editace uživatele");
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
        if (isNew) {
            UserManager::getInstance()->addUser(name, entryNT, entryVT);
            this->close();
        } else {
            User *user = new User(userId, name, entryNT, entryVT);
            UserManager::getInstance()->updateUser(*user);
            this->close();
        }

    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Chybná data");
        msgBox.setText("Špatně zadaná data");
        msgBox.exec();
    }
}

void AddUserDialog::on_cancelButton_clicked() {
    this->close();
}


