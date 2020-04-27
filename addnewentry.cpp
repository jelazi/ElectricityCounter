#include "addnewentry.h"
#include "ui_addnewentry.h"
#include "usermanager.h"
#include "QDoubleSpinBox"


QPushButton *okButtonAddEntry;
QPushButton *cancelButtonAddEntry;
QComboBox *monthComboBoxAddEntry;
QComboBox *yearComboBoxAddEntry;
QVBoxLayout *usersLayout;

QList<QString> months = {"leden", "únor", "březen", "duben", "květen", "červen", "červenec", "srpen", "září", "říjen", "listopad", "prosinec"};
QList<QString> years;

QList <Entry> entries;


AddNewEntry::AddNewEntry(QWidget *parent): QDialog(parent), ui(new Ui::AddNewEntry) {
    ui->setupUi(this);
    okButtonAddEntry = ui->okButton;
    cancelButtonAddEntry = ui->cancelButton;
    monthComboBoxAddEntry = ui->monthComboBox;
    yearComboBoxAddEntry = ui->yearComboBox;
    usersLayout = ui->userLayout;
    fillYearsList();
    fillUsers();

}

void AddNewEntry::fillYearsList () {
    MyDate now = MyDate::getNowDate();
    int nowYear = now.getYear();
    for (int i = nowYear - 1; i < nowYear + 30; i++) {
        years.push_back(QString::number(i));
    }
    foreach (QString month, months) {
        monthComboBoxAddEntry->addItem(month);
    }
    monthComboBoxAddEntry->setCurrentIndex(now.getMonth() - 1);
    int width = monthComboBoxAddEntry->minimumSizeHint().width();
    monthComboBoxAddEntry->setMinimumWidth(width);
    foreach (QString year, years) {
        yearComboBoxAddEntry->addItem(year, QVariant(year.toInt()));
    }
    yearComboBoxAddEntry->setCurrentIndex(1);
}


void AddNewEntry::fillUsers() {
    QList<User> users = UserManager::getInstance()->getUsers();
    foreach(User user, users) {
        QHBoxLayout *layout = new QHBoxLayout();
        QLabel *name = new QLabel;
        name->setText(user.name);
        name->setStyleSheet("font-weight: bold; color: blue");
        layout->addWidget(name);
        QLabel *labelNT = new QLabel;
        labelNT->setText("NT: ");
        layout->addWidget(labelNT);
        QDoubleSpinBox *spinBoxNT = new QDoubleSpinBox;
        spinBoxNT->setObjectName(user.name + "_spinBoxNT");
        spinBoxNT->setValue(0);
        layout->addWidget(spinBoxNT);
        QLabel *labelVT = new QLabel;
        labelVT->setText("VT: ");
        layout->addWidget(labelVT);
        QDoubleSpinBox *spinBoxVT = new QDoubleSpinBox;
        spinBoxVT->setObjectName(user.name + "_spinBoxVT");
        spinBoxVT->setValue(0);
        layout->addWidget(spinBoxVT);
        usersLayout->addLayout(layout);

    }
}

void AddNewEntry::getValues() {
    QList<QWidget *> widgets = this->findChildren<QWidget*>();
    MyDate *selectedDate = new MyDate(monthComboBoxAddEntry->currentIndex() + 1, yearComboBoxAddEntry->itemData(yearComboBoxAddEntry->currentIndex()).toInt());
    QList<QString> nameUsers = UserManager::getInstance()->getNameUsers();

    foreach (QString name, nameUsers) {
        QString nameSpinBoxNT = name + "_spinBoxNT";
        QString nameSpinBoxVT = name + "_spinBoxVT";
        QDoubleSpinBox *spinBoxNT = this->findChild<QDoubleSpinBox *>(nameSpinBoxNT);
        QDoubleSpinBox *spinBoxVT = this->findChild<QDoubleSpinBox *>(nameSpinBoxVT);
        Entry entryNT;
        entryNT.type = TypeEntry::realNT;
        entryNT.user = name;
        entryNT.value = spinBoxNT->value();
        entryNT.setDate(*selectedDate);
        entries.push_back(entryNT);

        Entry entryVT;
        entryVT.type = TypeEntry::realVT;
        entryVT.user = name;
        entryVT.value = spinBoxVT->value();
        entryVT.setDate(*selectedDate);
        entries.push_back(entryVT);
    }
}

AddNewEntry::~AddNewEntry() {
    delete ui;
}

void AddNewEntry::on_cancelButton_clicked() {
    close();
}

void AddNewEntry::on_okButton_clicked() {
    getValues();
    TypeMessageError typeMessage = UserManager::getInstance()->addEntries(entries);
    if (typeMessage == TypeMessageError::correct) {
        UserManager::getInstance()->saveCurrentUsersToJson();
        close();
    } else {
        QMessageBox msgBox;
        if (typeMessage == TypeMessageError::sameDate) {
            msgBox.setText("Toto datum se již použilo.");
        } else {
            msgBox.setText("Jiná chyba");
        }
        msgBox.exec();
    }
}
