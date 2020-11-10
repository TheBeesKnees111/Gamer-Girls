
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Admin.cpp \
    Database.cpp \
    DisplayInfo.cpp \
    Login.cpp \
    Souvenir.cpp \
    SouvenirAndTrip.cpp \
    Stadium.cpp \
    Team.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Admin.h \
    Database.h \
    DisplayInfo.h \
    Login.h \
    Souvenir.h \
    SouvenirAndTrip.h \
    Stadium.h \
    Team.h \
    mainwindow.h

FORMS += \
    Admin.ui \
    DisplayInfo.ui \
    Login.ui \
    SouvenirAndTrip.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    BackgroundImages.qrc \
    db.qrc
