/********************************************************************************
** Form generated from reading UI file 'adduserdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSERDIALOG_H
#define UI_ADDUSERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddUserDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *nameLineEdit;
    QLabel *label_2;
    QDoubleSpinBox *spinNT;
    QLabel *label_3;
    QDoubleSpinBox *spinVT;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddUserDialog)
    {
        if (AddUserDialog->objectName().isEmpty())
            AddUserDialog->setObjectName(QString::fromUtf8("AddUserDialog"));
        AddUserDialog->resize(400, 300);
        gridLayout = new QGridLayout(AddUserDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(AddUserDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 10));

        verticalLayout->addWidget(label);

        nameLineEdit = new QLineEdit(AddUserDialog);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        verticalLayout->addWidget(nameLineEdit);

        label_2 = new QLabel(AddUserDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        spinNT = new QDoubleSpinBox(AddUserDialog);
        spinNT->setObjectName(QString::fromUtf8("spinNT"));
        spinNT->setDecimals(2);
        spinNT->setMaximum(999999999.990000009536743);
        spinNT->setSingleStep(1.000000000000000);

        verticalLayout->addWidget(spinNT);

        label_3 = new QLabel(AddUserDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        spinVT = new QDoubleSpinBox(AddUserDialog);
        spinVT->setObjectName(QString::fromUtf8("spinVT"));
        spinVT->setMaximum(999999999.990000009536743);

        verticalLayout->addWidget(spinVT);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        okButton = new QPushButton(AddUserDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(AddUserDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(AddUserDialog);

        QMetaObject::connectSlotsByName(AddUserDialog);
    } // setupUi

    void retranslateUi(QDialog *AddUserDialog)
    {
        AddUserDialog->setWindowTitle(QCoreApplication::translate("AddUserDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddUserDialog", "Jm\303\251no u\305\276ivatele:", nullptr));
        label_2->setText(QCoreApplication::translate("AddUserDialog", "Po\304\215\303\241te\304\215n\303\255 stav NT:", nullptr));
        label_3->setText(QCoreApplication::translate("AddUserDialog", "Po\304\215\303\241te\304\215n\303\255 stav VT:", nullptr));
        okButton->setText(QCoreApplication::translate("AddUserDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddUserDialog", "Zru\305\241it", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddUserDialog: public Ui_AddUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSERDIALOG_H
