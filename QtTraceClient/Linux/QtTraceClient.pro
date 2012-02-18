FORMS += \
    ../UI/ViewPage.ui \
    ../UI/TracesView.ui \
    ../UI/PipesMgntPage.ui \
    ../UI/NewViewDlg.ui \
    ../UI/NewPoolDlg.ui \
    ../UI/NewDocumentDlg.ui \
    ../UI/mainwindow.ui

RESOURCES += \
    ../QTraceClient.qrc

HEADERS += \
    ../Sources/Dialogs/NewViewDlg.hpp \
    ../Sources/Dialogs/NewPoolDlg.hpp \
    ../Sources/Dialogs/NewDocumentDlg.hpp \
    ../Sources/Document/TracesDocument.hpp \
    ../Sources/Document/DocumentsCollection.hpp \
    ../Sources/Document/DocRepositoryObserver.hpp \
    ../Sources/MainWindow/ViewTreeItem.hpp \
    ../Sources/MainWindow/ViewPage.hpp \
    ../Sources/MainWindow/PoolTreeItem.hpp \
    ../Sources/MainWindow/PipesMgntPage.hpp \
    ../Sources/StatusUpdaters/UISensorsFactory.hpp \
    ../Sources/StatusUpdaters/UISensorsCollection.hpp \
    ../Sources/StatusUpdaters/UISensorCreator.hpp \
    ../Sources/StatusUpdaters/UISensor.hpp \
    ../Sources/StatusUpdaters/UISensor_LineEdit.hpp \
    ../Sources/StatusUpdaters/StatusUpdater.hpp \
    ../Sources/View/ViewSettings.hpp \
    ../Sources/View/ViewItemTickCountPainter.hpp \
    ../Sources/View/ViewItemThreadIdPainter.hpp \
    ../Sources/View/ViewItemTextPainter.hpp \
    ../Sources/View/ViewItemsSettings.hpp \
    ../Sources/View/ViewItemsNodeObjectsPool.hpp \
    ../Sources/View/ViewItemsModulesMgr.hpp \
    ../Sources/View/ViewItemsModules.hpp \
    ../Sources/View/ViewItemSettings.hpp \
    ../Sources/View/ViewItems.hpp \
    ../Sources/View/ViewItemRowPainter.hpp \
    ../Sources/View/ViewItemPos.hpp \
    ../Sources/View/ViewItemPainterCollection.hpp \
    ../Sources/View/ViewItemPainter.hpp \
    ../Sources/View/ViewItemModuleNamePainter.hpp \
    ../Sources/View/ViewItemMargins.hpp \
    ../Sources/View/ViewItemLineNumberPainter.hpp \
    ../Sources/View/ViewItemInserter.hpp \
    ../Sources/View/ViewItemDataPainter.hpp \
    ../Sources/View/ViewItemBackgroundPainter.hpp \
    ../Sources/View/ViewItem.hpp \
    ../Sources/View/ViewItem_TraceData.hpp \
    ../Sources/View/ViewHeader.hpp \
    ../Sources/View/ViewEnums.hpp \
    ../Sources/View/ViewDrawSettings.hpp \
    ../Sources/View/ViewColumnsSettings.hpp \
    ../Sources/View/ViewColumnsOrder.hpp \
    ../Sources/View/ViewColumnSettings.hpp \
    ../Sources/View/ViewColumnId.hpp \
    ../Sources/View/SettingsToolBar.hpp \
    ../Sources/View/SessionViewItems.hpp \
    ../Sources/View/ModuleViewItems.hpp \
    ../Sources/View/IViewItemsModulesListener.hpp \
    ../Sources/View/DrawViewItemState.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerStats.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerPos.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodesPool.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodePos.hpp \
    ../Sources/View/Walkers/ViewItemsWalkerNode.hpp \
    ../Sources/View/Walkers/ViewItemsWalker.hpp \
    ../Sources/View/Walkers/ViewItemsSessionWalkerNode.hpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNodePos.hpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNode.hpp \
    ../Sources/View/Walkers/FileWriterViewItemsWalker.hpp \
    ../Sources/TracesView.h \
    ../Sources/TraceClientApp.hpp \
    ../Sources/MainWindow.h \
    ../Sources/AppSettings.hpp \
    ../Sources/MainWindow/PipesMgntPageItemDelegate.hpp

