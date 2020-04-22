#ifndef USER_H
#define USER_H
#include "QString"


class User {
public:
    User(int id, QString name, float initialDesicion);
    QString name;
    int id;
    float initialDesicion;

private:



};

#endif // USER_H
