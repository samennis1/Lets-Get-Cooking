QT       += core gui sql
OTHER_FILES += database.sqlite

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasecontrol.cpp \
    databaseexception.cpp \
    databasemanager.cpp \
    global.cpp \
    ingredient.cpp \
    main.cpp \
    mainwindow.cpp \
    recipe.cpp

HEADERS += \
    databasecontrol.h \
    databaseexception.h \
    databasemanager.h \
    global.h \
    ingredient.h \
    mainwindow.h \
    recipe.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
