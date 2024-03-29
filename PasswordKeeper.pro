QT       += core gui sql network

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
    GUI/dbconfigdialog.cpp \
    GUI/generatortab.cpp \
    GUI/insertiondialog.cpp \
    GUI/loadingdialog.cpp \
    GUI/logindialog.cpp \
    GUI/tabletab.cpp \
    Handlers/passwordgenerator.cpp \
    Handlers/usercontroller.cpp \
    Single/password.cpp \
    Single/user.cpp \
    Verifier/databaseverifier.cpp \
    keygrabaction.cpp \
    main.cpp \
    mainwindow.cpp \
    private/keygrabactionobject.cpp \
    table/proxymodel.cpp \
    table/tabledelegate.cpp \
    table/tablemodel.cpp \
    table/tableview.cpp

HEADERS += \
    GUI/dbconfigdialog.h \
    GUI/generatortab.h \
    GUI/insertiondialog.h \
    GUI/loadingdialog.h \
    GUI/logindialog.h \
    GUI/tabletab.h \
    Handlers/passwordgenerator.h \
    Handlers/usercontroller.h \
    Single/ObjectTypes.h \
    Single/password.h \
    Single/user.h \
    Verifier/databaseverifier.h \
    config/config.h \
    keygrabaction.h \
    mainwindow.h \
    private/keygrabactionobject.h \
    table/proxymodel.h \
    table/tabledelegate.h \
    table/tablemodel.h \
    table/tableview.h

FORMS += \
    GUI/dbconfigdialog.ui \
    GUI/generatortab.ui \
    GUI/insertiondialog.ui \
    GUI/loadingdialog.ui \
    GUI/logindialog.ui \
    GUI/tabletab.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    backgrounds.qrc \
    icons.qrc \
    style.qrc

 RC_FILE = $$PWD/appRC.rc
