#include "usermanager.h"
QList<User>*usersList;
UserManager::UserManager() {

    loadDefaultUser();

}

void UserManager::loadDefaultUser() {
    addUser("Matějkovi", 0);
    addUser("Činčalovi", 0);
    addUser("Žižkovi", 0);
    addUser("Čapkovi", 0);
}

QList<User> UserManager::getUsers(){
    return usersList;
}

void UserManager::addUser(QString nameUser, float initialDesicion) {
    idCounter++;
    User *user = new User(idCounter, nameUser, initialDesicion);
    usersList.append(*user);
}
