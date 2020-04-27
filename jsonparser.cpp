#include "jsonparser.h"
#include <QString>
#include <QJsonObject>

JsonParser::JsonParser() {

}

QJsonObject JsonParser::userToJson(User user) {
    QJsonObject object;
    object["ID"] = user.getID();
    object["name"] = user.name;
    QJsonObject initialDesicionNT;
    QJsonObject initialDesicionVT;
    initialDesicionNT["date"] = user.initialDesicionNT.date.toString();
    initialDesicionNT["value"] = user.initialDesicionNT.value;
    initialDesicionVT["date"] = user.initialDesicionVT.date.toString();
    initialDesicionVT["value"] = user.initialDesicionVT.value;
    object["initialDesicionNT"] = initialDesicionNT;
    object["initialDesicionVT"] = initialDesicionVT;
    QJsonArray realEntriesVT = User::entriesToJson(user.realEntriesVT);
    object["realEntriesVT"] = realEntriesVT;
    QJsonArray realEntriesNT = User::entriesToJson(user.realEntriesNT);
    object["realEntriesNT"] = realEntriesNT;
    QJsonArray invoiceEntriesVT = User::entriesToJson(user.invoiceEntriesVT);
    object["invoiceEntriesVT"] = invoiceEntriesVT;
    QJsonArray invoiceEntriesNT = User::entriesToJson(user.invoiceEntriesNT);
    object["invoiceEntriesNT"] = invoiceEntriesNT;
    return object;
}

User JsonParser::jsonToUser(QJsonObject object) {
    QJsonValue IDValue = object.value("ID");
    int ID = IDValue.toInt();

    QJsonValue nameValue = object.value("name");
    QString name = nameValue.toString();

    QJsonValue initialDesicionNTValue = object.value("initialDesicionNT");
    QJsonValue initialDesicionVTValue = object.value("initialDesicionVT");

    QJsonObject initialDesicionNTObject = initialDesicionNTValue.toObject();

    QJsonObject initialDesicionVTObject = initialDesicionVTValue.toObject();

    Entry initialDesicionNT;
    initialDesicionNT.date = * new MyDate(initialDesicionNTObject.value("date").toString());
    initialDesicionNT.value = initialDesicionNTObject.value("value").toDouble();

    initialDesicionNT.type = TypeEntry::realNT;

    Entry initialDesicionVT;
    initialDesicionVT.date = * new MyDate(initialDesicionVTObject.value("date").toString());
    initialDesicionVT.value = initialDesicionVTObject.value("value").toDouble();
    initialDesicionVT.type = TypeEntry::realVT;

    User *user = new User(ID, name, initialDesicionNT, initialDesicionVT);

    QJsonValue arrayRealEntriesNTValue = object.value("realEntriesNT");
    QJsonValue arrayRealEntriesVTValue = object.value("realEntriesVT");

    QJsonArray arrayRealEntriesNT = arrayRealEntriesNTValue.toArray();
    user->realEntriesNT = User::entriesFromJson(arrayRealEntriesNT);
    QJsonArray arrayRealEntriesVT = arrayRealEntriesVTValue.toArray();
    user->realEntriesVT = User::entriesFromJson(arrayRealEntriesVT);

    QJsonValue arrayInvoiceEntriesNTValue = object.value("invoiceEntriesNT");
    QJsonValue arrayInvoiceEntriesVTValue = object.value("invoiceEntriesVT");

    QJsonArray arrayInvoiceEntriesNT = arrayInvoiceEntriesNTValue.toArray();
    user->invoiceEntriesNT = User::entriesFromJson(arrayInvoiceEntriesNT);
    QJsonArray arrayInvoiceEntriesVT = arrayInvoiceEntriesVTValue.toArray();
    user->invoiceEntriesVT = User::entriesFromJson(arrayInvoiceEntriesVT);
    return *user;
}


QString JsonParser::createJsonUserFile(QList <User> userList) {

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
            User user = jsonToUser(object);

            if (!user.name.isNull() && !user.name.isEmpty() && user.getID() > 0 && user.initialDesicionNT.value >= 0 && user.initialDesicionVT.value >= 0) {
                users.append(user);
            } else {
                qDebug()<< "noCorrect user data";
            }
        }

    return users;
}
