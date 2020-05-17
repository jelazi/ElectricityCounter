#include "usermanager.h"
#include <QFile>
#include "filemanager.h"
#include "jsonparser.h"
#include <QDir>
#include <QDate>


const QString pathUserJson = QDir::currentPath() + "/user.json";

UserManager* UserManager::instance = 0;

UserManager* UserManager::getInstance() {
    if (instance == 0) {
        instance = new UserManager();
    }
    return instance;
}

UserManager::UserManager() {
    loadUsersFromJson();
}



void UserManager::loadUsersFromJson() {
    QString users = FileManager::loadTextFileWithPath(pathUserJson);
    if (users.isEmpty()) {
        setDefaultUser();
        qDebug()<<"I can read json user file";
    } else {
        usersList = JsonParser::getUsersFromJson(users);
    }
}

QList<User> UserManager::getUsers() {
    return usersList;
}

bool UserManager::removeUser(int ID) {
    for (int i = 0; i<usersList.length(); i++) {
        if (usersList[i].getID() == ID) {
            usersList.removeAt(i);
            return true;
        }
    }
    return false;
}


void UserManager::setDefaultUser() {
    Entry entryVT;
    MyDate now = MyDate::getCurrentDate();
    entryVT.date = now;
    entryVT.type = TypeEntry::realVT;
    entryVT.value = 0;

    Entry entryNT;
    entryNT.date = now;
    entryNT.type = TypeEntry::realNT;
    entryNT.value = 0;

    addUser("Matějkovi", entryNT, entryVT);
    addUser("Činčalovi", entryNT, entryVT);
    addUser("Žižkovi", entryNT, entryVT);
    addUser("Čapkovi", entryNT, entryVT);
    addUser("Hvězda", entryNT, entryVT);
    saveCurrentUsersToJson();
}


void UserManager::saveCurrentUsersToJson() {
    QString jsonString = JsonParser::createJsonUserFile(usersList);
    FileManager::setTextToJsonFile(pathUserJson, jsonString);
}

void UserManager::addUser(QString nameUser, Entry initialDesicionNT, Entry initialDesicionVT) {
    idCounter++;
    User *user = new User(idCounter, nameUser, initialDesicionNT, initialDesicionVT);
    usersList.append(*user);
}



int UserManager::getLastFreeID() {
    int lastIndex = 0;
    bool indexSearching = true;
    if (usersList.isEmpty()) return lastIndex;
    while (indexSearching) {
        for(int i = 0; i < usersList.length();i++) {
            if (usersList[i].getID() == lastIndex
                    ) {
                indexSearching = true;
                lastIndex++;
                break;
            } else {
                indexSearching = false;
            }
        }

    }
    return lastIndex;
}


QList<QString> UserManager::getNameUsers () {
    QList<QString> userNames;
    foreach (User user, usersList) {
        userNames.push_back(user.name);
    }
    return userNames;
}

TypeMessageError UserManager::addEntries(QList<Entry> entries) {
    for (int i = 0; i<entries.length();i++) {
        TypeMessageError typeMessage = getUserByName(entries[i].user)->addEntry(entries[i]);
        if (typeMessage != TypeMessageError::correct) {
            return typeMessage;
        }
    }
    return TypeMessageError::correct;
}


User* UserManager::getUserByName(QString name) {
    for (int i = 0; i < usersList.length(); i++) {
        if (usersList[i].name == name) return &usersList[i];
    }
    qDebug()<<"error find user in usersList";
    return &usersList[0];
}

QList<QString> UserManager::getAllNameDates() {
    QList<QString> allDates;
    QList <Entry> entries;
    foreach (User user, usersList) {
        entries.append(user.getAllEntries());

        }
    std::sort(entries.begin(), entries.end(),
              [](Entry & a, Entry & b) -> bool
          {
              return a.date.isLessThan(b.date);
          });

    foreach (Entry entry, entries) {
        QString nameDate;
        if (entry.type == TypeEntry::realNT) {
            nameDate = "Sk NT: " + entry.date.toStringWithName();
        }
        if (entry.type == TypeEntry::realVT) {
            nameDate = "Sk VT: " + entry.date.toStringWithName();
        }


        if(!allDates.contains(nameDate)) {
            allDates.push_back(nameDate);
            allDates.push_back("% " + nameDate);
        }
    }
    return allDates;
}

QList<MyDate> UserManager::getAllDates() {
    QList<QString> allDatesName;
    QList<MyDate> allDate;
    QList <Entry> entries;
    foreach (User user, usersList) {
        entries.append(user.getAllEntries());

        }
    std::sort(entries.begin(), entries.end(),
              [](Entry & a, Entry & b) -> bool
          {
              return a.date.isLessThan(b.date);
          });

    foreach (Entry entry, entries) {
        QString nameDate;
        if (entry.type == TypeEntry::realNT) {
            nameDate = entry.date.toStringWithName();
        }
        if (entry.type == TypeEntry::realVT) {
            nameDate = entry.date.toStringWithName();
        }


        if(!allDatesName.contains(nameDate)) {
            allDatesName.push_back(nameDate);
            allDatesName.push_back("% " + nameDate);
            allDate.push_back(entry.date);
        }
    }
    return allDate;
}




double UserManager::getRatioUserEntry(Entry entry) {
    QList <Entry> entriesCompare = getEntriesForCompare(entry);
    double sum = 0.0;
    foreach (Entry entry, entriesCompare) {
        sum += entry.value;
    }
    if (entry.value == 0 || sum == 0) return 0;
    return entry.value / sum;
}

QList<Entry> UserManager::getEntriesForCompare(Entry entry) {
    QList <Entry> entriesCompare;
    foreach (User user, usersList) {
        foreach (Entry ent, user.getAllEntries()) {
            if (entry.type == ent.type && entry.date.isSameDate(ent.date)) {
                entriesCompare.append(ent);
            }
        }
    }
    return entriesCompare;
}

void UserManager::updateUser(User user) {
    for (int i = 0; i < usersList.length(); i++) {
        if (usersList[i].getID() == user.getID()) {
           usersList[i].name = user.name;
           usersList[i].initialDesicionNT = user.initialDesicionNT;
           usersList[i].initialDesicionVT = user.initialDesicionVT;
        }
    }
}

double UserManager::getEntryValue(User user, MyDate date, TypeEntry typeEntry) {
  User *choiceUser = getUserByName(user.getName());
  if (typeEntry == TypeEntry::realNT) {
      foreach (Entry entry, choiceUser->getRealEntries(TypeEntry::realNT)) {
          if (entry.date.isSameDate(date)) return entry.value;
        }
    }

  if (typeEntry == TypeEntry::realVT) {
      foreach (Entry entry, choiceUser->getRealEntries(TypeEntry::realVT)) {
          if (entry.date.isSameDate(date)) return entry.value;
        }
    }

  qDebug()<<"no entry in user";
  return 0;
}


