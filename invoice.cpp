#include "invoice.h"



Invoice::Invoice(MyDate dateRef) {
    date = dateRef;
}

void Invoice::changeInvoice(Invoice anotherInvoice) {
    date = anotherInvoice.date;
    fixedRate = anotherInvoice.fixedRate;
    variableRateNT = anotherInvoice.variableRateNT;
    variableRateVT = anotherInvoice.variableRateVT;
}





