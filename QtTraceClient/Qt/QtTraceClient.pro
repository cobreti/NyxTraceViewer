# -------------------------------------------------
# Project created by QtCreator 2010-02-12T21:15:19
# -------------------------------------------------
QT += xml
QT += widgets
QT += network
QT += script

TARGET = NyxTraceViewer
TEMPLATE = app
NyxPath=../../../Nyx
DEFINES += STDCONSTRUCT
SOURCES += ../Sources/TracesView.cpp \
    ../Sources/main.cpp \
    ../Sources/Dialogs/NewViewDlg.cpp \
    ../Sources/Dialogs/NewPoolDlg.cpp \
    ../Sources/Dialogs/NewDocumentDlg.cpp \
    ../Sources/StatusUpdaters/UISensorsFactory.cpp \
    ../Sources/StatusUpdaters/UISensorsCollection.cpp \
    ../Sources/StatusUpdaters/UISensor.cpp \
    ../Sources/StatusUpdaters/StatusUpdater.cpp \
    ../Sources/MainWindow/PoolTreeItem.cpp \
    ../Sources/View/DrawViewItemState.cpp \
    ../Sources/View/ViewItemSettings.cpp \
    ../Sources/View/ViewItemMargins.cpp \
    ../Sources/View/ViewColumnsSettings.cpp \
    ../Sources/View/ViewColumnsOrder.cpp \
    ../Sources/View/ViewColumnSettings.cpp \
    ../Sources/View/ViewSettings.cpp \
    ../Sources/View/ViewItemsSettings.cpp \
    ../Sources/MainWindow/ViewPage.cpp \
    ../Sources/MainWindow/PipesMgntPage.cpp \
    ../Sources/View/ViewHeader.cpp \
    ../Sources/TraceClientApp.cpp \
    ../Sources/View/SettingsToolBar.cpp \
    ../Sources/AppSettings.cpp \
    ../Sources/View/ViewDrawSettings.cpp \
    ../Sources/MainWindow/PipesMgntPageItemDelegate.cpp \
    ../Sources/View/TracesViewCore.cpp \
    ../Sources/TracesWindow.cpp \
    ../Sources/TracesWindows.cpp \
    ../Sources/MainWindow/MainWindow.cpp \
    ../Sources/ChannelsMgnt/ChannelsMgnt.cpp \
    ../Sources/ChannelsMgnt/CChannelTreeItem.cpp \
    ../Sources/ChannelsMgnt/CChannelTreeItemDelegate.cpp \
    ../Sources/ChannelsMgnt/CClearChannelContentConfirmationDlg.cpp \
    ../Sources/Dialogs/HighlightColorsSelectionDlg.cpp \
    ../Sources/Dialogs/AboutDlg.cpp \
    ../Sources/Color/ColorBtn.cpp \
    ../Sources/View/Highlight/ViewItemPattern.cpp \
    ../Sources/View/Highlight/ViewItemHighlightersSet.cpp \
    ../Sources/View/Highlight/ViewItemHighlighter_SearchedLine.cpp \
    ../Sources/View/Highlight/ViewHighlightSettings.cpp \
    ../Sources/View/Highlight/HighlightBrushesSet.cpp \
    ../Sources/View/Highlight/HighlightBrush.cpp \
    ../Sources/View/Highlight/HighlightsMgrWnd.cpp \
    ../Sources/View/Highlight/ViewItemPattern_Text.cpp \
    ../Sources/View/Highlight/ViewItemHighlighter.cpp \
    ../Sources/View/Highlight/HighlightTreeItemEventsConnection.cpp \
    ../Sources/View/Highlight/HighlightTreeItemDelegate.cpp \
    ../Sources/View/Highlight/HighlightTreeItem.cpp \
    ../Sources/View/Highlight/HighlightColorsPopup.cpp \
    ../Sources/View/ViewSearchEngine.cpp \
    ../Sources/WindowsManager.cpp \
    ../Sources/MainWindow/TcpIpSettingsPanel.cpp \
    ../Sources/ChannelSelection.cpp \
    ../Sources/ChannelsListener.cpp \
    ../Sources/View/ViewTracesIterator.cpp \
    ../Sources/TracesGroupMgrListener.cpp \
    ../Sources/TracesGroupListItem.cpp \
    ../Sources/TracesGroupNotificationsListener.cpp \
    ../Sources/Controls/ToggleToolButton.cpp \
    ../Sources/Panels/SettingsPanel.cpp \
    ../Sources/ServerAccess/TraceServerPortal.cpp \
    ../Sources/ServerAccess/WSSetTraceClient.cpp \
    ../Sources/Panels/DevicesSelectionPanel.cpp \
    ../Sources/DevicesMgr.cpp \
    ../Sources/Device.cpp \
    ../Sources/ServerAccess/WSGetDevices.cpp \
    ../Sources/ServerAccess/WebServiceRequest.cpp \
    ../Sources/ServerAccess/WSMapDevice.cpp \
    ../Sources/ServerAccess/WSUnmapDevice.cpp \
    ../Sources/DevicesMapping.cpp \
    ../Sources/View/ViewTracePainter.cpp \
    ../Sources/View/TracesViewSet.cpp
