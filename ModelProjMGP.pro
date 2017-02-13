#-------------------------------------------------
#
# Project created by QtCreator 2014-09-30T03:12:39
#
#-------------------------------------------------

QT       += core gui serialport
CONFIG    +=qwt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalFmiProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MDate.cpp \
    MPotential.cpp \
    MTime.cpp \
    RawData.cpp \
    RawDataLine.cpp \
    DataLine.cpp \
    GeographicValue.cpp \
    InitialTypes.cpp \
    settingsdialog.cpp \
    fmidelegate.cpp \
    finaldata.cpp \
    graphikwindow.cpp \
    potentialgraphikwindow.cpp \
    helpmenu.cpp

HEADERS  += mainwindow.h \
    MDate.h \
    MPotential.h \
    MTime.h \
    RawData.h \
    RawDataLine.h \
    DataLine.h \
    ErrorClasses.h \
    GeographicValue.h \
    InitialTypes.h \
    settingsdialog.h \
    fmidelegate.h \
    finaldata.h \
    graphikwindow.h \
    potentialgraphikwindow.h \
    helpmenu.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    graphikwindow.ui \
    potentialgraphikwindow.ui

RESOURCES += \
    iconsToProject.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/lib/ -lqwt

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

OTHER_FILES +=
