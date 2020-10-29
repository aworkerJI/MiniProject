QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoProcessor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        tab01-Movement.cpp \
        tab02-Divide.cpp \
        tab03-Histo.cpp \
        tab04-Detect.cpp \
        tab05-SensorCDS.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

#include(c:/opencv.pri)

INCLUDEPATH += /usr/local/include/opencv4 /usr/arm-linux-gnueabi/include
                                        # /usr/arm-linux-gnueabi/include 라즈베리용
#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_videoio -lopencv_objdetect -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_shape -lopencv_videoio -lopencv_calib3d -lopencv_face -L/usr/local/lib -L/usr/lib64 -L/usr/lib -lwiringPi
                                        # -lwiringPi : 라즈베리용
