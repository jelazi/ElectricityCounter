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

private:
    QList<User>usersList;
    void loadDefaultUser();
    int idCounter = 0;

};

#endif // USERMANAGER_H
