/********************************************************************************
** Form generated from reading UI file 'viewresult.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWRESULT_H
#define UI_VIEWRESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ViewResult
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *entriesTable;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QTableView *invoiceTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnCancel;
    QPushButton *btnCreatePdf;
    QPushButton *btnSendMail;

    void setupUi(QDialog *ViewResult)
    {
        if (ViewResult->objectName().isEmpty())
            ViewResult->setObjectName(QString::fromUtf8("ViewResult"));
        ViewResult->resize(1030, 702);
        verticalLayout_2 = new QVBoxLayout(ViewResult);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ViewResult);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        entriesTable = new QTableView(ViewResult);
        entriesTable->setObjectName(QString::fromUtf8("entriesTable"));

        verticalLayout->addWidget(entriesTable);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(ViewResult);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        invoiceTable = new QTableView(ViewResult);
        invoiceTable->setObjectName(QString::fromUtf8("invoiceTable"));

        verticalLayout_3->addWidget(invoiceTable);


        verticalLayout_2->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnCancel = new QPushButton(ViewResult);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);

        btnCreatePdf = new QPushButton(ViewResult);
        btnCreatePdf->setObjectName(QString::fromUtf8("btnCreatePdf"));

        horizontalLayout->addWidget(btnCreatePdf);

        btnSendMail = new QPushButton(ViewResult);
        btnSendMail->setObjectName(QString::fromUtf8("btnSendMail"));

        horizontalLayout->addWidget(btnSendMail);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ViewResult);

        QMetaObject::connectSlotsByName(ViewResult);
    } // setupUi

    void retranslateUi(QDialog *ViewResult)
    {
        ViewResult->setWindowTitle(QCoreApplication::translate("ViewResult", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ViewResult", "M\304\233\305\231en\303\255", nullptr));
        label_2->setText(QCoreApplication::translate("ViewResult", "Faktura", nullptr));
        btnCancel->setText(QCoreApplication::translate("ViewResult", "Storno", nullptr));
        btnCreatePdf->setText(QCoreApplication::translate("ViewResult", "Vytvo\305\231it PDF", nullptr));
        btnSendMail->setText(QCoreApplication::translate("ViewResult", "Poslat mail", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewResult: public Ui_ViewResult {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWRESULT_H
