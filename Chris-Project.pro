QT       += core gui sql
OTHER_FILES += database.sqlite

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ingredientslist.cpp \
    about.cpp \
    card.cpp \
    databasecontrol.cpp \
    databasemanager.cpp \
    ingredient.cpp \
    main.cpp \
    mainwindow.cpp \
    newrecipe.cpp \
    recipe.cpp \
    review.cpp \
    viewrecipe.cpp

HEADERS += \
    Ingredientslist.h \
    about.h \
    card.h \
    databasecontrol.h \
    databaseexception.h \
    databasemanager.h \
    global.h \
    ingredient.h \
    mainexception.h \
    mainwindow.h \
    newrecipe.h \
    recipe.h \
    review.h \
    viewrecipe.h

FORMS += \
    about.ui \
    card.ui \
    mainwindow.ui \
    newrecipe.ui \
    review.ui \
    viewrecipe.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += logo.png

RESOURCES += \
    resources.qrc
