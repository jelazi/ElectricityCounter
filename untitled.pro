QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    addnewentry.cpp \
    adduserdialog.cpp \
    editusers.cpp \
    filemanager.cpp \
    jsonparser.cpp \
    main.cpp \
    mainwindow.cpp \
    mydate.cpp \
    user.cpp \
    usermanager.cpp

HEADERS += \
    addnewentry.h \
    adduserdialog.h \
    editusers.h \
    filemanager.h \
    jsonparser.h \
    mainwindow.h \
    mydate.h \
    structures.h \
    user.h \
    usermanager.h

FORMS += \
    addnewentry.ui \
    adduserdialog.ui \
    editusers.ui \
    mainwindow.ui

TRANSLATIONS += \
    untitled_cs_CZ.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
