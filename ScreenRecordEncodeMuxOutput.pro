#-------------------------------------------------
#
# Project created by QtCreator 2024-05-06T13:05:03
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScreenRecordEncodeMuxOutput
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
        avrecord.cpp \
        main.cpp \
        widget.cpp

HEADERS += \
        avrecord.h \
        widget.h

FORMS += \
        widget.ui

win32{
INCLUDEPATH += $$PWD/ffmpeg-4.3.1-win32-dev\include
LIBS += $$PWD/ffmpeg-4.3.1-win32-dev\lib\avformat.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\avcodec.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\avdevice.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\avfilter.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\avutil.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\postproc.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\swresample.lib   \
$$PWD/ffmpeg-4.3.1-win32-dev\lib\swscale.lib
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
