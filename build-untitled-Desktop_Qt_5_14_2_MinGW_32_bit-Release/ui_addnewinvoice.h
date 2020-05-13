/********************************************************************************
** Form generated from reading UI file 'addnewinvoice.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWINVOICE_H
#define UI_ADDNEWINVOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddNewInvoice
{
public:
    QLabel *dateLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QPushButton *okBtn;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *dataLayout;

    void setupUi(QDialog *AddNewInvoice)
    {
        if (AddNewInvoice->objectName().isEmpty())
            AddNewInvoice->setObjectName(QString::fromUtf8("AddNewInvoice"));
        AddNewInvoice->resize(658, 506);
        dateLabel = new QLabel(AddNewInvoice);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));
        dateLabel->setGeometry(QRect(150, 26, 331, 20));
        horizontalLayoutWidget = new QWidget(AddNewInvoice);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(160, 400, 351, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cancelBtn = new QPushButton(horizontalLayoutWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);

        okBtn = new QPushButton(horizontalLayoutWidget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        horizontalLayout->addWidget(okBtn);

        verticalLayoutWidget = new QWidget(AddNewInvoice);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 80, 521, 271));
        dataLayout = new QVBoxLayout(verticalLayoutWidget);
        dataLayout->setObjectName(QString::fromUtf8("dataLayout"));
        dataLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(AddNewInvoice);

        QMetaObject::connectSlotsByName(AddNewInvoice);
    } // setupUi

    void retranslateUi(QDialog *AddNewInvoice)
    {
        AddNewInvoice->setWindowTitle(QCoreApplication::translate("AddNewInvoice", "Dialog", nullptr));
        dateLabel->setText(QCoreApplication::translate("AddNewInvoice", "TextLabel", nullptr));
        cancelBtn->setText(QCoreApplication::translate("AddNewInvoice", "Zru\305\241it", nullptr));
        okBtn->setText(QCoreApplication::translate("AddNewInvoice", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddNewInvoice: public Ui_AddNewInvoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWINVOICE_H
