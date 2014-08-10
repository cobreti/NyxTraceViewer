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

macx {
    INCLUDEPATH += $${NyxPath}/include/OSX
    INCLUDEPATH += $${NyxPath}/include/OSX/NyxNet
    LIBS += /System/Library/Frameworks/CoreServices.framework/CoreServices
    LIBS += /System/Library/Frameworks/Foundation.framework/Foundation
}

win32 {
    INCLUDEPATH += $${NyxPath}/include/Win32
    INCLUDEPATH += $${NyxPath}/include/Win32/NyxNet
}

MOC_DIR = ../MOC
UI_DIR = ../UI

CONFIG(debug, debug|release) {

    macx {
            PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Debug_64/libNyxBase.a
            PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Debug_64/libNyxNet.a
            LIBS += -lNyxBase \
            -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lNyxNet \
            -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += /usr/lib/libiconv.dylib
    }
    win32 {
            LIBS += -lNyxBase \
                -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lNyxNet \
                -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lNyxWebSvr \
                -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lssleay32 \
                -L$${NyxPath}/Lib/Windows/x64/openssl
            LIBS += -llibeay32 \
                -L$${NyxPath}/Lib/Windows/x64/openssl
    }
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else {
    macx {
        PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Release_64/libNyxBase.a
        PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Release_64/libNyxNet.a
        LIBS += -lNyxBase \
        -L$(NyxPath)/Lib/OSX/Release_64
        LIBS += -lNyxNet \
        -L$(NyxPath)/Lib/OSX/Release_64
    }

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

