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

INCLUDEPATH += $(NYXPATH)/include
INCLUDEPATH += $(NYXPATH)/include/NyxNet
INCLUDEPATH += ../../../TraceViewerConnection/public/Win32
INCLUDEPATH += $(NYXPATH)/include/Win32

LIBS += -lUser32
LIBS += -lws2_32

CONFIG(debug, debug|release) {
    LIBS += -lNyxBase \
        -L$(NYXPATH)/Lib/Windows/$(PLATFORM)/Debug
    LIBS += -lNyxNet \
        -L$(NYXPATH)/Lib/Windows/$(PLATFORM)/Debug
    DESTDIR = ./bin/x86/Debug
    OBJECTS_DIR = ./objs/x86/Debug
    DEFINES += _DEBUG
}
else {
    mac::PRE_TARGETDEPS += $(NYXPATH)/Lib/OSX/Release_64/libNyxBase.a
    mac::PRE_TARGETDEPS += $(NYXPATH)/Lib/OSX/Release_64/libNyxNet.a
    mac:LIBS += -lNyxBase \
        -L$(NYXPATH)/Lib/OSX/Release_64
    mac:LIBS += -lNyxNet \
        -L$(NYXPATH)/Lib/OSX/Release_64
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
    ../../../TraceViewerConnection/public/Win32/NyxTraceViewerConnection.hpp \
    ../DllFeeder.hpp

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
    ../../../TraceViewerConnection/public/Win32/NyxTraceViewerConnection_impl.cpp \
    ../DllFeeder.cpp

