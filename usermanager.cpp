#include "usermanager.h"
#include <QFile>
#include "filemanager.h"
#include "jsonparser.h"
#include <QDir>


QList<User>*usersList;
const QString pathUserJson = QDir::currentPath() + "/user.json";
UserManager::UserManager() {

    loadUsersFromJson();

}

void UserManager::loadUsersFromJson() {

    qDebug()<<pathUserJson;
    QString users = FileManager::loadTextFileWithPath(pathUserJson);
    if (users.isEmpty()) {
        setDefaultUser();
        qDebug()<<"I can read json user file";
    } else {
        usersList = JsonParser::getUsersFromJson(users);
    }
}

QList<User> UserManager::getUsers(){
    return usersList;
}


void UserManager::setDefaultUser() {
    addUser("Matějkovi", 0);
    addUser("Činčalovi", 0);
    addUser("Žižkovi", 0);
    addUser("Čapkovi", 0);
    saveCurrentUsersToJson();
}


void UserManager::saveCurrentUsersToJson() {
    QString jsonString = JsonParser::createJsonUserFile(this);
    FileManager::setTextToJsonFile(pathUserJson, jsonString);
}

void UserManager::addUser(QString nameUser, float initialDesicion) {
    idCounter++;
    User *user = new User(idCounter, nameUser, initialDesicion);
    usersList.append(*user);
}

int UserManager::getLastID() {
    return idCounter;
}
