/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QLabel *label;
    QLabel *la_image_view;
    QWidget *tab_2;
    QLabel *label_2;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QWidget *tab;
    QLabel *label_3;
    QLabel *lnetworks;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(732, 454);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 731, 421));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tabWidget = new QTabWidget(frame);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 731, 421));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        label = new QLabel(tab_1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 141, 17));
        la_image_view = new QLabel(tab_1);
        la_image_view->setObjectName(QStringLiteral("la_image_view"));
        la_image_view->setGeometry(QRect(10, 40, 701, 331));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 221, 17));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(620, 10, 97, 26));
        tableWidget = new QTableWidget(tab_2);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 711, 341));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 191, 17));
        lnetworks = new QLabel(tab);
        lnetworks->setObjectName(QStringLiteral("lnetworks"));
        lnetworks->setEnabled(true);
        lnetworks->setGeometry(QRect(160, 20, 521, 161));
        QFont font;
        font.setFamily(QStringLiteral("Tlwg Typo"));
        font.setPointSize(12);
        lnetworks->setFont(font);
        lnetworks->setLineWidth(1);
        lnetworks->setTextFormat(Qt::PlainText);
        lnetworks->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        tabWidget->addTab(tab, QString());
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Imagens Recebidas", 0));
        la_image_view->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Updates", 0));
        label_2->setText(QApplication::translate("MainWindow", "Dados das pessoas autenticadas", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Atualizar", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Infos", 0));
        label_3->setText(QApplication::translate("MainWindow", "Interfaces de Rede:", 0));
        lnetworks->setText(QApplication::translate("MainWindow", "TextLabel", "1"));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Config", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
