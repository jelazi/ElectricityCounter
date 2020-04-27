#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QDate>
#include "mydate.h"
#include "QJsonObject"

enum TypeEntry {
    realVT,
    realNT,
    invoiceVT,
    invoiceNT
};


enum TypeMessageError {
    sameDate,
    anotherError,
    correct
};


struct Entry {
    double value;
    TypeEntry type;
    MyDate date = MyDate::getNowDate();
    QString user;
    void setDate(MyDate newDate) {
      date = newDate;
    };
    QJsonObject toJson() {
        QJsonObject object;
        object["value"] = value;
        object["type"] =  (type == TypeEntry::realNT)? "NT":"VT";
        object["date"] = date.toString();
        object["user"] = user;
        return object;
    }
};






#endif // STRUCTURES_H
