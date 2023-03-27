QT       += core gui sql
OTHER_FILES += database.sqlite

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ingredientslist.cpp \
    card.cpp \
    databasecontrol.cpp \
    databasemanager.cpp \
    global.cpp \
    ingredient.cpp \
    main.cpp \
    mainwindow.cpp \
    newrecipe.cpp \
    recipe.cpp

HEADERS += \
    Ingredientslist.h \
    card.h \
    databasecontrol.h \
    databaseexception.h \
    databasemanager.h \
    global.h \
    ingredient.h \
    mainwindow.h \
    newrecipe.h \
    recipe.h

FORMS += \
    card.ui \
    mainwindow.ui \
    newrecipe.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Downloads/cookbook.png \
    cookbook.png
