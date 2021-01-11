#include "invoicemanager.h"
#include "filemanager.h"
#include <QDir>
#include "jsonparser.h"


InvoiceManager* InvoiceManager::instance = 0;
const QString pathInvoiceJson = QDir::currentPath() + "/invoices.json";

InvoiceManager* InvoiceManager::getInstance() {
    if (instance == 0) {
        instance = new InvoiceManager();
    }
    return instance;
}

InvoiceManager::InvoiceManager() {
    loadInvoicesFromJson();
}


void InvoiceManager::loadInvoicesFromJson() {
  QString invoicesString = FileManager::loadTextFileWithPath(pathInvoiceJson);
  if (invoicesString.isEmpty()) {
      qDebug()<<"I can read json invoice file";
      saveCurrentInvoiceToJson();
  } else {
      invoicesList = JsonParser::getInvoicesFromJson(invoicesString);
  }
}


void InvoiceManager::editInvoice(Invoice invoice) {
    if (invoicesList.isEmpty()) {
        qDebug()<<"error invoices list is empty";
        return;
    }
    for (int i = 0; i <invoicesList.length(); i++) {
        if (invoicesList[i].date.isSameDate(invoice.date)) {
            invoicesList[i].changeInvoice(invoice);
        }
    }
    saveCurrentInvoiceToJson();
}

void InvoiceManager::deleteInvoice(Invoice invoice) {
    if (invoicesList.isEmpty()) {
        qDebug()<<"invoices list is empty";
        return;
    }
    for (int i = 0; i < invoicesList.length(); i++) {
        if (invoicesList[i].date.isSameDate(invoice.date)) {
            invoicesList.removeAt(i);
            saveCurrentInvoiceToJson();
            return;
        }
    }
    qDebug()<<"Error: there is not invoice this date";
}


Invoice* InvoiceManager::getInvoiceByDate(MyDate date) {
  for (int i = 0; i< invoicesList.length(); i++) {
      if (invoicesList[i].date.isSameDate(date)) {
          return &invoicesList[i];
      }
    }
          qDebug()<<"error find invoice in invoicesList";
          return &invoicesList[0];

}

void InvoiceManager::addInvoice(Invoice invoice) {
  invoicesList.push_back(invoice);
  saveCurrentInvoiceToJson();
}

void InvoiceManager::saveCurrentInvoiceToJson() {
  QString jsonString = JsonParser::createJsonInvoiceFile(invoicesList);
  FileManager::setTextToJsonFile(pathInvoiceJson, jsonString);
}


bool InvoiceManager::containsInvoiceByDate(Invoice invoice) {
  foreach (Invoice inv, invoicesList) {
      if (inv.date.isSameDate(invoice.date)) return true;
    }
  return false;
}

QList<Invoice> InvoiceManager::getInvoices() {
  return invoicesList;
}
