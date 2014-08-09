#-------------------------------------------------
#
# Project created by QtCreator 2011-01-08T10:05:35
#
#-------------------------------------------------

QT += widgets
QT += network
CONFIG += c++11


TARGET = TraceViewerFeeder
TEMPLATE = app
NyxPath=../../../../Nyx

INCLUDEPATH += $${NyxPath}/include
INCLUDEPATH += $${NyxPath}/include/NyxNet
INCLUDEPATH += ../../../TraceViewerConnection/public/OSX
mac:INCLUDEPATH += $${NyxPath}/include/OSX
mac:INCLUDEPATH += $${NyxPath}/include/OSX/NyxNet
mac:LIBS += /System/Library/Frameworks/CoreServices.framework/CoreServices
mac:LIBS += /System/Library/Frameworks/Foundation.framework/Foundation

MOC_DIR = ../MOC
UI_DIR = ../UI

CONFIG(debug, debug|release) {
    mac::PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Debug_64/libNyxBase.a
    mac::PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Debug_64/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L$${NyxPath}/Lib/Qt/Debug_64
    mac:LIBS += -lNyxNet \
        -L$${NyxPath}/Lib/Qt/Debug_64
    mac:LIBS += /usr/lib/libiconv.dylib
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else {
    mac::PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Release_64/libNyxBase.a
    mac::PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Release_64/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L$(NyxPath)/Lib/OSX/Release_64
    mac:LIBS += -lNyxNet \
        -L$(NyxPath)/Lib/OSX/Release_64
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
    ../PlainFeeder.h

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
    ../../../TraceViewerConnection/public/OSX/NyxTraceViewerConnection_Impl.cpp \
    ../PlainFeeder.cpp

FORMS += \
    ../UI/traceviewerfeeder.ui

