QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = icons8-electricity-80.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adduserdialog.cpp \
    choicedate.cpp \
    editusers.cpp \
    entrywindow.cpp \
    filemanager.cpp \
    invoice.cpp \
    invoicemanager.cpp \
    invoicewindow.cpp \
    jsonparser.cpp \
    main.cpp \
    mainwindow.cpp \
    mydate.cpp \
    pdfcreator.cpp \
    showmonth.cpp \
    user.cpp \
    usermanager.cpp \
    viewresult.cpp

HEADERS += \
    adduserdialog.h \
    choicedate.h \
    editusers.h \
    entrywindow.h \
    filemanager.h \
    invoice.h \
    invoicemanager.h \
    invoicewindow.h \
    jsonparser.h \
    mainwindow.h \
    mydate.h \
    pdfcreator.h \
    showmonth.h \
    structures.h \
    user.h \
    usermanager.h \
    viewresult.h

FORMS += \
    adduserdialog.ui \
    choicedate.ui \
    editusers.ui \
    entrywindow.ui \
    invoicewindow.ui \
    mainwindow.ui \
    showmonth.ui \
    viewresult.ui

TRANSLATIONS += \
    untitled_cs_CZ.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    32px-Symbol_OK.svg.png

RESOURCES += \
    images.qrc

