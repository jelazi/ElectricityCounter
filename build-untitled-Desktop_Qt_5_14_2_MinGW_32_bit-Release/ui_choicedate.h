/********************************************************************************
** Form generated from reading UI file 'choicedate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEDATE_H
#define UI_CHOICEDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_choiceDate
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QPushButton *okBtn;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *month;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *year;

    void setupUi(QDialog *choiceDate)
    {
        if (choiceDate->objectName().isEmpty())
            choiceDate->setObjectName(QString::fromUtf8("choiceDate"));
        choiceDate->resize(500, 384);
        horizontalLayoutWidget = new QWidget(choiceDate);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(150, 290, 168, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cancelBtn = new QPushButton(horizontalLayoutWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);

        okBtn = new QPushButton(horizontalLayoutWidget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        horizontalLayout->addWidget(okBtn);

        label = new QLabel(choiceDate);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 30, 101, 16));
        verticalLayoutWidget = new QWidget(choiceDate);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 90, 431, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        month = new QComboBox(verticalLayoutWidget);
        month->setObjectName(QString::fromUtf8("month"));

        horizontalLayout_3->addWidget(month);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        year = new QComboBox(verticalLayoutWidget);
        year->setObjectName(QString::fromUtf8("year"));

        horizontalLayout_2->addWidget(year);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(choiceDate);

        QMetaObject::connectSlotsByName(choiceDate);
    } // setupUi

    void retranslateUi(QDialog *choiceDate)
    {
        choiceDate->setWindowTitle(QCoreApplication::translate("choiceDate", "Dialog", nullptr));
        cancelBtn->setText(QCoreApplication::translate("choiceDate", "Zru\305\241it", nullptr));
        okBtn->setText(QCoreApplication::translate("choiceDate", "Ok", nullptr));
        label->setText(QCoreApplication::translate("choiceDate", "Vyberte datum", nullptr));
        label_3->setText(QCoreApplication::translate("choiceDate", "M\304\233s\303\255c", nullptr));
        label_2->setText(QCoreApplication::translate("choiceDate", "Rok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choiceDate: public Ui_choiceDate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICEDATE_H
