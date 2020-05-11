#ifndef VIEWRESULT_H
#define VIEWRESULT_H

#include <QDialog>
#include "mydate.h"
#include "QStandardItem"

namespace Ui {
  class ViewResult;
}

class ViewResult : public QDialog {
    Q_OBJECT

  public:
    explicit ViewResult(QWidget *parent = nullptr);
    ~ViewResult();
    void setDate (MyDate *myDate);

  private slots:


    void on_btnCancel_clicked();

    void on_btnCreatePdf_clicked();

    void on_btnSendMail_clicked();

  private:
    Ui::ViewResult *ui;
    void reloadInvoiceTable();
    void reloadEntriesTable();

    QStandardItemModel modelInvoice;
    QStandardItemModel modelEntries;
    QStringList horizontalHeaderInvoice;
    QStringList verticalHeaderInvoice;
    QStringList horizontalHeaderEntries;
    QStringList verticalHeaderEntries;
};

#endif // VIEWRESULT_H