SOURCES += \
    ../Sources/Dialogs/NewViewDlg.cpp \
    ../Sources/Dialogs/NewPoolDlg.cpp \
    ../Sources/Dialogs/NewDocumentDlg.cpp \
    ../Sources/Document/TracesDocument.cpp \
    ../Sources/Document/DocumentsCollection.cpp \
    ../Sources/Document/DocRepositoryObserver.cpp \
    ../Sources/MainWindow/ViewTreeItem.cpp \
    ../Sources/MainWindow/ViewPage.cpp \
    ../Sources/MainWindow/PoolTreeItem.cpp \
    ../Sources/MainWindow/PipesMgntPage.cpp \
    ../Sources/StatusUpdaters/UISensorsFactory.cpp \
    ../Sources/StatusUpdaters/UISensorsCollection.cpp \
    ../Sources/StatusUpdaters/UISensor.cpp \
    ../Sources/StatusUpdaters/StatusUpdater.cpp \
    ../Sources/View/ViewSettings.cpp \
    ../Sources/View/ViewItemTickCountPainter.cpp \
    ../Sources/View/ViewItemThreadIdPainter.cpp \
    ../Sources/View/ViewItemTextPainter.cpp \
    ../Sources/View/ViewItemsSettings.cpp \
    ../Sources/View/ViewItemsNodeObjectsPool.cpp \
    ../Sources/View/ViewItemsModulesMgr.cpp \
    ../Sources/View/ViewItemsModules.cpp \
    ../Sources/View/ViewItemSettings.cpp \
    ../Sources/View/ViewItems.cpp \
    ../Sources/View/ViewItemRowPainter.cpp \
    ../Sources/View/ViewItemPos.cpp \
    ../Sources/View/ViewItemPainterCollection.cpp \
    ../Sources/View/ViewItemPainter.cpp \
    ../Sources/View/ViewItemModuleNamePainter.cpp \
    ../Sources/View/ViewItemMargins.cpp \
    ../Sources/View/ViewItemLineNumberPainter.cpp \
    ../Sources/View/ViewItemInserter.cpp \
    ../Sources/View/ViewItemDataPainter.cpp \
    ../Sources/View/ViewItemBackgroundPainter.cpp \
    ../Sources/View/ViewItem.cpp \
    ../Sources/View/ViewItem_TraceData.cpp \
    ../Sources/View/ViewHeader.cpp \
    ../Sources/View/ViewDrawSettings.cpp \
    ../Sources/View/ViewColumnsSettings.cpp \
    ../Sources/View/ViewColumnsOrder.cpp \
    ../Sources/View/ViewColumnSettings.cpp \
    ../Sources/View/SettingsToolBar.cpp \
    ../Sources/View/SessionViewItems.cpp \
    ../Sources/View/ModuleViewItems.cpp \
    ../Sources/View/DrawViewItemState.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerStats.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerPos.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodesPool.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerNodePos.cpp \
    ../Sources/View/Walkers/ViewItemsWalkerNode.cpp \
    ../Sources/View/Walkers/ViewItemsWalker.cpp \
    ../Sources/View/Walkers/ViewItemsSessionWalkerNode.cpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNodePos.cpp \
    ../Sources/View/Walkers/ViewItemsModuleWalkerNode.cpp \
    ../Sources/View/Walkers/FileWriterViewItemsWalker.cpp \
    ../Sources/TracesView.cpp \
    ../Sources/TraceClientApp.cpp \
    ../Sources/MainWindow.cpp \
    ../Sources/main.cpp \
    ../Sources/AppSettings.cpp \
    ../Sources/MainWindow/PipesMgntPageItemDelegate.cpp


ICON=../Icons/AppLinux.icns
MOC_DIR = ../MOC
UI_DIR = ../UI
INCLUDEPATH += ../Sources
INCLUDEPATH += ../UI
INCLUDEPATH += ../../NyxLibs/include/
INCLUDEPATH += ../../NyxLibs/include/NyxNet
INCLUDEPATH += ../../TraceClientCore/include
INCLUDEPATH += ../../NyxLibs/include/Linux
CONFIG(debug, debug|release) {
#    PRE_TARGETDEPS += ../../lib/Linux/Debug/libTraceClientCore.a
#    PRE_TARGETDEPS += ../../NyxLibs/lib/Linux/Debug/libNyxBase.a
#    PRE_TARGETDEPS += ../../NyxLibs/lib/Linux/Debug/libNyxNet.a
    LIBS += -lTraceClientCore \
        -L../../lib/Linux/Debug
    LIBS += -lNyxNet \
        -L../../NyxLibs/Lib/Linux/Debug
    LIBS += -lNyxBase \
        -L../../NyxLibs/Lib/Linux/Debug
    DESTDIR = ./Debug
    OBJECTS_DIR = ./Debug
    DEFINES += _DEBUG
}
else {
#    PRE_TARGETDEPS += ../../lib/Linux/Release/libTraceClientCore.a
#    PRE_TARGETDEPS += ../../NyxLibs/lib/Linux/Release/libNyxBase.a
#    PRE_TARGETDEPS += ../../NyxLibs/lib/Linux/Release/libNyxNet.a
    LIBS += -lTraceClientCore \
        -L../../lib/Linux/Release
    LIBS += -lNyxNet \
        -L../../NyxLibs/Lib/Linux/Release
    LIBS += -lNyxBase \
        -L../../NyxLibs/Lib/Linux/Release
    DESTDIR = ./Release
    OBJECTS_DIR = ./Release
}

RESOURCES += \
    ../QTraceClient.qrc














