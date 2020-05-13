#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QStandardItem"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_editUserBtn_clicked();

    void on_btnAddEntry_clicked();


    void on_addInvoice_clicked();

    void on_viewResultBtn_clicked();

    void slotChangeData();

  private:
    Ui::MainWindow *ui;
    void createTables();
    void reloadUserTable();
    void reloadInvoiceTable();
    QStandardItemModel modelMainUser;
    QStringList horizontalHeaderUser;
    QStringList verticalHeaderUser;
    QStandardItemModel modelMainInvoice;
    QStringList horizontalHeaderInvoice;
    QStringList verticalHeaderInvoice;
    void fillDataUserTable(User user, int ind);
    void fillDataUserEntry (Entry entry, int ind);
};
#endif // MAINWINDOW_H
