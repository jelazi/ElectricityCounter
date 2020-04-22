#include "editusers.h"
#include "ui_editusers.h"
#include "user.h"
#include "usermanager.h"

QPushButton *okButton;
QPushButton *cancelButton;
QPushButton *addUser;
QTableView *userTable;
UserManager *userManager;


EditUsers::EditUsers(QWidget *parent): QDialog(parent), ui(new Ui::EditUsers) {
    ui->setupUi(this);
    this->setWindowTitle("Uživatelé");
    okButton = ui->okButton;
    cancelButton = ui->cancelButton;
    addUser = ui->addUserButton;
    userTable = ui->userTable;

    userManager = new UserManager();
    createUserTable();
}



EditUsers::~EditUsers() {
    delete ui;
}

void EditUsers::createUserTable() {
    horizontalHeader.append("ID");
    horizontalHeader.append("Jméno");
    horizontalHeader.append("Počáteční stav");

    model.index(0,0,model.index(0,0));
    model.setHorizontalHeaderLabels(horizontalHeader);
    model.setVerticalHeaderLabels(verticalHeader);

    userTable->setModel(&model);
    reloadUserTable();
}



void EditUsers::reloadUserTable() {


    QList<User> usersList = userManager->getUsers();
    for(int i = 0; i < usersList.length();i++) {
        QStandardItem *itemUserID= new QStandardItem(QString::number(usersList[i].id));
        model.setItem(i, 0, itemUserID);
        QStandardItem *itemUserName = new QStandardItem(QString(usersList[i].name));
        model.setItem(i, 1, itemUserName);
        QStandardItem *itemUserInitialDesicion = new QStandardItem(QString::number(usersList[i].initialDesicion));
        model.setItem(i, 2, itemUserInitialDesicion);
    }



      userTable->resizeRowsToContents();
      userTable->resizeColumnsToContents();
}



void EditUsers::on_cancelButton_clicked() {
    this->close();
}

void EditUsers::on_okButton_clicked() {
    this->close();
}

void EditUsers::on_addUserButton_clicked() {
    userManager->addUser("blablabla", 0.15);
    reloadUserTable();
}
