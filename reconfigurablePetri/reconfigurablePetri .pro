#-------------------------------------------------
#
# Project created by QtCreator 2022-09-16T08:37:40
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reconfigurablePetri
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
    arc.cpp \
    arcedgeselectionrectangle.cpp \
    command.cpp \
    component.cpp \
    graphedge.cpp \
    graphgenerator.cpp \
    graphicsedittab.cpp \
    graphnode.cpp \
    graphvisualizer.cpp \
        main.cpp \
        mainwindow.cpp \
    place.cpp \
    placeeditdialog.cpp \
    ptnet.cpp \
    ptnscene.cpp \
    sceneselectionrectangle.cpp \
    tabwidget.cpp \
    dockwidget.cpp \
    transition.cpp \
    transitioneditdialog.cpp \
    undostack.cpp \
    arceditdialog.cpp \
    petritabwidget.cpp \
    xmlwriter.cpp \
    xmlparser.cpp \
    messagehandler.cpp \
    editrulelibrary.cpp \
    componentcontroller.cpp

HEADERS += \
    arc.h \
    arcedgeselectionrectangle.h \
    command.h \
    component.h \
    defs.h \
    graphedge.h \
    graphgenerator.h \
    graphicsedittab.h \
    graphnode.h \
    graphvisualizer.h \
        mainwindow.h \
    place.h \
    placeeditdialog.h \
    ptnet.h \
    ptnscene.h \
    sceneselectionrectangle.h \
    tabwidget.h \
    dockwidget.h \
    transition.h \
    transitioneditdialog.h \
    undostack.h \
    arceditdialog.h \
    petritabwidget.h \
    xmlwriter.h \
    xmlparser.h \
    messagehandler.h \
    editrulelibrary.h \
    componentcontroller.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS += graphicsedittab.ui \
    editrulelibrary.ui