HEADERS += ../Sources/TracesView.h \
    ../Sources/Dialogs/NewViewDlg.hpp \
    ../Sources/Dialogs/NewPoolDlg.hpp \
    ../Sources/Dialogs/NewDocumentDlg.hpp \
    ../Sources/StatusUpdaters/UISensorsFactory.hpp \
    ../Sources/StatusUpdaters/UISensorsCollection.hpp \
    ../Sources/StatusUpdaters/UISensorCreator.hpp \
    ../Sources/StatusUpdaters/UISensor.hpp \
    ../Sources/StatusUpdaters/UISensor_LineEdit.hpp \
    ../Sources/StatusUpdaters/StatusUpdater.hpp \
    ../Sources/MainWindow/PoolTreeItem.hpp \
    ../Sources/View/DrawViewItemState.hpp \
    ../Sources/View/ViewItemSettings.hpp \
    ../Sources/View/ViewItemMargins.hpp \
    ../Sources/View/ViewColumnsSettings.hpp \
    ../Sources/View/ViewColumnsOrder.hpp \
    ../Sources/View/ViewColumnSettings.hpp \
    ../Sources/View/ViewColumnId.hpp \
    ../Sources/View/ViewSettings.hpp \
    ../Sources/View/ViewItemsSettings.hpp \
    ../Sources/MainWindow/ViewPage.hpp \
    ../Sources/MainWindow/PipesMgntPage.hpp \
    ../Sources/View/ViewHeader.hpp \
    ../Sources/TraceClientApp.h \
    ../Sources/View/SettingsToolBar.hpp \
    ../Sources/AppSettings.hpp \
    ../Sources/View/ViewDrawSettings.hpp \
    ../Sources/MainWindow/PipesMgntPageItemDelegate.hpp \
    ../Sources/View/TracesViewCore.hpp \
    ../Sources/TracesWindow.hpp \
    ../Sources/TracesWindows.hpp \
    ../Sources/MainWindow/MainWindow.hpp \
    ../Sources/ChannelsMgnt/ChannelsMgnt.hpp \
    ../Sources/ChannelsMgnt/CChannelTreeItem.hpp \
    ../Sources/ChannelsMgnt/CChannelTreeItemDelegate.hpp \
    ../Sources/ChannelsMgnt/CClearChannelContentConfirmationDlg.hpp \
    ../Sources/Dialogs/AboutDlg.h \
    ../Sources/Dialogs/HighlightColorsSelectionDlg.h \
    ../Sources/Color/ColorBtn.h \
    ../Sources/View/Highlight/ViewItemPattern.hpp \
    ../Sources/View/Highlight/ViewItemPattern_Text.hpp \
    ../Sources/View/Highlight/ViewItemHighlightersSet.hpp \
    ../Sources/View/Highlight/ViewItemHighlighter_SearchedLine.hpp \
    ../Sources/View/Highlight/ViewItemHighlighter.hpp \
    ../Sources/View/Highlight/ViewHighlightSettings.hpp \
    ../Sources/View/Highlight/HighlightBrushesSet.hpp \
    ../Sources/View/Highlight/HighlightBrush.hpp \
    ../Sources/View/Highlight/HighlightTreeItemDelegate.hpp \
    ../Sources/View/Highlight/HighlightTreeItem.hpp \
    ../Sources/View/Highlight/HighlightsMgrWnd.h \
    ../Sources/View/Highlight/HighlightTreeItemEventsConnection.h \
    ../Sources/View/Highlight/HighlightColorsPopup.h \
    ../Sources/View/ViewSearchEngine.h \
    ../Sources/WindowsManager.hpp \
    ../Sources/MainWindow/TcpIpSettingsPanel.h \
    ../Sources/ChannelSelection.h \
    ../Sources/ChannelsListener.h \
    ../Sources/View/ViewTracesIterator.hpp \
    ../Sources/TracesGroupMgrListener.h \
    ../Sources/TracesGroupListItem.h \
    ../Sources/TracesGroupNotificationsListener.h \
    ../Sources/Controls/ToggleToolButton.h \
    ../Sources/Panels/SettingsPanel.h \
    ../Sources/ServerAccess/TraceServerPortal.h \
    ../Sources/ServerAccess/WSSetTraceClient.h \
    ../Sources/Panels/DevicesSelectionPanel.h \
    ../Sources/DevicesMgr.h \
    ../Sources/Device.h \
    ../Sources/ServerAccess/WSGetDevices.h \
    ../Sources/ServerAccess/WebServiceRequest.h \
    ../Sources/ServerAccess/WSMapDevice.h \
    ../Sources/ServerAccess/WSUnmapDevice.h \
    ../Sources/DevicesMapping.h \
    ../Sources/View/ViewTracePainter.h \
    ../Sources/View/TracesViewSet.hpp
