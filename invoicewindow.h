#ifndef ADDNEWINVOICE_H
#define ADDNEWINVOICE_H

#include <QDialog>
#include "mydate.h"

namespace Ui {
  class AddNewInvoice;
}

class InvoiceWindow : public QDialog
{
    Q_OBJECT

  public:
    explicit InvoiceWindow(QWidget *parent = nullptr);
    ~InvoiceWindow();
    void setDate(MyDate *myDate);

    void setIsEditInvoice(bool value);

private slots:


    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

    void on_pushButton_clicked();

signals:
    void signalChangeData();

  private:
    Ui::AddNewInvoice *ui;
    void addItems();
    void loadEditableData();
    bool isEditInvoice = false;

};

#endif // ADDNEWINVOICE_H
