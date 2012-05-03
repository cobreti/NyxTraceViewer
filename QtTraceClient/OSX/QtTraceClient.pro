# -------------------------------------------------
# Project created by QtCreator 2010-02-12T21:15:19
# -------------------------------------------------
QT += xml
TARGET = TraceViewer
TEMPLATE = app
SOURCES += ../Sources/TracesView.cpp \
    ../Sources/mainwindow.cpp \
    ../Sources/main.cpp \
    ../Sources/Dialogs/NewViewDlg.cpp \
    ../Sources/Dialogs/NewPoolDlg.cpp \
    ../Sources/Dialogs/NewDocumentDlg.cpp \
    ../Sources/StatusUpdaters/UISensorsFactory.cpp \
    ../Sources/StatusUpdaters/UISensorsCollection.cpp \
    ../Sources/StatusUpdaters/UISensor.cpp \
    ../Sources/StatusUpdaters/StatusUpdater.cpp \
    ../Sources/MainWindow/PoolTreeItem.cpp \
    ../Sources/View/ViewItem.cpp \
    ../Sources/View/ViewItems.cpp \
    ../Sources/View/ViewItemPos.cpp \
    ../Sources/View/ViewItem_TraceData.cpp \
    ../Sources/View/ViewItemPainter.cpp \
    ../Sources/View/DrawViewItemState.cpp \
    ../Sources/View/ViewItemPainterCollection.cpp \
    ../Sources/View/ViewItemSettings.cpp \
    ../Sources/View/ViewItemMargins.cpp \
    ../Sources/View/ViewItemTextPainter.cpp \
    ../Sources/View/ViewItemDataPainter.cpp \
    ../Sources/View/ViewItemTickCountPainter.cpp \
    ../Sources/View/ViewItemThreadIdPainter.cpp \
    ../Sources/View/ViewItemBackgroundPainter.cpp \
    ../Sources/View/ViewColumnsSettings.cpp \
    ../Sources/View/ViewColumnsOrder.cpp \
    ../Sources/View/ViewColumnSettings.cpp \
    ../Sources/View/ViewSettings.cpp \
    ../Sources/View/ViewItemsSettings.cpp \
    ../Sources/View/ViewItemModuleNamePainter.cpp \
    ../Sources/View/ViewItemRowPainter.cpp \
    ../Sources/MainWindow/ViewPage.cpp \
    ../Sources/MainWindow/PipesMgntPage.cpp \
    ../Sources/View/ViewHeader.cpp \
    ../Sources/View/ViewItemInserter.cpp \
    ../Sources/View/ViewItemLineNumberPainter.cpp \
    ../Sources/View/ViewItemsNodeObjectsPool.cpp \
    ../Sources/MainWindow/ViewTreeItem.cpp \
    ../Sources/TraceClientApp.cpp \
    ../Sources/View/SettingsToolBar.cpp \
    ../Sources/View/SessionViewItems.cpp \
    ../Sources/View/ModuleViewItems.cpp \
    ../Sources/View/ViewItemsModules.cpp \
    ../Sources/View/ViewItemsModulesMgr.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerStats.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerNode.cpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNode.cpp \
    ../Sources/View/Walkers/ViewItemsSessionWalkerNode.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodesPool.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerPos.cpp \
    ../Sources/View/Walkers/FileWriterViewItemsWalker.cpp \
    ../Sources/AppSettings.cpp \
    ../Sources/View/ViewDrawSettings.cpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNodePos.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodePos.cpp \
    ../Sources/MainWindow/PipesMgntPageItemDelegate.cpp \
    ../Sources/View/TracesViewCore.cpp \
    ../Sources/View/TracesViewCoreRepositoryObserver.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerCore.cpp \
    ../Sources/View/Walkers/ViewItemsWalker.cpp \
    ../Sources/View/TracesViewSet.cpp \
    ../Sources/View/ViewItemsModulesListeners.cpp
