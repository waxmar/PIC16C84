/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *dateiname;
    QPushButton *laden;
    QPushButton *suchen;
    QListWidget *befehlsliste;
    QLabel *programmzaehler;
    QPushButton *go;
    QPushButton *schritt;
    QListWidget *stack;
    QTableWidget *speicherAnzeige;
    QPushButton *hilfe;
    QLabel *w_reg;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1166, 593);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dateiname = new QLineEdit(centralWidget);
        dateiname->setObjectName(QStringLiteral("dateiname"));
        dateiname->setGeometry(QRect(130, 10, 113, 20));
        laden = new QPushButton(centralWidget);
        laden->setObjectName(QStringLiteral("laden"));
        laden->setGeometry(QRect(30, 40, 75, 23));
        suchen = new QPushButton(centralWidget);
        suchen->setObjectName(QStringLiteral("suchen"));
        suchen->setGeometry(QRect(30, 10, 75, 23));
        befehlsliste = new QListWidget(centralWidget);
        befehlsliste->setObjectName(QStringLiteral("befehlsliste"));
        befehlsliste->setGeometry(QRect(130, 40, 741, 451));
        programmzaehler = new QLabel(centralWidget);
        programmzaehler->setObjectName(QStringLiteral("programmzaehler"));
        programmzaehler->setGeometry(QRect(40, 80, 46, 13));
        go = new QPushButton(centralWidget);
        go->setObjectName(QStringLiteral("go"));
        go->setGeometry(QRect(30, 120, 75, 23));
        schritt = new QPushButton(centralWidget);
        schritt->setObjectName(QStringLiteral("schritt"));
        schritt->setGeometry(QRect(10, 150, 111, 23));
        stack = new QListWidget(centralWidget);
        stack->setObjectName(QStringLiteral("stack"));
        stack->setGeometry(QRect(20, 190, 101, 192));
        speicherAnzeige = new QTableWidget(centralWidget);
        speicherAnzeige->setObjectName(QStringLiteral("speicherAnzeige"));
        speicherAnzeige->setGeometry(QRect(880, 40, 256, 371));
        hilfe = new QPushButton(centralWidget);
        hilfe->setObjectName(QStringLiteral("hilfe"));
        hilfe->setGeometry(QRect(930, 10, 75, 23));
        w_reg = new QLabel(centralWidget);
        w_reg->setObjectName(QStringLiteral("w_reg"));
        w_reg->setGeometry(QRect(40, 100, 46, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1166, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        laden->setText(QApplication::translate("MainWindow", "Laden", 0));
        suchen->setText(QApplication::translate("MainWindow", "Suchen", 0));
        programmzaehler->setText(QApplication::translate("MainWindow", "PC", 0));
        go->setText(QApplication::translate("MainWindow", "GO", 0));
        schritt->setText(QApplication::translate("MainWindow", "Schritt ausf\303\274hren", 0));
        hilfe->setText(QApplication::translate("MainWindow", "HILFE", 0));
        w_reg->setText(QApplication::translate("MainWindow", "w_reg", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
