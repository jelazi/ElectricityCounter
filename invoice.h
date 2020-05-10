#ifndef INVOICE_H
#define INVOICE_H
#include "mydate.h"


class Invoice {
  public:

    Invoice(MyDate dateRef);
    double fixedRateNT;
    double fixedRateVT;
    double variableRateNT;
    double variableRateVT;
    MyDate date;

  private:


};

#endif // INVOICE_H
