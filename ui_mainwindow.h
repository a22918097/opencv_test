/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QWidget *centralWidget;
    QPushButton *pushButton_Read;
    QLabel *label_cam_L;
    QPushButton *pushButton_close;
    QLabel *label_cam_R;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_play;
    QLabel *save_L;
    QLabel *save_R;
    QPushButton *pushButton_save;
    QLabel *label_disp;
    QCheckBox *checkBox_pseudo_color;
    QCheckBox *checkBox_do_depth;
    QLabel *label_color_table;
    QLabel *label_disp_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1800, 1000);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_Read = new QPushButton(centralWidget);
        pushButton_Read->setObjectName(QStringLiteral("pushButton_Read"));
        pushButton_Read->setGeometry(QRect(30, 20, 91, 81));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(16);
        pushButton_Read->setFont(font);
        label_cam_L = new QLabel(centralWidget);
        label_cam_L->setObjectName(QStringLiteral("label_cam_L"));
        label_cam_L->setGeometry(QRect(200, 0, 450, 450));
        pushButton_close = new QPushButton(centralWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(1520, 30, 141, 111));
        pushButton_close->setFont(font);
        label_cam_R = new QLabel(centralWidget);
        label_cam_R->setObjectName(QStringLiteral("label_cam_R"));
        label_cam_R->setGeometry(QRect(200, 460, 450, 450));
        pushButton_pause = new QPushButton(centralWidget);
        pushButton_pause->setObjectName(QStringLiteral("pushButton_pause"));
        pushButton_pause->setGeometry(QRect(30, 130, 91, 81));
        pushButton_pause->setFont(font);
        pushButton_play = new QPushButton(centralWidget);
        pushButton_play->setObjectName(QStringLiteral("pushButton_play"));
        pushButton_play->setGeometry(QRect(30, 240, 91, 81));
        pushButton_play->setFont(font);
        save_L = new QLabel(centralWidget);
        save_L->setObjectName(QStringLiteral("save_L"));
        save_L->setGeometry(QRect(740, 0, 450, 450));
        save_R = new QLabel(centralWidget);
        save_R->setObjectName(QStringLiteral("save_R"));
        save_R->setGeometry(QRect(740, 460, 450, 450));
        pushButton_save = new QPushButton(centralWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(30, 350, 91, 81));
        pushButton_save->setFont(font);
        label_disp = new QLabel(centralWidget);
        label_disp->setObjectName(QStringLiteral("label_disp"));
        label_disp->setGeometry(QRect(1230, 510, 501, 391));
        checkBox_pseudo_color = new QCheckBox(centralWidget);
        checkBox_pseudo_color->setObjectName(QStringLiteral("checkBox_pseudo_color"));
        checkBox_pseudo_color->setGeometry(QRect(20, 480, 111, 16));
        checkBox_do_depth = new QCheckBox(centralWidget);
        checkBox_do_depth->setObjectName(QStringLiteral("checkBox_do_depth"));
        checkBox_do_depth->setGeometry(QRect(21, 451, 73, 16));
        label_color_table = new QLabel(centralWidget);
        label_color_table->setObjectName(QStringLiteral("label_color_table"));
        label_color_table->setGeometry(QRect(1240, 920, 300, 15));
        label_disp_2 = new QLabel(centralWidget);
        label_disp_2->setObjectName(QStringLiteral("label_disp_2"));
        label_disp_2->setGeometry(QRect(710, 550, 501, 391));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        pushButton_Read->setText(QApplication::translate("MainWindow", "Read image", 0));
        label_cam_L->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton_close->setText(QApplication::translate("MainWindow", "CLOSE", 0));
        label_cam_R->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton_pause->setText(QApplication::translate("MainWindow", "Pause", 0));
        pushButton_play->setText(QApplication::translate("MainWindow", "Play", 0));
        save_L->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        save_R->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pushButton_save->setText(QApplication::translate("MainWindow", "Save", 0));
        label_disp->setText(QApplication::translate("MainWindow", "Disparity", 0));
        checkBox_pseudo_color->setText(QApplication::translate("MainWindow", "Pseudo-color", 0));
        checkBox_do_depth->setText(QApplication::translate("MainWindow", "Do depth", 0));
        label_color_table->setText(QApplication::translate("MainWindow", "ColorTable", 0));
        label_disp_2->setText(QApplication::translate("MainWindow", "Disparity", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
