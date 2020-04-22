#ifndef EDITUSERS_H
#define EDITUSERS_H

#include <QDialog>
#include "QStandardItem"
#include "QDebug"

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

private:
    Ui::EditUsers *ui;
    void reloadUserTable();

    QStandardItemModel model;

    QModelIndex modelIndex;

    QStandardItem *item00;
    QStandardItem *item01;
    QStandardItem *item02;
    QStandardItem *item03;
    QStandardItem *item10;
    QStandardItem *item11;
    QStandardItem *item12;
    QStandardItem *item13;

    QStringList horizontalHeader;
    QStringList verticalHeader;
};

#endif // EDITUSERS_H
