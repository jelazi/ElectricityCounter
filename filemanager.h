#ifndef FILEMANAGER_H
#define FILEMANAGER_H
 #include <QString>


class FileManager
{
public:
    FileManager();
    static QString loadTextFileWithPath(QString path);
    static void setTextToJsonFile(QString path, QString text);
};

#endif // FILEMANAGER_H
