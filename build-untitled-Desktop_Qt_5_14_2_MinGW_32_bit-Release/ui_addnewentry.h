/********************************************************************************
** Form generated from reading UI file 'addnewentry.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWENTRY_H
#define UI_ADDNEWENTRY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddNewEntry
{
public:
    QPushButton *okButton;
    QPushButton *cancelButton;
    QComboBox *monthComboBox;
    QLabel *label;
    QComboBox *yearComboBox;
    QLabel *label_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *userLayout;

    void setupUi(QDialog *AddNewEntry)
    {
        if (AddNewEntry->objectName().isEmpty())
            AddNewEntry->setObjectName(QString::fromUtf8("AddNewEntry"));
        AddNewEntry->resize(681, 521);
        okButton = new QPushButton(AddNewEntry);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(130, 440, 80, 22));
        cancelButton = new QPushButton(AddNewEntry);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(260, 440, 80, 22));
        monthComboBox = new QComboBox(AddNewEntry);
        monthComboBox->setObjectName(QString::fromUtf8("monthComboBox"));
        monthComboBox->setGeometry(QRect(150, 20, 73, 22));
        label = new QLabel(AddNewEntry);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 20, 54, 14));
        yearComboBox = new QComboBox(AddNewEntry);
        yearComboBox->setObjectName(QString::fromUtf8("yearComboBox"));
        yearComboBox->setGeometry(QRect(150, 70, 73, 22));
        label_2 = new QLabel(AddNewEntry);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 70, 54, 14));
        verticalLayoutWidget = new QWidget(AddNewEntry);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 150, 651, 231));
        userLayout = new QVBoxLayout(verticalLayoutWidget);
        userLayout->setObjectName(QString::fromUtf8("userLayout"));
        userLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(AddNewEntry);

        QMetaObject::connectSlotsByName(AddNewEntry);
    } // setupUi

    void retranslateUi(QDialog *AddNewEntry)
    {
        AddNewEntry->setWindowTitle(QCoreApplication::translate("AddNewEntry", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("AddNewEntry", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddNewEntry", "Zru\305\241it", nullptr));
        label->setText(QCoreApplication::translate("AddNewEntry", "M\304\233s\303\255c", nullptr));
        label_2->setText(QCoreApplication::translate("AddNewEntry", "Rok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddNewEntry: public Ui_AddNewEntry {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWENTRY_H
