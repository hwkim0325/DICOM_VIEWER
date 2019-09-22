/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QWindow
{
public:
    QAction *actionAbout_Dicom_Viewer;
    QAction *actionOpen;
    QAction *actionOpenDicomDir;
    QAction *actionOpen_Zip_file;
    QAction *actionScan_for_Dicom_file;
    QAction *actionPrint_Setup;
    QAction *actionExit;
    QAction *actionToolBar;
    QAction *actionCustomize;
    QAction *actionOptions;
    QWidget *centralwidget;
    QSplitter *splitter;
    QListWidget *listWidget;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QVTKOpenGLWidget *view1;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QVTKOpenGLWidget *view2_3;
    QVTKOpenGLWidget *view2_2;
    QVTKOpenGLWidget *view2_4;
    QVTKOpenGLWidget *view2_1;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QWindow)
    {
        if (QWindow->objectName().isEmpty())
            QWindow->setObjectName(QStringLiteral("QWindow"));
        QWindow->resize(1490, 880);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QWindow->sizePolicy().hasHeightForWidth());
        QWindow->setSizePolicy(sizePolicy);
        QWindow->setMinimumSize(QSize(1490, 880));
        QWindow->setMaximumSize(QSize(1490, 880));
        actionAbout_Dicom_Viewer = new QAction(QWindow);
        actionAbout_Dicom_Viewer->setObjectName(QStringLiteral("actionAbout_Dicom_Viewer"));
        QIcon icon;
        icon.addFile(QStringLiteral("Icons/info1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Dicom_Viewer->setIcon(icon);
        actionOpen = new QAction(QWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Icons/folder1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionOpenDicomDir = new QAction(QWindow);
        actionOpenDicomDir->setObjectName(QStringLiteral("actionOpenDicomDir"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Icons/directory1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenDicomDir->setIcon(icon2);
        actionOpen_Zip_file = new QAction(QWindow);
        actionOpen_Zip_file->setObjectName(QStringLiteral("actionOpen_Zip_file"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Icons/Zip file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Zip_file->setIcon(icon3);
        actionScan_for_Dicom_file = new QAction(QWindow);
        actionScan_for_Dicom_file->setObjectName(QStringLiteral("actionScan_for_Dicom_file"));
        actionPrint_Setup = new QAction(QWindow);
        actionPrint_Setup->setObjectName(QStringLiteral("actionPrint_Setup"));
        actionExit = new QAction(QWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Icons/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        actionToolBar = new QAction(QWindow);
        actionToolBar->setObjectName(QStringLiteral("actionToolBar"));
        actionCustomize = new QAction(QWindow);
        actionCustomize->setObjectName(QStringLiteral("actionCustomize"));
        actionOptions = new QAction(QWindow);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        centralwidget = new QWidget(QWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMinimumSize(QSize(1450, 700));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(11, 10, 1471, 761));
        splitter->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(splitter);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMinimumSize(QSize(250, 715));
        splitter->addWidget(listWidget);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(735, 720));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        view1 = new QVTKOpenGLWidget(tab_1);
        view1->setObjectName(QStringLiteral("view1"));
        view1->setEnabled(true);
        view1->setGeometry(QRect(10, 10, 710, 710));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(200);
        sizePolicy2.setVerticalStretch(200);
        sizePolicy2.setHeightForWidth(view1->sizePolicy().hasHeightForWidth());
        view1->setSizePolicy(sizePolicy2);
        view1->setMinimumSize(QSize(710, 710));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setMinimumSize(QSize(740, 740));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 709, 711));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        view2_3 = new QVTKOpenGLWidget(layoutWidget);
        view2_3->setObjectName(QStringLiteral("view2_3"));
        sizePolicy2.setHeightForWidth(view2_3->sizePolicy().hasHeightForWidth());
        view2_3->setSizePolicy(sizePolicy2);
        view2_3->setMinimumSize(QSize(350, 350));

        gridLayout->addWidget(view2_3, 1, 0, 1, 1);

        view2_2 = new QVTKOpenGLWidget(layoutWidget);
        view2_2->setObjectName(QStringLiteral("view2_2"));
        sizePolicy2.setHeightForWidth(view2_2->sizePolicy().hasHeightForWidth());
        view2_2->setSizePolicy(sizePolicy2);
        view2_2->setMinimumSize(QSize(350, 350));

        gridLayout->addWidget(view2_2, 0, 1, 1, 1);

        view2_4 = new QVTKOpenGLWidget(layoutWidget);
        view2_4->setObjectName(QStringLiteral("view2_4"));
        sizePolicy2.setHeightForWidth(view2_4->sizePolicy().hasHeightForWidth());
        view2_4->setSizePolicy(sizePolicy2);
        view2_4->setMinimumSize(QSize(350, 350));
        view2_4->setBaseSize(QSize(0, 0));

        gridLayout->addWidget(view2_4, 1, 1, 1, 1);

        view2_1 = new QVTKOpenGLWidget(layoutWidget);
        view2_1->setObjectName(QStringLiteral("view2_1"));
        view2_1->setEnabled(true);
        sizePolicy2.setHeightForWidth(view2_1->sizePolicy().hasHeightForWidth());
        view2_1->setSizePolicy(sizePolicy2);
        view2_1->setMinimumSize(QSize(350, 350));

        gridLayout->addWidget(view2_1, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        splitter->addWidget(tabWidget);
        tableWidget = new QTableWidget(splitter);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(450, 715));
        splitter->addWidget(tableWidget);
        QWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(QWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1490, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        QWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(QWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        QWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(QWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionOpenDicomDir);
        menuFile->addAction(actionOpen_Zip_file);
        menuFile->addAction(actionScan_for_Dicom_file);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint_Setup);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionToolBar);
        menuTools->addAction(actionCustomize);
        menuTools->addAction(actionOptions);
        menuHelp->addAction(actionAbout_Dicom_Viewer);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionOpenDicomDir);
        toolBar->addSeparator();
        toolBar->addAction(actionAbout_Dicom_Viewer);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(QWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QWindow)
    {
        QWindow->setWindowTitle(QApplication::translate("QWindow", "DICOM_VIEWER", Q_NULLPTR));
        actionAbout_Dicom_Viewer->setText(QApplication::translate("QWindow", "About Dicom_Viewer", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("QWindow", "Open", Q_NULLPTR));
        actionOpenDicomDir->setText(QApplication::translate("QWindow", "Open DicomDir...", Q_NULLPTR));
        actionOpen_Zip_file->setText(QApplication::translate("QWindow", "Open Zip file...", Q_NULLPTR));
        actionScan_for_Dicom_file->setText(QApplication::translate("QWindow", "Scan for Dicom file...", Q_NULLPTR));
        actionPrint_Setup->setText(QApplication::translate("QWindow", "Print Setup", Q_NULLPTR));
        actionExit->setText(QApplication::translate("QWindow", "Exit", Q_NULLPTR));
        actionToolBar->setText(QApplication::translate("QWindow", "ToolBar", Q_NULLPTR));
        actionCustomize->setText(QApplication::translate("QWindow", "Customize", Q_NULLPTR));
        actionOptions->setText(QApplication::translate("QWindow", "Options...", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("QWindow", "2D view", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QWindow", "3D view", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QWindow", "(Group, Element)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QWindow", "Tag description", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QWindow", "Value", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("QWindow", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("QWindow", "View", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("QWindow", "Tools", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("QWindow", "Help", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("QWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QWindow: public Ui_QWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
