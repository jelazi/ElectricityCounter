#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QJsonObject>
#include <QJsonDocument>
#include "user.h"
#include "usermanager.h"
#include <QList>
#include <QDebug>
#include "invoice.h"


class JsonParser {
public:
    JsonParser();
    static QJsonObject userToJson(User user);
    static User jsonToUser(QJsonObject object);
    static QString createJsonUserFile (QList <User> userList);
    static QList <User> getUsersFromJson (QString json);

    static QJsonObject invoiceToJson(Invoice invoice);
    static Invoice jsonToInvoice(QJsonObject object);
    static QString createJsonInvoiceFile (QList <Invoice> invoicesList);
    static QList <Invoice> getInvoicesFromJson (QString json);

};

#endif // JSONPARSER_H
