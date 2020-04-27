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
int selectedMonth;
int selectedYear;
Entry NT;
Entry VT;
User *errorUser = new User(1, "", NT, VT);




AddNewEntry::AddNewEntry(QWidget *parent): QDialog(parent), ui(new Ui::AddNewEntry) {
    entries.clear();
    ui->setupUi(this);
    this->setWindowTitle("Přidání měření");
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
    selectedMonth = now.getMonth();
    selectedYear = now.getYear();
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
        layout->addStretch();
        QLabel *labelNT = new QLabel;
        labelNT->setText("NT: ");
        layout->addWidget(labelNT);
        double sumNTValue = user.getSummary(TypeEntry::realNT);
        QLabel *sumNT = new QLabel;
        sumNT->setText("Stav: " + QString::number(sumNTValue, 'f', 2));
        layout->addWidget(sumNT);
        QDoubleSpinBox *spinBoxNT = new QDoubleSpinBox;
        spinBoxNT->setObjectName(user.name + "_spinBoxNT");
        spinBoxNT->setValue(sumNTValue);
        spinBoxNT->setRange(0, 9999999);
        layout->addWidget(spinBoxNT);
        QLabel *labelVT = new QLabel;
        labelVT->setText("VT: ");
        layout->addWidget(labelVT);
        double sumVTValue = user.getSummary(TypeEntry::realVT);
        QLabel *sumVT = new QLabel;
        sumVT->setText("Stav: " + QString::number(sumVTValue, 'f', 2));
        layout->addWidget(sumVT);
        QDoubleSpinBox *spinBoxVT = new QDoubleSpinBox;
        spinBoxVT->setObjectName(user.name + "_spinBoxVT");
        spinBoxVT->setRange(0, 9999999);
        spinBoxVT->setValue(sumVTValue);
        layout->addWidget(spinBoxVT);
        usersLayout->addLayout(layout);
    }
}

 TypeMessageError AddNewEntry::getValues() {
    entries.clear();
    QList<QWidget *> widgets = this->findChildren<QWidget*>();
    MyDate *selectedDate = new MyDate(selectedMonth, selectedYear);
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
        if (!user->isCorrectNewSum(entryNT.type, valNT)) {
            errorUser = user;
            entries.clear();
            return TypeMessageError::wrongInputData;
        }
        entryNT.value = valNT - user->getSummary(TypeEntry::realNT);
        entries.push_back(entryNT);

        Entry entryVT;
        entryVT.type = TypeEntry::realVT;
        entryVT.user = name;
        double valVT = spinBoxVT->value();

        entryVT.setDate(*selectedDate);
        if (!user->isCorrectNewSum(entryVT.type, valVT)) {
            errorUser = user;
            entries.clear();
            return TypeMessageError::wrongInputData;
        }
        entryVT.value =  valVT - user->getSummary(TypeEntry::realVT);
        entries.push_back(entryVT);
    }
    return TypeMessageError::correct;
}

AddNewEntry::~AddNewEntry() {
    delete ui;
}

void AddNewEntry::on_cancelButton_clicked() {
    close();
}

void AddNewEntry::on_okButton_clicked() {
    TypeMessageError typeMessageValue = getValues();
                if (typeMessageValue != TypeMessageError::correct) {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Chybná data");
                msgBox.setText("Špatně zadané data u " + errorUser->name + " nové hodnoty jsou menší než původní.");
                msgBox.exec();
                return;
    }

    TypeMessageError typeMessage = UserManager::getInstance()->addEntries(entries);
    if (typeMessage == TypeMessageError::correct) {
        UserManager::getInstance()->saveCurrentUsersToJson();
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

void AddNewEntry::on_monthComboBox_currentIndexChanged(int index) {
    selectedMonth = index + 1;
}

void AddNewEntry::on_yearComboBox_currentIndexChanged(int index) {
    selectedYear = years[index].toInt();
    qDebug()<<selectedYear;
}
