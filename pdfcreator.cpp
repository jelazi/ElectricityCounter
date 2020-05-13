#include "pdfcreator.h"



PDFCreator::PDFCreator() {

}

void PDFCreator::createPDF() {


    QTextStream out(&strStream);


  out <<  "<html>\n"
      "<head>\n"
      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
      <<  QString("<title>%1</title>\n").arg(title)
      <<  "</head>\n"
      "<body bgcolor=#ffffff link=#5000A0>\n"
         " <h1 align=center>"+ title+"</h1>";


          for (int i = 0; i < listTables.length(); i++) {

             out<< " <h2>" + listNamesTables[i]+ "</h2>";

              QTableView *tableView = listTables[i];
              const int rowCount = tableView->model()->rowCount();
              const int columnCount = tableView->model()->columnCount();
            out<<  "<table border=1 cellspacing=0 cellpadding=2>\n";

          // headers
          out << "<thead><tr bgcolor=#f0f0f0>";
          for (int column = 0; column < columnCount; column++)
              if (!tableView->isColumnHidden(column))
                  out << QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
          out << "</tr></thead>\n";

          // data table
          for (int row = 0; row < rowCount; row++) {
              out << "<tr>";
              for (int column = 0; column < columnCount; column++) {
                  if (!tableView->isColumnHidden(column)) {
                      QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
                      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                  }
              }
              out << "</tr>\n";
          }
          out <<  "</table>\n";
          out << "<br />";
          out << "<br />";
}

    out <<  "</body>\n"
      "</html>\n";

  QTextDocument *document = new QTextDocument();
  document->setHtml(strStream);

  QPrinter printer(QPrinter::PrinterResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPaperSize(QPrinter::A4);
  printer.setOutputFileName(path);
  printer.setPageMargins(QMarginsF(15, 15, 15, 15));

  document->print(&printer);
  delete document;

}

void PDFCreator::addTitle(QString tit) {
    title = tit;
}

void PDFCreator::addPath(QString pathRef) {
    path = pathRef;
}

void PDFCreator::addTable(QTableView *tableView, QString nameTable) {
    listTables.append(tableView);
    listNamesTables.append(nameTable);
}
