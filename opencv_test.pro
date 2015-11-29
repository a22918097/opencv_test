#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T16:08:35
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    topview.cpp \
    stereo_vision.cpp \
    sensorbase.cpp \
    sensorinfo.cpp

HEADERS  += mainwindow.h \
    topview.h \
    stereo_vision.h \
    sensorbase.h \
    sensorinfo.h

FORMS    += mainwindow.ui

OpenCV_Lib = $$quote(G:\opencv\build\x86\vc11\lib)

CAN_Lib = $$quote(C:\Program Files (x86)\Kvaser\Canlib\Lib\MS)

INCLUDEPATH +=  $$quote(C:\Program Files (x86)\Kvaser\Canlib\INC)   # CANLib
INCLUDEPATH +=  $$quote(G:\opencv\build\include)

    Release: LIBS +=    $$OpenCV_Lib/opencv_ts300.lib\
                        $$OpenCV_Lib/opencv_world300.lib\


    Debug: LIBS +=      $$OpenCV_Lib/opencv_ts300d.lib\
                        $$OpenCV_Lib/opencv_world300d.lib\

