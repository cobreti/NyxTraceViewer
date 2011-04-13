#-------------------------------------------------
#
# Project created by QtCreator 2011-01-08T10:05:35
#
#-------------------------------------------------

QT       += core gui

TARGET = TraceViewerFeeder
TEMPLATE = app

HEADERS += \
    ../NyxFeeder.hpp \
    ../FeederSettings.hpp \
    ../FeederEntryWidgetItem.hpp \
    ../FeederEntry.hpp \
    ../FeederBase.hpp \
    ../TraceViewerFeeder.h

SOURCES += \
    ../NyxFeeder.cpp \
    ../main.cpp \
    ../FeederSettings.cpp \
    ../FeederEntryWidgetItem.cpp \
    ../FeederEntry.cpp \
    ../FeederBase.cpp \
    ../TraceViewerFeeder.cpp

FORMS += \
    ../traceviewerfeeder.ui

INCLUDEPATH += ../../../NyxLibs/NyxBase/include
INCLUDEPATH += ../../../NyxLibs/NyxNet/include
mac:INCLUDEPATH += ../../../NyxLibs/NyxBase/include/OSX
mac:LIBS += /System/Library/Frameworks/CoreServices.framework/CoreServices
mac:CONFIG += x86
mac:CONFIG -= x86_64

CONFIG(debug, debug|release) {
    mac::PRE_TARGETDEPS += ../../../NyxLibs/NyxBase/lib/OSX/Debug_32/libNyxBase.a
    mac::PRE_TARGETDEPS += ../../../NyxLibs/NyxNet/lib/OSX/Debug_32/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L../../../NyxLibs/NyxBase/lib/OSX/Debug_32
    mac:LIBS += -lNyxNet \
        -L../../../NyxLibs/NyxNet/lib/OSX/Debug_32
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else {
    mac::PRE_TARGETDEPS += ../../../NyxLibs/NyxBase/lib/OSX/Release_32/libNyxBase.a
    mac::PRE_TARGETDEPS += ../../../NyxLibs/NyxNet/lib/OSX/Release_32/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L../../../NyxLibs/NyxBase/lib/OSX/Release_32
    mac:LIBS += -lNyxNet \
        -L../../../NyxLibs/NyxNet/lib/OSX/Release_32
    DESTDIR = ./Release
    OBJECTS_DIR = ./Release
}
