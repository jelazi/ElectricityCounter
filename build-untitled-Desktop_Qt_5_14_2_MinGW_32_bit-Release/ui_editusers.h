/********************************************************************************
** Form generated from reading UI file 'editusers.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITUSERS_H
#define UI_EDITUSERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_EditUsers
{
public:
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QPushButton *okButton;
    QTableView *userTable;
    QPushButton *addUserButton;

    void setupUi(QDialog *EditUsers)
    {
        if (EditUsers->objectName().isEmpty())
            EditUsers->setObjectName(QString::fromUtf8("EditUsers"));
        EditUsers->resize(708, 500);
        gridLayout = new QGridLayout(EditUsers);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cancelButton = new QPushButton(EditUsers);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cancelButton, 4, 1, 1, 1);

        okButton = new QPushButton(EditUsers);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout->addWidget(okButton, 3, 1, 1, 1);

        userTable = new QTableView(EditUsers);
        userTable->setObjectName(QString::fromUtf8("userTable"));

        gridLayout->addWidget(userTable, 0, 0, 1, 2);

        addUserButton = new QPushButton(EditUsers);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));

        gridLayout->addWidget(addUserButton, 3, 0, 1, 1);


        retranslateUi(EditUsers);

        QMetaObject::connectSlotsByName(EditUsers);
    } // setupUi

    void retranslateUi(QDialog *EditUsers)
    {
        EditUsers->setWindowTitle(QCoreApplication::translate("EditUsers", "Dialog", nullptr));
        cancelButton->setText(QCoreApplication::translate("EditUsers", "Zru\305\241it", nullptr));
        okButton->setText(QCoreApplication::translate("EditUsers", "Ok", nullptr));
        addUserButton->setText(QCoreApplication::translate("EditUsers", "P\305\231idat u\305\276ivatele", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditUsers: public Ui_EditUsers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITUSERS_H
