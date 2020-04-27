#ifndef USER_H
#define USER_H
#include "QString"
#include "structures.h"
#include "QJsonArray"

class User {
public:
    User(int id, QString name, Entry initialDesicionNT, Entry initialDesicionVT);
    QString name;
    QList <Entry> realEntriesVT;
    QList <Entry> realEntriesNT;
    QList <Entry> invoiceEntriesVT;
    QList <Entry> invoiceEntriesNT;
    Entry initialDesicionNT;
    Entry initialDesicionVT;
    int getID();
    void setID(int inputID);
    QList<Entry> getRealEntries(TypeEntry typeEntry);
    QList<Entry> getInvoiceEntries(TypeEntry typeEntry);
    TypeMessageError addEntry(Entry entry);
    static QJsonArray entriesToJson(QList<Entry> entries);
    static QList<Entry> entriesFromJson (QJsonArray array);

private:
    int id;
    bool isSameDateEntry(Entry entry);
};

#endif // USER_H
