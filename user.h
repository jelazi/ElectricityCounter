#ifndef USER_H
#define USER_H
#include "QString"
#include "structures.h"
#include "QJsonArray"

class User {
public:
    User(int id, QString name, Entry initialDesicionNT, Entry initialDesicionVT);

    int getID();
    void setID(int inputID);
    QList<Entry> getRealEntries(TypeEntry typeEntry);
    TypeMessageError addEntry(Entry entry);
    static QJsonArray entriesToJson(QList<Entry> entries);
    static QList<Entry> entriesFromJson (QJsonArray array);
    QList <Entry> getAllEntries();
    double getSummary (TypeEntry typeEntry);
    bool isCorrectNewSum (TypeEntry typeEntry, double newSum);
    bool containsEntry(MyDate date);
    QString getName();
    Entry getEntryByDate(MyDate date, TypeEntry typeEntry);

    void setName(const QString &value);

    QList<Entry> getRealEntriesVT() const;
    void setRealEntriesVT(const QList<Entry> &value);

    QList<Entry> getRealEntriesNT() const;
    void setRealEntriesNT(const QList<Entry> &value);

    Entry getInitialDesicionNT() const;
    void setInitialDesicionNT(const Entry &value);

    Entry getInitialDesicionVT() const;
    void setInitialDesicionVT(const Entry &value);

private:
    //properties
    QString name;
    QList <Entry> realEntriesVT;
    QList <Entry> realEntriesNT;
    Entry initialDesicionNT;
    Entry initialDesicionVT;


    int id;
    bool isSameDateEntry(Entry entry);
};

#endif // USER_H
