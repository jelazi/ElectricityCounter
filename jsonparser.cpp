#include "jsonparser.h"

JsonParser::JsonParser() {

}

QJsonObject JsonParser::userToJson(User user) {
    QJsonObject object;
    object["ID"] = user.id;
    object["name"] = user.name;
    object["initialDesicion"] = user.initialDesicion;
    return object;
}

User JsonParser::jsonToUser(QJsonObject object) {
    QJsonValue IDValue = object.value("ID");
    int ID = IDValue.toString().toInt();

    QJsonValue nameValue = object.value("name");
    QString name = nameValue.toString();

    QJsonValue initialDesicionValue = object.value("initialDesicion");
    float initialDesicion = initialDesicionValue.toString().toFloat();

    User *user = new User(ID, name, initialDesicion);
    return *user;
}


QString JsonParser::createJsonUserFile(UserManager *userManager) {
    QList <User> userList = userManager->getUsers();
    QJsonDocument document;
    QJsonObject rootObject;
    for (int i = 0; i < userList.length();i++) {
        rootObject.insert(QString::number(i), JsonParser::userToJson(userList[i]));
    }
    document.setObject(rootObject);
    return document.toJson();
}

QList <User> JsonParser::getUsersFromJson (QString json) {
    QList <User> users;
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObject = document.object();
    foreach(const QString& key, jsonObject.keys()) {
            QJsonValue value = jsonObject[key];
            QJsonObject object = value.toObject();
            QString name = object["name"].toString();
            int ID = object["ID"].toInt();
            float initialDesicion = object["initialDesicion"].toDouble();
            if (!name.isNull() && !name.isEmpty() && ID > 0 && initialDesicion >= 0) {
                User *user = new User(ID, name, initialDesicion);
                users.append(*user);
            }
        }

    return users;
}
