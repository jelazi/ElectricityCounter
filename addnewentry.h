#ifndef ADDNEWENTRY_H
#define ADDNEWENTRY_H

#include <QDialog>
#include "mydate.h"
#include <QMessageBox>

namespace Ui {
class AddNewEntry;
}

class AddNewEntry : public QDialog {
    Q_OBJECT

public:
    explicit AddNewEntry(QWidget *parent = nullptr);
    ~AddNewEntry();

private slots:
    void on_cancelButton_clicked();
    void fillUsers();
    void on_okButton_clicked();
    void getValues();

private:
    Ui::AddNewEntry *ui;
    void fillYearsList();
};

#endif // ADDNEWENTRY_H
