#ifndef EDITUSERS_H
#define EDITUSERS_H

#include <QDialog>
#include "QStandardItem"
#include "QDebug"
#include "adduserdialog.h"

namespace Ui {
class EditUsers;
}

class EditUsers : public QDialog
{
    Q_OBJECT

public:
    explicit EditUsers(QWidget *parent = nullptr);
    ~EditUsers();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_addUserButton_clicked();

    void on_userTable_doubleClicked(const QModelIndex &index);

private:
    Ui::EditUsers *ui;
    void reloadUserTable();
    void createUserTable();

    QStandardItemModel model;

    QStringList horizontalHeader;
    QStringList verticalHeader;
    int countDigits(double num);
};

#endif // EDITUSERS_H
