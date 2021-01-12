#ifndef ADDNEWENTRY_H
#define ADDNEWENTRY_H

#include <QDialog>
#include "mydate.h"
#include <QMessageBox>
#include "structures.h"

namespace Ui {
class AddNewEntry;
}

class EntryWindow : public QDialog {
    Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();
    void fillDateLabel(MyDate *myDate);

    void setIsEditable(bool value);

private slots:
    void on_cancelButton_clicked();
    void fillUsers();
    void on_okButton_clicked();
    TypeMessageError getValues();



signals:

    void signalChangeData();

private:
    Ui::AddNewEntry *ui;
    bool isEditable = false;
    QList <Entry> entries;
    void fillDataForEdit();
};

#endif // ADDNEWENTRY_H
