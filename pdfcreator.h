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
    void createPDF(QTableView *tableView, QString path, QString title);
};

#endif // PDFCREATOR_H
