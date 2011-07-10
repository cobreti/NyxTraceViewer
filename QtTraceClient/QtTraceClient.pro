# -------------------------------------------------
# Project created by QtCreator 2010-02-12T21:15:19
# -------------------------------------------------
QT += xml
TARGET = TraceViewer
TEMPLATE = app
SOURCES += Sources/TracesView.cpp \
    Sources/mainwindow.cpp \
    Sources/DebugPanel.cpp \
    Sources/main.cpp \
    Sources/Dialogs/NewViewDlg.cpp \
    Sources/Dialogs/NewPoolDlg.cpp \
    Sources/Dialogs/NewDocumentDlg.cpp \
    Sources/StatusUpdaters/UISensorsFactory.cpp \
    Sources/StatusUpdaters/UISensorsCollection.cpp \
    Sources/StatusUpdaters/UISensor.cpp \
    Sources/StatusUpdaters/StatusUpdater.cpp \
    Sources/MainWindow/PoolTreeItem.cpp \
    Sources/Document/DocumentsCollection.cpp \
    Sources/View/ViewItem.cpp \
    Sources/View/ViewItems.cpp \
    Sources/View/ViewItemPos.cpp \
    Sources/View/ViewItem_TraceData.cpp \
    Sources/View/ViewItemPainter.cpp \
    Sources/View/DrawViewItemState.cpp \
    Sources/View/ViewItemPainterCollection.cpp \
    Sources/View/ViewItemSettings.cpp \
    Sources/View/ViewItemMargins.cpp \
    Sources/View/ViewItemTextPainter.cpp \
    Sources/View/ViewItemDataPainter.cpp \
    Sources/View/ViewItemTickCountPainter.cpp \
    Sources/View/ViewItemThreadIdPainter.cpp \
    Sources/View/ViewItemBackgroundPainter.cpp \
    Sources/View/ViewColumnsSettings.cpp \
    Sources/View/ViewColumnsOrder.cpp \
    Sources/View/ViewColumnSettings.cpp \
    Sources/View/ViewSettings.cpp \
    Sources/View/ViewItemsSettings.cpp \
    Sources/View/ViewItemModuleNamePainter.cpp \
    Sources/View/ViewItemRowPainter.cpp \
    Sources/MainWindow/ViewPage.cpp \
    Sources/MainWindow/PipesMgntPage.cpp \
    Sources/View/ViewHeader.cpp \
    Sources/View/ViewItemInserter.cpp \
    Sources/Document/DocRepositoryObserver.cpp \
    Sources/View/ViewItemLineNumberPainter.cpp \
    Sources/View/ViewItemsNodeObjectsPool.cpp \
    Sources/MainWindow/ViewTreeItem.cpp \
    Sources/TraceClientApp.cpp \
    Sources/View/SettingsToolBar.cpp \
    Sources/Document/TracesDocument.cpp \
    Sources/View/SessionViewItems.cpp \
    Sources/View/ModuleViewItems.cpp \
    Sources/View/ViewItemsModules.cpp \
    Sources/View/ViewItemsModulesMgr.cpp \
    Sources/View/Walkers/ViewItemsWalkerStats.cpp \
    Sources/View/Walkers/ViewItemsWalkerNode.cpp \
    Sources/View/Walkers/ViewItemsWalker.cpp \
    Sources/View/Walkers/ViewItemsModuleWalkerNode.cpp \
    Sources/View/Walkers/ViewItemsSessionWalkerNode.cpp \
    Sources/View/Walkers/ViewItemsWalkerNodesPool.cpp \
    Sources/View/Walkers/ViewItemsWalkerPos.cpp \
    Sources/View/Walkers/FileWriterViewItemsWalker.cpp
