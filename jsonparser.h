#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QJsonObject>
#include <QJsonDocument>
#include "user.h"
#include "usermanager.h"
#include <QList>
#include <QDebug>


class JsonParser {
public:
    JsonParser();
    static QJsonObject userToJson(User user);
    static User jsonToUser(QJsonObject object);
    static QString createJsonUserFile (QList <User> userList);
    static QList <User> getUsersFromJson (QString json);
};

#endif // JSONPARSER_H
