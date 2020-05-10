#include "mydate.h"

QList<QString> nameMonths = {"leden", "únor", "březen", "duben", "květen", "červen", "červenec", "srpen", "září", "říjen", "listopad", "prosinec"};

MyDate::MyDate(){
  this->month = 1;
  this->year = 2016;

}

MyDate::MyDate(int month, int year) {
    if (!(month > 0 && month < 13 && year > 2015 && year < 2100)) {
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
     if (!(m > 0 && m < 13 && y > 2015 && y < 2100)) {
         qDebug()<< "no correct data";
         return;
     }
     this->year = y;
     this->month = m;
}

QString MyDate::toStringWithName() {
    QString result = nameMonths[month - 1] + " " + QString::number(year);
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
    if (this->year < anotherDate.getYear()) return -1;
    if (this->month > anotherDate.getMonth()) return 1;
    if (this->month < anotherDate.getMonth()) return -1;
    return 0;
}

MyDate MyDate::getCurrentDate() {
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

bool MyDate::isLessThan(MyDate anotherDate) {
    if (this->year < anotherDate.year) return true;
    if (this->month < anotherDate.month) return true;
    return false;
}

bool MyDate::isSameDate(MyDate anotherDate) {
    if (this->year == anotherDate.year && this->month == anotherDate.month) return true;
    return false;
}

QList <QString> MyDate::getListNameMonths() {
  QList<QString> months = {"leden", "únor", "březen", "duben", "květen", "červen", "červenec", "srpen", "září", "říjen", "listopad", "prosinec"};
  return months;
}
