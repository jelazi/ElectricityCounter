/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableView *userTable;
    QLabel *label_2;
    QTableView *invoiceTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *editUserBtn;
    QPushButton *addInvoice;
    QPushButton *btnAddEntry;
    QPushButton *viewResultBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1088, 666);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));

        verticalLayout->addLayout(gridLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout_2->addWidget(label, 0, Qt::AlignHCenter);

        userTable = new QTableView(centralwidget);
        userTable->setObjectName(QString::fromUtf8("userTable"));

        verticalLayout_2->addWidget(userTable);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        invoiceTable = new QTableView(centralwidget);
        invoiceTable->setObjectName(QString::fromUtf8("invoiceTable"));

        verticalLayout_2->addWidget(invoiceTable);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        editUserBtn = new QPushButton(centralwidget);
        editUserBtn->setObjectName(QString::fromUtf8("editUserBtn"));

        horizontalLayout->addWidget(editUserBtn);

        addInvoice = new QPushButton(centralwidget);
        addInvoice->setObjectName(QString::fromUtf8("addInvoice"));

        horizontalLayout->addWidget(addInvoice);

        btnAddEntry = new QPushButton(centralwidget);
        btnAddEntry->setObjectName(QString::fromUtf8("btnAddEntry"));

        horizontalLayout->addWidget(btnAddEntry);

        viewResultBtn = new QPushButton(centralwidget);
        viewResultBtn->setObjectName(QString::fromUtf8("viewResultBtn"));

        horizontalLayout->addWidget(viewResultBtn);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "M\304\233\305\231en\303\255", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Faktury", nullptr));
        editUserBtn->setText(QCoreApplication::translate("MainWindow", "Editace spot\305\231ebitel\305\257", nullptr));
        addInvoice->setText(QCoreApplication::translate("MainWindow", "P\305\231idat fakturu", nullptr));
        btnAddEntry->setText(QCoreApplication::translate("MainWindow", "P\305\231idat m\304\233\305\231en\303\255", nullptr));
        viewResultBtn->setText(QCoreApplication::translate("MainWindow", "Spo\304\215\303\255tat m\304\233s\303\255c", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
