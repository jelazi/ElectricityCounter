#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "user.h"
#include "QList"
#include "QDebug"



class UserManager {
public:
    static UserManager* getInstance();

    QList<User> getUsers();
    void addUser (QString nameUser, Entry initialDesicionNT, Entry initialDesicionVT);
    void saveCurrentUsersToJson();
    bool removeUser(int ID);
    int getLastFreeID();
    QList<QString> getNameUsers ();
    TypeMessageError addEntries(QList<Entry> entries);
    User* getUserByName(QString name);

private:
    static UserManager* instance;
    UserManager();
    QList<User>usersList;
    void loadUsersFromJson();
    int idCounter = 0;
    void setDefaultUser();


};

#endif // USERMANAGER_H
