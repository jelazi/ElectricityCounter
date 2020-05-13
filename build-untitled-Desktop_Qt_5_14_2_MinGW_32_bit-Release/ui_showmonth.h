/********************************************************************************
** Form generated from reading UI file 'showmonth.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMONTH_H
#define UI_SHOWMONTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_showMonth
{
public:

    void setupUi(QDialog *showMonth)
    {
        if (showMonth->objectName().isEmpty())
            showMonth->setObjectName(QString::fromUtf8("showMonth"));
        showMonth->resize(530, 416);

        retranslateUi(showMonth);

        QMetaObject::connectSlotsByName(showMonth);
    } // setupUi

    void retranslateUi(QDialog *showMonth)
    {
        showMonth->setWindowTitle(QCoreApplication::translate("showMonth", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class showMonth: public Ui_showMonth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMONTH_H
