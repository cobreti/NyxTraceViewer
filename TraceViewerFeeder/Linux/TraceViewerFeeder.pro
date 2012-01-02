#-------------------------------------------------
#
# Project created by QtCreator 2011-01-08T10:05:35
#
#-------------------------------------------------

QT       += core gui

TARGET = TraceViewerFeeder
TEMPLATE = app


FORMS += \
    ../traceviewerfeeder.ui

INCLUDEPATH += ../../NyxLibs/include
INCLUDEPATH += ../../NyxLibs/include/NyxNet
INCLUDEPATH += ../../NyxLibs/include/Linux

CONFIG(debug, debug|release) {
    LIBS += -lNyxBase \
        -L../../NyxLibs/Lib/Linux/Debug
    LIBS += -lNyxNet \
        -L../../NyxLibs/Lib/Linux/Debug
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else {
    LIBS += -lNyxBase \
        -L../../NyxLibs/Lib/Linux/Release
    LIBS += -lNyxNet \
        -L../../NyxLibs/Lib/Linux/Release
    DESTDIR = ./Release
    OBJECTS_DIR = ./Release
}

HEADERS += \
    ../TraceViewerFeeder.h \
    ../NyxFeeder.hpp \
    ../FeederSettings.hpp \
    ../FeederEntryWidgetItem.hpp \
    ../FeederEntry.hpp \
    ../FeederBase.hpp \
    ../FeederSource.hpp \
    ../FeederSource_UserText.hpp \
    ../FeederSource_TextFile.hpp

SOURCES += \
    ../TraceViewerFeeder.cpp \
    ../NyxFeeder.cpp \
    ../main.cpp \
    ../FeederSettings.cpp \
    ../FeederEntryWidgetItem.cpp \
    ../FeederEntry.cpp \
    ../FeederBase.cpp \
    ../FeederSource.cpp \
    ../FeederSource_UserText.cpp \
    ../FeederSource_TextFile.cpp
