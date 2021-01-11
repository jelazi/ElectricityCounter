#include "filemanager.h"
#include <QFile>
#include <QDebug>

FileManager::FileManager() {

}

QString FileManager::loadTextFileWithPath(QString path) {

    QFile file(path);
    if (!file.exists()) {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        if (file.exists()) {
            qDebug() << "Created empty profilename file";
        } else {
            qDebug() << "Unable to create empty profilename file";
            return "";
        }
        file.close();

    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Issues with opening file!";
    }

    QTextStream out(&file);
    QString ret = out.readAll();
    file.close();
    return ret;
}

void FileManager::setTextToJsonFile(QString path, QString text) {
    QFile jsonFile(path);

    if (!jsonFile.exists()) {
        assert(0);
    }

    jsonFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&jsonFile);

    if(jsonFile.isOpen()){
        out << text;
        out.flush();
        jsonFile.close();
    }else{
        qDebug() <<"Error write file";
    }
}
