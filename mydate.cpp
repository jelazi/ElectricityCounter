#include "mydate.h"

QList<QString> nameMonths = {"leden", "únor", "březen", "duben", "květen", "červen", "červenec", "srpen", "září", "říjen", "listopad", "prosinec"};

MyDate::MyDate(int month, int year) {
    if (!(month > 0 && month < 13 && year > 2019 && year < 2100)) {
        qDebug()<< "no correct data";
        return;
    }
    this->month = month;
    this->year = year;
}

MyDate::MyDate (QString nameDate) {
     QStringList myStringList = nameDate.split(',');
     int m = (myStringList.first()).toInt();
     int y = (myStringList.last().toInt());
     if (!(m > 0 && m < 13 && y > 2019 && y < 2100)) {
         qDebug()<< "no correct data";
         return;
     }
     this->year = y;
     this->month = m;
}

QString MyDate::toStringWithName() {
    QString result = nameMonths[month - 1] + ", " + QString::number(year);
    return result;
}

QString MyDate::toString() {
    return QString::number(month) + ", " + QString::number(year);
}

QString MyDate::getNameMonth() {
    return nameMonths[month - 1];
}

int MyDate::getYear() {
    return year;
}

int MyDate::getMonth() {
    return month;
}

int MyDate::compareDates(MyDate anotherDate) {
    if (this->year > anotherDate.getYear()) return 1;
    if (this->year > anotherDate.getYear()) return -1;
    if (this->month > anotherDate.getMonth()) return 1;
    if (this->month > anotherDate.getMonth()) return -1;
    return 0;
}

MyDate MyDate::getNowDate() {
    QDate now = QDate::currentDate();
    MyDate *myDate = new MyDate (now.month(), now.year());
    return *myDate;
}

QJsonObject MyDate::toJson () {
    QJsonObject object;
    object["month"] = this->month;
    object["year"] = this->year;
    return object;
}