HEADERS += ../Sources/TracesView.h \
    ../Sources/mainwindow.h \
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
    ../Sources/View/ViewItem.hpp \
    ../Sources/View/ViewItems.hpp \
    ../Sources/View/ViewItemPos.hpp \
    ../Sources/View/ViewItem_TraceData.hpp \
    ../Sources/View/ViewItemPainter.hpp \
    ../Sources/View/DrawViewItemState.hpp \
    ../Sources/View/ViewItemPainterCollection.hpp \
    ../Sources/View/ViewItemSettings.hpp \
    ../Sources/View/ViewItemMargins.hpp \
    ../Sources/View/ViewItemTextPainter.hpp \
    ../Sources/View/ViewItemDataPainter.hpp \
    ../Sources/View/ViewItemTickCountPainter.hpp \
    ../Sources/View/ViewItemThreadIdPainter.hpp \
    ../Sources/View/ViewItemBackgroundPainter.hpp \
    ../Sources/View/ViewColumnsSettings.hpp \
    ../Sources/View/ViewColumnsOrder.hpp \
    ../Sources/View/ViewColumnSettings.hpp \
    ../Sources/View/ViewColumnId.hpp \
    ../Sources/View/ViewSettings.hpp \
    ../Sources/View/ViewItemsSettings.hpp \
    ../Sources/View/ViewItemModuleNamePainter.hpp \
    ../Sources/View/ViewItemRowPainter.hpp \
    ../Sources/MainWindow/ViewPage.hpp \
    ../Sources/MainWindow/PipesMgntPage.hpp \
    ../Sources/View/ViewHeader.hpp \
    ../Sources/View/ViewItemInserter.hpp \
    ../Sources/View/ViewItemLineNumberPainter.hpp \
    ../Sources/View/ViewItemsNodeObjectsPool.hpp \
    ../Sources/MainWindow/ViewTreeItem.hpp \
    ../Sources/TraceClientApp.hpp \
    ../Sources/View/SettingsToolBar.hpp \
    ../Sources/View/SessionViewItems.hpp \
    ../Sources/View/ModuleViewItems.hpp \
    ../Sources/View/ViewItemsModules.hpp \
    ../Sources/View/ViewItemsModulesMgr.hpp \
    ../Sources/View/IViewItemsModulesListener.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerStats.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerNode.hpp \
    ../Sources/View/Walkers/ViewItemsWalker.hpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNode.hpp \
    ../Sources/View/Walkers/ViewItemsSessionWalkerNode.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodesPool.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerPos.hpp \
    ../Sources/View/Walkers/FileWriterViewItemsWalker.hpp \
    ../Sources/AppSettings.hpp \
    ../Sources/View/ViewDrawSettings.hpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNodePos.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodePos.hpp \
    ../Sources/MainWindow/PipesMgntPageItemDelegate.hpp \
    ../Sources/View/TracesViewCore.hpp \
    ../Sources/View/TracesViewCoreRepositoryObserver.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerCore.hpp \
    ../Sources/View/Walkers/ViewItemsWalker.hpp \
    ../Sources/View/Walkers/IViewItemsWalkerMethods.hpp \
    ../Sources/View/TracesViewSet.hpp \
    ../Sources/View/ViewItemsModulesListeners.hpp
FORMS += ../UI/TracesView.ui \
    ../UI/mainwindow.ui \
    ../UI/NewViewDlg.ui \
    ../UI/NewPoolDlg.ui \
    ../UI/NewDocumentDlg.ui \
    ../UI/PipesMgntPage.ui \
    ../UI/ViewPage.ui
ICON=../Icons/AppOSX.icns
MOC_DIR = ../MOC
UI_DIR = ../UI
INCLUDEPATH += ../Sources
INCLUDEPATH += ../UI
INCLUDEPATH += $(NyxPath)/include/
INCLUDEPATH += $(NyxPath)/include/NyxNet
INCLUDEPATH += ../../TraceClientCore/include
mac:INCLUDEPATH += $(NyxPath)/include/OSX
mac:LIBS += /System/Library/Frameworks/CoreServices.framework/CoreServices
mac:LIBS += /System/Library/Frameworks/Foundation.framework/Foundation
CONFIG(debug, debug|release) {
    mac::PRE_TARGETDEPS += ../../lib/OSX/Debug/libTraceClientCore.a
    mac::PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Debug_Universal_32_64/libNyxBase.a
    mac::PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Debug_Universal_32_64/libNyxNet.a
    mac:LIBS += -lTraceClientCore \
        -L../../lib/OSX/Debug
    mac:LIBS += -lNyxBase \
        -L$(NyxPath)/Lib/OSX/Debug_Universal_32_64
    mac:LIBS += -lNyxNet \
        -L$(NyxPath)/Lib/OSX/Debug_Universal_32_64
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else { 
    mac::PRE_TARGETDEPS += ../../lib/OSX/Release/libTraceClientCore.a
    mac::PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Release_Universal_32_64/libNyxBase.a
    mac::PRE_TARGETDEPS += $(NyxPath)/Lib/OSX/Release_Universal_32_64/libNyxNet.a
    mac:LIBS += -lTraceClientCore \
        -L../../lib/OSX/Release
    mac:LIBS += -lNyxBase \
        -L$(NyxPath)/Lib/OSX/Release_Universal_32_64
    mac:LIBS += -lNyxNet \
        -L$(NyxPath)/Lib/OSX/Release_Universal_32_64
    DESTDIR = ./Release
    OBJECTS_DIR = ./Release
}

RESOURCES += \
    ../QTraceClient.qrc
