#include "user.h"

User::User(int inputId, QString inputName, Entry InputInitialDesicionNT, Entry InputInitialDesicionVT) {
    this->id = inputId;
    this->name = inputName;
    this->initialDesicionNT = InputInitialDesicionNT;
    this->initialDesicionVT = InputInitialDesicionVT;
}

int User::getID() {
    return id;
}

void User::setID(int inputID) {
    if (this->id > 0) {
       return;
    }
    this->id = inputID;
}

QList<Entry> User::getRealEntries(TypeEntry typeEntry) {
    if (typeEntry == TypeEntry::realNT) {
        return realEntriesNT;
    } else {
        return realEntriesVT;
    }
}



TypeMessageError User::addEntry(Entry entry) {
    if (entry.type == TypeEntry::realNT) {
        if (!isSameDateEntry(entry)) {
            realEntriesNT.append(entry);
            return TypeMessageError::correct;
        } else {
            for (int i = 0; i < realEntriesNT.length(); i++) {
                if (realEntriesNT[i].date.isSameDate(entry.date)) {
                    realEntriesNT[i].value = entry.value;
                    return TypeMessageError::correct;
                }
            }
        }
    }
    if (entry.type == TypeEntry::realVT) {
        if (!isSameDateEntry(entry)) {
            realEntriesVT.append(entry);
            return TypeMessageError::correct;
        } else {
            for (int i = 0; i < realEntriesVT.length(); i++) {
                if (realEntriesVT[i].date.isSameDate(entry.date)) {
                    realEntriesVT[i].value = entry.value;
                    return TypeMessageError::correct;
                }
            }
        }
    }

    return TypeMessageError::anotherError;
}



QJsonArray User::entriesToJson(QList<Entry> entries) {
    QJsonArray array;
       for (Entry entry : entries)
          array.append(entry.toJson());
       return array;
}


QList<Entry> User::entriesFromJson (QJsonArray array) {
    QList<Entry> entries;
    foreach (QJsonValue entryJson, array) {
        QJsonObject entryObject = entryJson.toObject();
        Entry entry;
        entry.date = MyDate (entryObject["date"].toString());
        entry.user = entryObject["user"].toString();
        entry.type = (entryObject["type"] == "NT") ? TypeEntry::realNT : TypeEntry::realVT;
        entry.value = entryObject["value"].toDouble();
        entries.push_back(entry);
    }
    return entries;
}

bool User::isSameDateEntry(Entry inputEntry) {
    QList <Entry> entries;
    if (inputEntry.type == TypeEntry::realNT) {
        entries = this->realEntriesNT;
    }
    if (inputEntry.type == TypeEntry::realVT) {
        entries = this->realEntriesVT;
    }


    foreach (Entry ent, entries) {
        if (ent.date.compareDates(inputEntry.date) == 0) return true;
    }

    return false;
}


QList <Entry> User::getAllEntries () {
    QList <Entry> entries;
    entries.append(realEntriesNT);
    entries.append(realEntriesVT);

   std::sort(entries.begin(), entries.end(),
             [](Entry & a, Entry & b) -> bool
         {
             return a.date.isLessThan(b.date);
         });
    return entries;
}

double User::getSummary(TypeEntry typeEntry) {

    int sum = 0;
    switch (typeEntry) {
    case TypeEntry::realNT : {
        sum = initialDesicionNT.value;
        foreach (Entry entry, realEntriesNT) {
            sum += entry.value;
        }
            break;
        }
    case TypeEntry::realVT : {
        sum = initialDesicionVT.value;
        foreach (Entry entry, realEntriesVT) {
            sum += entry.value;
        }
            break;
        }

    }
    return sum;
}

bool User::isCorrectNewSum(TypeEntry typeEntry, double newSum) {
    int beforeSum = getSummary(typeEntry);
    return (beforeSum <=newSum);
}



QString User::getName() {
  return name;
}

Entry User::getEntryByDate(MyDate date, TypeEntry typeEntry) {
  if (typeEntry == TypeEntry::realNT) {
      foreach (Entry ent, realEntriesNT) {
          if (ent.date.isSameDate(date)) return ent;
        }
    }
  if (typeEntry == TypeEntry::realVT) {
      foreach (Entry ent, realEntriesVT) {
          if (ent.date.isSameDate(date)) return ent;
        }
    }
  qDebug()<<"Error: entry dont find";
  Entry entry;
  return entry;
}

void User::setName(const QString &value)
{
    name = value;
}

QList<Entry> User::getRealEntriesVT() const
{
    return realEntriesVT;
}

void User::setRealEntriesVT(const QList<Entry> &value)
{
    realEntriesVT = value;
}

QList<Entry> User::getRealEntriesNT() const
{
    return realEntriesNT;
}

void User::setRealEntriesNT(const QList<Entry> &value)
{
    realEntriesNT = value;
}

Entry User::getInitialDesicionNT() const
{
    return initialDesicionNT;
}

void User::setInitialDesicionNT(const Entry &value)
{
    initialDesicionNT = value;
}

Entry User::getInitialDesicionVT() const
{
    return initialDesicionVT;
}

void User::setInitialDesicionVT(const Entry &value)
{
    initialDesicionVT = value;
}

bool User::containsEntry(MyDate date)  {
    foreach (Entry ent, realEntriesNT) {
        if (ent.date.isSameDate(date)) {
            foreach (Entry entVT, realEntriesVT) {
              if (entVT.date.isSameDate(date)) return true;
            }
          return false;
        }
    }
  return false;
}
