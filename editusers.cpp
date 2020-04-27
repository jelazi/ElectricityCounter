#include "editusers.h"
#include "ui_editusers.h"
#include "user.h"
#include "usermanager.h"
#include "jsonparser.h"
#include <QMessageBox>

QPushButton *okButton;
QPushButton *cancelButton;
QPushButton *addUser;
QTableView *userTable;


EditUsers::EditUsers(QWidget *parent): QDialog(parent), ui(new Ui::EditUsers) {
    ui->setupUi(this);
    this->setWindowTitle("Uživatelé");
    okButton = ui->okButton;
    cancelButton = ui->cancelButton;
    addUser = ui->addUserButton;
    userTable = ui->userTable;

    createUserTable();
    QString userJson = JsonParser::createJsonUserFile(UserManager::getInstance()->getUsers());
   // qDebug()<<userJson;
    QList<User> users = JsonParser::getUsersFromJson(userJson);
    foreach (User user, users) {
  //      qDebug() <<user.name;
    }
}




EditUsers::~EditUsers() {
    delete ui;
}

void EditUsers::createUserTable() {

    horizontalHeader.append("ID");
    horizontalHeader.append("Jméno");
    horizontalHeader.append("Počátek NT");
    horizontalHeader.append("Datum NT");
    horizontalHeader.append("Počátek VT");
    horizontalHeader.append("Datum VT");

    userTable->setModel(&model);
    reloadUserTable();
    userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

}



void EditUsers::reloadUserTable() {
    QList<User> usersList = UserManager::getInstance()->getUsers();
    model.clear();


    model.setHorizontalHeaderLabels(horizontalHeader);
    model.setVerticalHeaderLabels(verticalHeader);


    for(int i = 0; i < usersList.length();i++) {
        QStandardItem *itemUserID= new QStandardItem(QString::number(usersList[i].getID()));
        model.setItem(i, 0, itemUserID);

        QStandardItem *itemUserName = new QStandardItem(QString(usersList[i].name));
        model.setItem(i, 1, itemUserName);

        QStandardItem *itemUserInitialDesicionNT = new QStandardItem(QString::number(usersList[i].initialDesicionNT.value, 'f', 2));
        model.setItem(i, 2, itemUserInitialDesicionNT);


        QStandardItem *itemUserInitialDesicionNTDate = new QStandardItem(usersList[i].initialDesicionNT.date.toString());
        model.setItem(i, 3, itemUserInitialDesicionNTDate);


        QStandardItem *itemUserInitialDesicionVT = new QStandardItem(QString::number(usersList[i].initialDesicionVT.value, 'f', 2));
        model.setItem(i, 4, itemUserInitialDesicionVT);

        QStandardItem *itemUserInitialDesicionVTDate = new QStandardItem(usersList[i].initialDesicionVT.date.toString());
        model.setItem(i, 5, itemUserInitialDesicionVTDate);
    }
      userTable->resizeRowsToContents();
      userTable->resizeColumnsToContents();
}

int EditUsers::countDigits(double num) {
     int temp = num;
     int count = 0;
     while(temp != 0) {
             count++;
             temp /= 10;
         }
     return count;
}



void EditUsers::on_cancelButton_clicked() {
    this->close();
}

void EditUsers::on_okButton_clicked() {
    UserManager::getInstance()->saveCurrentUsersToJson();
    this->close();
}

void EditUsers::on_addUserButton_clicked() {
    AddUserDialog adduserDialog;
    adduserDialog.setModal(true);
    int result = adduserDialog.exec();

    if(result==QDialog::Accepted) {
        reloadUserTable();
    }
    else {
        reloadUserTable();
    }
}

void EditUsers::on_userTable_doubleClicked(const QModelIndex &index) {
    int row = index.row();
    User selectedUser = UserManager::getInstance()->getUsers()[row];

    QMessageBox reply;
    reply.setWindowTitle("Editace uživatele");
    reply.setText("Co chcete s uživatelem: " + selectedUser.name + " udělat?");
     QAbstractButton *myYesButton = reply.addButton(("Editovat"), QMessageBox::YesRole);
     QAbstractButton *myNoButton = reply.addButton(("Vymazat"), QMessageBox::YesRole);
     reply.addButton(("Storno"), QMessageBox::NoRole);
    reply.exec();
     if (reply.clickedButton() == myYesButton) {
         AddUserDialog adduserDialog;
         adduserDialog.setModal(true);

         adduserDialog.setUser(selectedUser);
         int result = adduserDialog.exec();


         if(result==QDialog::Accepted) {
             reloadUserTable();
         }
         else {
             reloadUserTable();
         }
     }
     if (reply.clickedButton() == myNoButton) {
         UserManager::getInstance()->removeUser(selectedUser.getID());
         reloadUserTable();
     }
}
