/********************************************************************************
** Form generated from reading UI file 'traceviewerfeeder.ui'
**
** Created: Sun Jul 8 15:58:51 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACEVIEWERFEEDER_H
#define UI_TRACEVIEWERFEEDER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CTraceViewerFeederClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QListWidget *ChannelsName;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *btnAddChannel;
    QPushButton *btnRemoveChannel;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *TracesPerBlockSpinBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_11;
    QSpinBox *IntervalBetweenBlocksSpinBox;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *btnNyxPipeAPISource;
    QRadioButton *btnNyxTcpIpAPISource;
    QRadioButton *btnExternalAPISource;
    QRadioButton *btnDllSource;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *TcpIpLabel;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *editTcpIpAddress;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *m_cbUseText;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_8;
    QPlainTextEdit *editTraceText;
    QSpacerItem *verticalSpacer_5;
    QCheckBox *m_cbUseFile;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QLineEdit *m_editFilename;
    QPushButton *m_btnBrowseFile;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnStartStop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CTraceViewerFeederClass)
    {
        if (CTraceViewerFeederClass->objectName().isEmpty())
            CTraceViewerFeederClass->setObjectName(QString::fromUtf8("CTraceViewerFeederClass"));
        CTraceViewerFeederClass->resize(696, 659);
        centralWidget = new QWidget(CTraceViewerFeederClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ChannelsName = new QListWidget(centralWidget);
        ChannelsName->setObjectName(QString::fromUtf8("ChannelsName"));
        ChannelsName->setMinimumSize(QSize(200, 0));
        ChannelsName->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

        verticalLayout_4->addWidget(ChannelsName);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        btnAddChannel = new QPushButton(centralWidget);
        btnAddChannel->setObjectName(QString::fromUtf8("btnAddChannel"));
        btnAddChannel->setFlat(false);

        horizontalLayout_5->addWidget(btnAddChannel);

        btnRemoveChannel = new QPushButton(centralWidget);
        btnRemoveChannel->setObjectName(QString::fromUtf8("btnRemoveChannel"));
        btnRemoveChannel->setCheckable(false);

        horizontalLayout_5->addWidget(btnRemoveChannel);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(400, 0));
        frame->setBaseSize(QSize(200, 200));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(2);
        frame->setMidLineWidth(2);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        TracesPerBlockSpinBox = new QSpinBox(frame);
        TracesPerBlockSpinBox->setObjectName(QString::fromUtf8("TracesPerBlockSpinBox"));
        TracesPerBlockSpinBox->setMinimumSize(QSize(100, 0));
        TracesPerBlockSpinBox->setMinimum(1);
        TracesPerBlockSpinBox->setMaximum(100000);

        horizontalLayout_2->addWidget(TracesPerBlockSpinBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_7->addWidget(label_4);

        horizontalSpacer_11 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        IntervalBetweenBlocksSpinBox = new QSpinBox(frame);
        IntervalBetweenBlocksSpinBox->setObjectName(QString::fromUtf8("IntervalBetweenBlocksSpinBox"));
        IntervalBetweenBlocksSpinBox->setMinimumSize(QSize(100, 0));
        IntervalBetweenBlocksSpinBox->setMaximum(9999999);

        horizontalLayout_7->addWidget(IntervalBetweenBlocksSpinBox);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        btnNyxPipeAPISource = new QRadioButton(frame);
        btnNyxPipeAPISource->setObjectName(QString::fromUtf8("btnNyxPipeAPISource"));
        btnNyxPipeAPISource->setMinimumSize(QSize(100, 0));

        verticalLayout_3->addWidget(btnNyxPipeAPISource);

        btnNyxTcpIpAPISource = new QRadioButton(frame);
        btnNyxTcpIpAPISource->setObjectName(QString::fromUtf8("btnNyxTcpIpAPISource"));

        verticalLayout_3->addWidget(btnNyxTcpIpAPISource);

        btnExternalAPISource = new QRadioButton(frame);
        btnExternalAPISource->setObjectName(QString::fromUtf8("btnExternalAPISource"));
        btnExternalAPISource->setMinimumSize(QSize(100, 0));

        verticalLayout_3->addWidget(btnExternalAPISource);

        btnDllSource = new QRadioButton(frame);
        btnDllSource->setObjectName(QString::fromUtf8("btnDllSource"));

        verticalLayout_3->addWidget(btnDllSource);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        TcpIpLabel = new QLabel(frame);
        TcpIpLabel->setObjectName(QString::fromUtf8("TcpIpLabel"));

        horizontalLayout_9->addWidget(TcpIpLabel);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_13);

        editTcpIpAddress = new QLineEdit(frame);
        editTcpIpAddress->setObjectName(QString::fromUtf8("editTcpIpAddress"));

        horizontalLayout_9->addWidget(editTcpIpAddress);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        m_cbUseText = new QCheckBox(frame);
        m_cbUseText->setObjectName(QString::fromUtf8("m_cbUseText"));

        verticalLayout->addWidget(m_cbUseText);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        editTraceText = new QPlainTextEdit(frame);
        editTraceText->setObjectName(QString::fromUtf8("editTraceText"));
        editTraceText->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(editTraceText);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        m_cbUseFile = new QCheckBox(frame);
        m_cbUseFile->setObjectName(QString::fromUtf8("m_cbUseFile"));

        verticalLayout->addWidget(m_cbUseFile);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_8->addWidget(label_5);

        m_editFilename = new QLineEdit(frame);
        m_editFilename->setObjectName(QString::fromUtf8("m_editFilename"));

        horizontalLayout_8->addWidget(m_editFilename);

        m_btnBrowseFile = new QPushButton(frame);
        m_btnBrowseFile->setObjectName(QString::fromUtf8("m_btnBrowseFile"));

        horizontalLayout_8->addWidget(m_btnBrowseFile);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btnStartStop = new QPushButton(frame);
        btnStartStop->setObjectName(QString::fromUtf8("btnStartStop"));

        horizontalLayout_6->addWidget(btnStartStop);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addWidget(frame);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        CTraceViewerFeederClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CTraceViewerFeederClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 696, 22));
        CTraceViewerFeederClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CTraceViewerFeederClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CTraceViewerFeederClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CTraceViewerFeederClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CTraceViewerFeederClass->setStatusBar(statusBar);

        retranslateUi(CTraceViewerFeederClass);

        QMetaObject::connectSlotsByName(CTraceViewerFeederClass);
    } // setupUi

    void retranslateUi(QMainWindow *CTraceViewerFeederClass)
    {
        CTraceViewerFeederClass->setWindowTitle(QApplication::translate("CTraceViewerFeederClass", "CTraceViewerFeeder", 0, QApplication::UnicodeUTF8));
        btnAddChannel->setText(QApplication::translate("CTraceViewerFeederClass", "+", 0, QApplication::UnicodeUTF8));
        btnRemoveChannel->setText(QApplication::translate("CTraceViewerFeederClass", "-", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CTraceViewerFeederClass", "Traces count per block", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CTraceViewerFeederClass", "Interval between blocks (msec):", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CTraceViewerFeederClass", "Traces API:", 0, QApplication::UnicodeUTF8));
        btnNyxPipeAPISource->setText(QApplication::translate("CTraceViewerFeederClass", "Nyx Pipe", 0, QApplication::UnicodeUTF8));
        btnNyxTcpIpAPISource->setText(QApplication::translate("CTraceViewerFeederClass", "Nyx TcpIp", 0, QApplication::UnicodeUTF8));
        btnExternalAPISource->setText(QApplication::translate("CTraceViewerFeederClass", "External (TraceClientLink)", 0, QApplication::UnicodeUTF8));
        btnDllSource->setText(QApplication::translate("CTraceViewerFeederClass", "Dll Feeder", 0, QApplication::UnicodeUTF8));
        TcpIpLabel->setText(QApplication::translate("CTraceViewerFeederClass", "TcpIp Address:", 0, QApplication::UnicodeUTF8));
        m_cbUseText->setText(QApplication::translate("CTraceViewerFeederClass", "Use text", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CTraceViewerFeederClass", "Text :", 0, QApplication::UnicodeUTF8));
        m_cbUseFile->setText(QApplication::translate("CTraceViewerFeederClass", "Use file", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CTraceViewerFeederClass", "Filename:", 0, QApplication::UnicodeUTF8));
        m_btnBrowseFile->setText(QApplication::translate("CTraceViewerFeederClass", "Browse", 0, QApplication::UnicodeUTF8));
        btnStartStop->setText(QApplication::translate("CTraceViewerFeederClass", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CTraceViewerFeederClass: public Ui_CTraceViewerFeederClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACEVIEWERFEEDER_H