HEADERS += Sources/TracesView.h \
    Sources/mainwindow.h \
    Sources/DebugPanel.h \
    Sources/Dialogs/NewViewDlg.hpp \
    Sources/Dialogs/NewPoolDlg.hpp \
    Sources/Dialogs/NewDocumentDlg.hpp \
    Sources/StatusUpdaters/UISensorsFactory.hpp \
    Sources/StatusUpdaters/UISensorsCollection.hpp \
    Sources/StatusUpdaters/UISensorCreator.hpp \
    Sources/StatusUpdaters/UISensor.hpp \
    Sources/StatusUpdaters/UISensor_LineEdit.hpp \
    Sources/StatusUpdaters/StatusUpdater.hpp \
    Sources/MainWindow/PoolTreeItem.hpp \
    Sources/Document/DocumentsCollection.hpp \
    Sources/View/ViewItem.hpp \
    Sources/View/ViewItems.hpp \
    Sources/View/ViewItemPos.hpp \
    Sources/View/ViewItem_TraceData.hpp \
    Sources/View/ViewItemPainter.hpp \
    Sources/View/DrawViewItemState.hpp \
    Sources/View/ViewItemPainterCollection.hpp \
    Sources/View/ViewItemSettings.hpp \
    Sources/View/ViewItemMargins.hpp \
    Sources/View/ViewItemTextPainter.hpp \
    Sources/View/ViewItemDataPainter.hpp \
    Sources/View/ViewItemTickCountPainter.hpp \
    Sources/View/ViewItemThreadIdPainter.hpp \
    Sources/View/ViewItemBackgroundPainter.hpp \
    Sources/View/ViewColumnsSettings.hpp \
    Sources/View/ViewColumnsOrder.hpp \
    Sources/View/ViewColumnSettings.hpp \
    Sources/View/ViewColumnId.hpp \
    Sources/View/ViewSettings.hpp \
    Sources/View/ViewItemsSettings.hpp \
    Sources/View/ViewItemModuleNamePainter.hpp \
    Sources/View/ViewItemRowPainter.hpp \
    Sources/MainWindow/ViewPage.hpp \
    Sources/MainWindow/PipesMgntPage.hpp \
    Sources/View/ViewHeader.hpp \
    Sources/View/ViewItemInserter.hpp \
    Sources/Document/DocRepositoryObserver.hpp \
    Sources/View/ViewItemLineNumberPainter.hpp \
    Sources/View/ViewItemsNodeObjectsPool.hpp \
    Sources/MainWindow/ViewTreeItem.hpp \
    Sources/TraceClientApp.hpp \
    Sources/View/SettingsToolBar.hpp \
    Sources/Document/TracesDocument.hpp \
    Sources/View/SessionViewItems.hpp \
    Sources/View/ModuleViewItems.hpp \
    Sources/View/ViewItemsModules.hpp \
    Sources/View/ViewItemsModulesMgr.hpp \
    Sources/View/IViewItemsModulesListener.hpp \
    Sources/View/Walkers/ViewItemsWalkerStats.hpp \
    Sources/View/Walkers/ViewItemsWalkerNode.hpp \
    Sources/View/Walkers/ViewItemsWalker.hpp \
    Sources/View/Walkers/ViewItemsModuleWalkerNode.hpp \
    Sources/View/Walkers/ViewItemsSessionWalkerNode.hpp \
    Sources/View/Walkers/ViewItemsWalkerNodesPool.hpp \
    Sources/View/Walkers/ViewItemsWalkerPos.hpp \
    Sources/View/Walkers/FileWriterViewItemsWalker.hpp
FORMS += UI/TracesView.ui \
    UI/mainwindow.ui \
    UI/DebugPanel.ui \
    UI/NewViewDlg.ui \
    UI/NewPoolDlg.ui \
    UI/NewDocumentDlg.ui \
    UI/PipesMgntPage.ui \
    UI/ViewPage.ui
ICON=Icons/AppOSX.icns
MOC_DIR = ./MOC
UI_DIR = ./UI
INCLUDEPATH += ./Sources
INCLUDEPATH += ./UI
INCLUDEPATH += ../NyxLibs/include/
INCLUDEPATH += ../NyxLibs/include/NyxNet
INCLUDEPATH += ../TraceClientCore/include
mac:INCLUDEPATH += ../NyxLibs/include/OSX
mac:LIBS += /System/Library/Frameworks/CoreServices.framework/CoreServices
mac:CONFIG += x86
mac:CONFIG -= x86_64
CONFIG(debug, debug|release) {
    mac::PRE_TARGETDEPS += ../lib/OSX/Debug_32/libTraceClientCore.a
    mac::PRE_TARGETDEPS += ../NyxLibs/lib/OSX/Debug_32/libNyxBase.a
    mac::PRE_TARGETDEPS += ../NyxLibs/lib/OSX/Debug_32/libNyxNet.a
    mac:LIBS += -lTraceClientCore \
        -L../lib/OSX/Debug_32
    mac:LIBS += -lNyxBase \
        -L../NyxLibs/lib/OSX/Debug_32
    mac:LIBS += -lNyxNet \
        -L../NyxLibs/lib/OSX/Debug_32
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else { 
    mac::PRE_TARGETDEPS += ../lib/OSX/Release_32/libTraceClientCore.a
    mac::PRE_TARGETDEPS += ../NyxLibs/lib/OSX/Release_32/libNyxBase.a
    mac::PRE_TARGETDEPS += ../NyxLibs/lib/OSX/Release_32/libNyxNet.a
    mac:LIBS += -lTraceClientCore \
        -L../lib/OSX/Release_32
    mac:LIBS += -lNyxBase \
        -L../NyxLibs/lib/OSX/Release_32
    mac:LIBS += -lNyxNet \
        -L../NyxLibs/lib/OSX/Release_32
    DESTDIR = ./Release
    OBJECTS_DIR = ./Release
}

RESOURCES += \
    QTraceClient.qrc
