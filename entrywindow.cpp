#include "entrywindow.h"
#include "ui_addnewentry.h"
#include "usermanager.h"
#include "QDoubleSpinBox"


QPushButton *okButtonAddEntry;
QPushButton *cancelButtonAddEntry;
QVBoxLayout *usersLayout;

Entry NT;
Entry VT;
User *errorUser = new User(1, "", NT, VT);
QLabel *dateLabelEntry;
MyDate *selectedDate;




EntryWindow::EntryWindow(QWidget *parent): QDialog(parent), ui(new Ui::AddNewEntry) {
    entries.clear();
    ui->setupUi(this);
    this->setWindowTitle("Přidání měření");
    okButtonAddEntry = ui->okButton;
    cancelButtonAddEntry = ui->cancelButton;
    usersLayout = ui->userLayout;
    dateLabelEntry = ui->label;
    fillUsers();

}

void EntryWindow::fillDateLabel (MyDate *myDate) {
    selectedDate = myDate;
    QString date = "Datum měření: " + myDate->toStringWithName();
    dateLabelEntry->setText(date);
}


void EntryWindow::fillUsers() {
    QList<User> users = UserManager::getInstance()->getUsers();
    foreach(User user, users) {
        QHBoxLayout *layout = new QHBoxLayout();

        QLabel *name = new QLabel;
        name->setText(user.getName());
        name->setStyleSheet("font-weight: bold; color: blue");
        layout->addWidget(name);
        layout->addStretch();
        QLabel *labelNT = new QLabel;
        labelNT->setText("      NT: ");
        labelNT->setStyleSheet("font-weight: bold; color: red");
        layout->addWidget(labelNT);

        /*double sumNTValue = user.getSummary(TypeEntry::realNT);
        QLabel *sumNT = new QLabel;
        sumNT->setText("Stav: " + QString::number(sumNTValue, 'f', 2));
        layout->addWidget(sumNT);*/

        QDoubleSpinBox *spinBoxNT = new QDoubleSpinBox;
        spinBoxNT->setObjectName(user.getName() + "_spinBoxNT");
        spinBoxNT->setRange(0, 9999999);
     //   spinBoxNT->setValue(sumNTValue);

        layout->addWidget(spinBoxNT);
        QLabel *coinLblNT = new QLabel();
        coinLblNT->setText("kWh");
        layout->addWidget(coinLblNT);

        QLabel *labelVT = new QLabel;
        labelVT->setText("      VT: ");
        labelVT->setStyleSheet("font-weight: bold; color: red");
        layout->addWidget(labelVT);


     /*   double sumVTValue = user.getSummary(TypeEntry::realVT);
        QLabel *sumVT = new QLabel;
        sumVT->setText("Stav: " + QString::number(sumVTValue, 'f', 2));
        layout->addWidget(sumVT);*/

        QDoubleSpinBox *spinBoxVT = new QDoubleSpinBox;
        spinBoxVT->setObjectName(user.getName() + "_spinBoxVT");
        spinBoxVT->setRange(0, 9999999);
        //spinBoxVT->setValue(sumVTValue);

        layout->addWidget(spinBoxVT);
        QLabel *coinLblVT = new QLabel();
        coinLblVT->setText("kWh");
        layout->addWidget(coinLblVT);
        usersLayout->addLayout(layout);
    }
}

 TypeMessageError EntryWindow::getValues() {
    entries.clear();
    QList<QWidget *> widgets = this->findChildren<QWidget*>();
    QList<QString> nameUsers = UserManager::getInstance()->getNameUsers();

    foreach (QString name, nameUsers) {
        User *user = UserManager::getInstance()->getUserByName(name);
        QString nameSpinBoxNT = name + "_spinBoxNT";
        QString nameSpinBoxVT = name + "_spinBoxVT";
        QDoubleSpinBox *spinBoxNT = this->findChild<QDoubleSpinBox *>(nameSpinBoxNT);

        QDoubleSpinBox *spinBoxVT = this->findChild<QDoubleSpinBox *>(nameSpinBoxVT);

        Entry entryNT;
        entryNT.type = TypeEntry::realNT;
        entryNT.user = name;
        double valNT = spinBoxNT->value();
        entryNT.setDate(*selectedDate);

        if (valNT < 0) {
            errorUser = user;
            entries.clear();
            return TypeMessageError::wrongInputData;
        }

        entryNT.value = valNT;
        entries.push_back(entryNT);

        Entry entryVT;
        entryVT.type = TypeEntry::realVT;
        entryVT.user = name;
        double valVT = spinBoxVT->value();

        entryVT.setDate(*selectedDate);

        if (valVT < 0) {
            errorUser = user;
            entries.clear();
            return TypeMessageError::wrongInputData;
        }
        entryVT.value =  valVT;
        entries.push_back(entryVT);
    }
    return TypeMessageError::correct;
}

EntryWindow::~EntryWindow() {
    delete ui;
}

void EntryWindow::on_cancelButton_clicked() {
    close();
}

void EntryWindow::on_okButton_clicked() {
    TypeMessageError typeMessageValue = getValues();
                if (typeMessageValue != TypeMessageError::correct) {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Chybná data");
                msgBox.setText("Špatně zadané data u " + errorUser->getName() + " nové hodnoty jsou záporné hodnoty.");
                msgBox.exec();
                return;
    }

    TypeMessageError typeMessage = UserManager::getInstance()->addEntries(entries);
    if (typeMessage == TypeMessageError::correct) {
        UserManager::getInstance()->saveCurrentUsersToJson();
        signalChangeData();
        close();
    } else {
        QMessageBox msgBox;
        if (typeMessage == TypeMessageError::sameDate) {
            msgBox.setWindowTitle("Chybná data");
            msgBox.setText("Toto datum se již použilo.");
        } else {
            msgBox.setWindowTitle("Chybná data");
            msgBox.setText("Jiná chyba");
        }
        msgBox.exec();
    }
}


