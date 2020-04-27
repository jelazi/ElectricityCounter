#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include "usermanager.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();


private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::AddUserDialog *ui;
    bool isCorrectValues();
};

#endif // ADDUSERDIALOG_H
