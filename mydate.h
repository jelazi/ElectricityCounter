#ifndef MYDATE_H
#define MYDATE_H
#include <QString>
#include <QList>
#include <QDebug>
#include <QDate>
#include <QJsonObject>


class MyDate {
public:
    MyDate(int month, int year);
    MyDate (QString nameDate);
    QString toStringWithName();
    QString toString();
    QString getNameMonth ();
    int getMonth ();
    int getYear ();
    static MyDate getNowDate();
    QJsonObject toJson();
    bool isSameDate(MyDate anotherDate);

    // -1 is early, 0 is same, 1 is later
    int compareDates(MyDate anotherDate);
    bool isLessThan (MyDate anotherDate);

private:
    int month;
    int year;
};

#endif // MYDATE_H
