#-------------------------------------------------
#
# Project created by QtCreator 2022-09-16T08:37:40
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    ODESolver/fparser.cc \
    ODESolver/fpoptimizer.cc \
    ODESolver/ODEsolver.cpp \
    arc.cpp \
    arcedgeselectionrectangle.cpp \
    arceditdialog.cpp \
    command.cpp \
    component.cpp \
    componentcontroller.cpp \
    dockwidget.cpp \
    editrulelibrary.cpp \
    graphedge.cpp \
    graphgenerator.cpp \
    graphicsedittab.cpp \
    graphnode.cpp \
    graphvisualizer.cpp \
    main.cpp \
    mainwindow.cpp \
    messagehandler.cpp \
    petritabwidget.cpp \
    place.cpp \
    placeeditdialog.cpp \
    ptnet.cpp \
    ptnscene.cpp \
    qcustomplot.cpp \
    sceneselectionrectangle.cpp \
    simulation/calculate.cpp \
    simulation/editlineproperty.cpp \
    simulation/editmanyproperty.cpp \
    simulation/editplotproperty.cpp \
    simulation/plot.cpp \
    simulation/savediffcsv.cpp \
    simulation/tabular.cpp \
    tabwidget.cpp \
    transition.cpp \
    transitioneditdialog.cpp \
    undostack.cpp \
    xmlparser.cpp \
    xmlwriter.cpp


HEADERS += \
    ODESolver/fparser.hh \
    ODESolver/fparser_gmpint.hh \
    ODESolver/fparser_mpfr.hh \
    ODESolver/fpaux.hh \
    ODESolver/fpconfig.hh \
    ODESolver/ODEsolver.h \
    ODESolver/fptypes.hh \
    arc.h \
    arcedgeselectionrectangle.h \
    arceditdialog.h \
    command.h \
    component.h \
    componentcontroller.h \
    defs.h \
    dockwidget.h \
    editrulelibrary.h \
    graphedge.h \
    graphgenerator.h \
    graphicsedittab.h \
    graphnode.h \
    graphvisualizer.h \
    mainwindow.h \
    messagehandler.h \
    petritabwidget.h \
    place.h \
    placeeditdialog.h \
    ptnet.h \
    ptnscene.h \
    qcustomplot.h \
    sceneselectionrectangle.h \
    simulation/calculate.h \
    simulation/editlineproperty.h \
    simulation/editmanyproperty.h \
    simulation/editplotproperty.h \
    simulation/plot.h \
    simulation/savediffcsv.h \
    simulation/tabular.h \
    tabwidget.h \
    transition.h \
    transitioneditdialog.h \
    undostack.h \
    xmlparser.h \
    xmlwriter.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS += graphicsedittab.ui \
    editrulelibrary.ui \
    simulation/editlineproperty.ui \
    simulation/editmanyproperty.ui \
    simulation/editplotproperty.ui \
    simulation/plot.ui \
    simulation/savediffcsv.ui \
    simulation/tabular.ui
