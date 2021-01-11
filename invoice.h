#ifndef INVOICE_H
#define INVOICE_H
#include "mydate.h"


class Invoice {
  public:

    Invoice(MyDate dateRef);
    double fixedRate;
    double variableRateNT;
    double variableRateVT;
    MyDate date;

    void changeInvoice(Invoice anotherInvoice);

  private:


};

#endif // INVOICE_H
