#ifndef PDFCREATOR_H
#define PDFCREATOR_H
#include <QString>
#include <QFile>
#include <QTextDocument>
#include <QPrinter>
#include <QTextStream>
#include <QTableView>
#include <QPrintDialog>

class PDFCreator
{
  public:
    PDFCreator();
    void createPDF();
    void addTitle(QString tit);
    void addTable (QTableView *tableView, QString nameTable);
    void addPath(QString pathRef);
    void addEmptyLine();


private:
    QString title;
    QString path;
    QList <QTableView*> listTables;
    QList <QString> listNamesTables;
    QString strStream;


};

#endif // PDFCREATOR_H
