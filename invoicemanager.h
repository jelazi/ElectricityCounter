#ifndef INVOICEMANAGER_H
#define INVOICEMANAGER_H
#include "invoice.h"


class InvoiceManager {
  public:

    static InvoiceManager* getInstance();

    Invoice* getInvoiceByDate (MyDate date);
    void addInvoice(Invoice invoice);
    void saveCurrentInvoiceToJson();
    bool containsInvoiceByDate(Invoice invoice);
    QList <Invoice> getInvoices();



  private:
      static InvoiceManager* instance;
      InvoiceManager();
      void loadInvoicesFromJson();


      QList<Invoice>invoicesList;
};

#endif // INVOICEMANAGER_H
