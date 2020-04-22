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
    void addManager(UserManager userManager);


private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::AddUserDialog *ui;
    UserManager *userManager;
    bool isCorrectValues();
};

#endif // ADDUSERDIALOG_H
