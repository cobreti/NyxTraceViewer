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

INCLUDEPATH += ../../../NyxLibs/include
INCLUDEPATH += ../../../NyxLibs/include/NyxNet
INCLUDEPATH += ../TraceClientLink_public
mac:INCLUDEPATH += ../../../NyxLibs/include/OSX
mac:LIBS += /System/Library/Frameworks/CoreServices.framework/CoreServices
mac:LIBS += /System/Library/Frameworks/Foundation.framework/Foundation

CONFIG(debug, debug|release) {
    mac::PRE_TARGETDEPS += ../../../NyxLibs/lib/OSX/Debug_Universal_32_64/libNyxBase.a
    mac::PRE_TARGETDEPS += ../../../NyxLibs/lib/OSX/Debug_Universal_32_64/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L../../../NyxLibs/lib/OSX/Debug_Universal_32_64
    mac:LIBS += -lNyxNet \
        -L../../../NyxLibs/lib/OSX/Debug_Universal_32_64
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else {
    mac::PRE_TARGETDEPS += ../../../NyxLibs/lib/OSX/Release_Universal_32_64/libNyxBase.a
    mac::PRE_TARGETDEPS += ../../../NyxLibs/lib/OSX/Release_Universal_32_64/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L../../../NyxLibs/lib/OSX/Release_Universal_32_64
    mac:LIBS += -lNyxNet \
        -L../../../NyxLibs/lib/OSX/Release_Universal_32_64
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
    ../FeederSource_TextFile.hpp \
    ../ExternalFeeder.hpp \
    ../../../TraceClientLink/public/OSX/TraceClientLink.hpp

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
    ../FeederSource_TextFile.cpp \
    ../ExternalFeeder.cpp \
    ../TraceClientLink_public/TraceClientLink_impl.cpp

