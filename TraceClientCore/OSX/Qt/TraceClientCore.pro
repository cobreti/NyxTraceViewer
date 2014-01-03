#-------------------------------------------------
#
# Project created by QtCreator 2013-12-31T21:57:28
#
#-------------------------------------------------

QT       -= gui

TARGET = TraceClientCore
TEMPLATE = lib
CONFIG += staticlib
NyxPath = ../../../../Nyx
DEFINES += STDCONSTRUCT


INCLUDEPATH += ../../include
INCLUDEPATH += $${NyxPath}/include
INCLUDEPATH += $${NyxPath}/include/OSX
INCLUDEPATH += $${NyxPath}/include/NyxNet
INCLUDEPATH += $${NyxPath}/include/OSX/NyxNet

CONFIG(debug, debug | release) {
    OBJECTS_DIR = ./Debug_64
    DESTDIR = ../../../Lib/Qt/Debug_64
}

CONFIG(release, debug | release) {
    OBJECTS_DIR = ./Release_64
    DESTDIR = ../../../Lib/Qt/Release_64
}

HEADERS += \
    ../../include/ChannelsMgr.hpp \
    ../../include/MultiViewTracesIterator.hpp \
    ../../include/PipeTraceFeeder.hpp \
    ../../include/PoolsUpdateClock.hpp \
    ../../include/RepositoryObserver.hpp \
    ../../include/RepositoryTraceInserter.hpp \
    ../../include/TcpModule.hpp \
    ../../include/TcpNxTracesReceiver.hpp \
    ../../include/TcpNxTracesReceiversSvr.hpp \
    ../../include/TcpTracesReceiversListener.hpp \
    ../../include/TcpTracesReceiversSvr.hpp \
    ../../include/TcpTracesReceiversTable.hpp \
    ../../include/TcpTxtTracesReceiver.hpp \
    ../../include/TcpTxtTracesReceiversSvr.hpp \
    ../../include/TextTraceHandler.hpp \
    ../../include/TimeStamp.hpp \
    ../../include/TraceChannel.hpp \
    ../../include/TraceChannels.hpp \
    ../../include/TraceClientCoreModule.hpp \
    ../../include/TraceData.hpp \
    ../../include/TraceDataRepository.hpp \
    ../../include/TraceFeeder.hpp \
    ../../include/TraceInserter.hpp \
    ../../include/TraceNxStreamReader.hpp \
    ../../include/TracesGroup.hpp \
    ../../include/TracesGroupMgr.hpp \
    ../../include/TracesIterator.hpp \
    ../../include/TracesList.hpp \
    ../../include/TracesPool.hpp \
    ../../include/TracesPoolCollection.hpp \
    ../../include/TracesReceiverProtocol_WebSocket.hpp \
    ../../include/TracesReceiverProtocol.hpp \
    ../../include/TracesView.hpp \
    ../../include/TracesViewNotificationsListener.hpp \
    ../../include/TracesViewRepoObserver.hpp \
    ../../include/DataStruct/PoolsList.hpp

SOURCES += \
    ../../sources/ChannelsMgr.cpp \
    ../../sources/MultiViewTracesIterator.cpp \
    ../../sources/PipeTraceFeeder.cpp \
    ../../sources/PoolsList.cpp \
    ../../sources/PoolsUpdateClock.cpp \
    ../../sources/RepositoryObserver.cpp \
    ../../sources/RepositoryTraceInserter.cpp \
    ../../sources/TcpModule.cpp \
    ../../sources/TcpNxTracesReceiver.cpp \
    ../../sources/TcpNxTracesReceiversSvr.cpp \
    ../../sources/TcpTracesReceiversSvr.cpp \
    ../../sources/TcpTracesReceiversTable.cpp \
    ../../sources/TcpTxtTracesReceiver.cpp \
    ../../sources/TcpTxtTracesReceiversSvr.cpp \
    ../../sources/TextTraceHandler.cpp \
    ../../sources/TimeStamp.cpp \
    ../../sources/TraceChannel.cpp \
    ../../sources/TraceChannels.cpp \
    ../../sources/TraceClientCoreModule.cpp \
    ../../sources/TraceData.cpp \
    ../../sources/TraceDataRepository.cpp \
    ../../sources/TraceFeeder.cpp \
    ../../sources/TraceNxStreamReader.cpp \
    ../../sources/TracesGroup.cpp \
    ../../sources/TracesGroupMgr.cpp \
    ../../sources/TracesIterator.cpp \
    ../../sources/TracesList.cpp \
    ../../sources/TracesPool.cpp \
    ../../sources/TracesPoolCollection.cpp \
    ../../sources/TracesReceiverProtocol_WebSocket.cpp \
    ../../sources/TracesReceiverProtocol.cpp \
    ../../sources/TracesView.cpp \
    ../../sources/TracesViewRepoObserver.cpp
