#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "user.h"
#include "QList"
#include "QDebug"


class UserManager {
public:
    UserManager();
    QList<User> getUsers();
    void addUser (QString nameUser, float initialDesicion);
    int getLastID();

private:
    QList<User>usersList;
    void loadUsersFromJson();
    int idCounter = 0;
    void setDefaultUser();
    void saveCurrentUsersToJson();

};

#endif // USERMANAGER_H