FORMS += ../UI/TracesView.ui \
    ../UI/NewViewDlg.ui \
    ../UI/NewPoolDlg.ui \
    ../UI/NewDocumentDlg.ui \
    ../UI/PipesMgntPage.ui \
    ../UI/ViewPage.ui \
    ../UI/TracesWindow.ui \
    ../UI/MainWindow.ui \
    ../UI/ChannelsMgnt.ui \
    ../UI/CClearChannelContentConfirmationDlg.ui \
    ../UI/HighlightsMgrWnd.ui \
    ../UI/HighlightColorsSelectionDlg.ui \
    ../UI/HighlightColorsPopup.ui \
    ../UI/AboutDlg.ui \
    ../UI/TcpIpSettingsPanel.ui \
    ../UI/ChannelSelection.ui \
    ../UI/SettingsPanel.ui \
    ../UI/DevicesSelection.ui
ICON=../Icons/AppOSX.icns
MOC_DIR = ../MOC
UI_DIR = ../UI
INCLUDEPATH += ../Sources
INCLUDEPATH += ../UI
INCLUDEPATH += $${NyxPath}/include/
INCLUDEPATH += $${NyxPath}/include/NyxNet
INCLUDEPATH += ../../TraceClientCore/include
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

CONFIG(debug, debug | release) {

    macx {
            PRE_TARGETDEPS += ../../Lib/Qt/Debug_64/libTraceClientCore.a
            PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Debug_64/libNyxBase.a
            PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Debug_64/libNyxNet.a
            LIBS += -lTraceClientCore \
                -L../../Lib/Qt/Debug_64
            LIBS += -lNyxBase \
                -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lNyxNet \
                -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lNyxWebSvr \
                -L$${NyxPath}/Lib/Qt/Debug_64
            LIBS += -lssl \
                -L$${NyxPath}/Lib/OSX/OpenSSL_64
            LIBS += -lcrypto \
                -L$${NyxPath}/Lib/OSX/OpenSSL_64
            LIBS += /usr/lib/libiconv.dylib
    }

    win32 {
            LIBS += -lwinmm
            LIBS += -lws2_32
            LIBS += -ladvapi32
            LIBS += -lTraceClientCore \
                -L../../Lib/Qt/Debug_64
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

    DESTDIR = ./Debug_64
    OBJECTS_DIR = ./Debug_64
    DEFINES += _DEBUG
}

CONFIG(release, debug | release) {
    macx {
        PRE_TARGETDEPS += ../../Lib/Qt/Release_64/libTraceClientCore.a
        PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Release_64/libNyxBase.a
        PRE_TARGETDEPS += $${NyxPath}/Lib/Qt/Release_64/libNyxNet.a
        LIBS += -lTraceClientCore \
            -L../../Lib/Qt/Release_64
        LIBS += -lNyxBase \
            -L$${NyxPath}/Lib/Qt/Release_64
        LIBS += -lNyxNet \
            -L$${NyxPath}/Lib/Qt/Release_64
        LIBS += -lNyxWebSvr \
            -L$${NyxPath}/Lib/Qt/Release_64
        LIBS += -lssl \
            -L$${NyxPath}/Lib/OSX/OpenSSL_64
        LIBS += -lcrypto \
            -L$${NyxPath}/Lib/OSX/OpenSSL_64
        LIBS += /usr/lib/libiconv.dylib
    }

    win32 {
            LIBS += -lwinmm
            LIBS += -lws2_32
            LIBS += -ladvapi32
            LIBS += -lTraceClientCore \
                -L../../Lib/Qt/Release_64
            LIBS += -lNyxBase \
                -L$${NyxPath}/Lib/Qt/Release_64
            LIBS += -lNyxNet \
                -L$${NyxPath}/Lib/Qt/Release_64
            LIBS += -lNyxWebSvr \
                -L$${NyxPath}/Lib/Qt/Release_64
            LIBS += -lssleay32 \
                -L$${NyxPath}/Lib/Windows/x64/openssl
            LIBS += -llibeay32 \
                -L$${NyxPath}/Lib/Windows/x64/openssl
    }

    DESTDIR = ./Release_64
    OBJECTS_DIR = ./Release_64
}

RESOURCES += \
    ../QTraceClient.qrc
