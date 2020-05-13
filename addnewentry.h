#ifndef ADDNEWENTRY_H
#define ADDNEWENTRY_H

#include <QDialog>
#include "mydate.h"
#include <QMessageBox>
#include "structures.h"

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
    TypeMessageError getValues();

    void on_monthComboBox_currentIndexChanged(int index);

    void on_yearComboBox_currentIndexChanged(int index);


signals:

    void signalChangeData();

private:
    Ui::AddNewEntry *ui;
    void fillYearsList();
    QList <Entry> entries;
};

#endif // ADDNEWENTRY_H
