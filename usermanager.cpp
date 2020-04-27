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
    MyDate now = MyDate::getNowDate();
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

    saveCurrentUsersToJson();
}


void UserManager::saveCurrentUsersToJson() {
    QString jsonString = JsonParser::createJsonUserFile();
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
