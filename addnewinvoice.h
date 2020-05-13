#ifndef ADDNEWINVOICE_H
#define ADDNEWINVOICE_H

#include <QDialog>
#include "mydate.h"

namespace Ui {
  class AddNewInvoice;
}

class AddNewInvoice : public QDialog
{
    Q_OBJECT

  public:
    explicit AddNewInvoice(QWidget *parent = nullptr);
    ~AddNewInvoice();
    void setDate(MyDate *myDate);

  private slots:


    void on_cancelBtn_clicked();

    void on_okBtn_clicked();

signals:
    void signalChangeData();

  private:
    Ui::AddNewInvoice *ui;
    void addItems();
};

#endif // ADDNEWINVOICE_H
