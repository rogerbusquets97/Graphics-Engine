#-------------------------------------------------
#
# Project created by QtCreator 2019-02-15T12:51:33
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myopenglwidget.cpp \
    circlewidget.cpp \
    gameobject.cpp \
    gameobjectwidget.cpp \
    scene.cpp \
    hierarchy_widget.cpp \
    inspector.cpp \
    component.cpp \
    componentshape.cpp \
    shapewidget.cpp \
    componentshapewidget.cpp \
    shapecomponentwidget.cpp \
    transformcomponentwidget.cpp

HEADERS += \
        mainwindow.h \
    myopenglwidget.h \
    circlewidget.h \
    gameobject.h \
    component.h \
    gameobjectwidget.h \
    scene.h \
    hierarchy_widget.h \
    inspector.h \
    ComponentShape.h \
    shapewidget.h \
    componentshapewidget.h \
    shapecomponentwidget.h \
    transformcomponentwidget.h

FORMS += \
        mainwindow.ui \
    rendering.ui \
    hierarchy_widget.ui \
    shapecomponentwidget.ui \
    transformcomponentwidget.ui
QT      += opengl

CONFIG += console

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
