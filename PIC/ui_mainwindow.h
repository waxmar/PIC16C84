/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *dateiname;
    QListWidget *befehlsliste;
    QListWidget *stack;
    QTableWidget *speicherAnzeige;
    QPushButton *hilfe;
    QLabel *stack_2;
    QTableWidget *registerA;
    QTableWidget *registerB;
    QLabel *ra;
    QLabel *rb;
    QLabel *spezialregister;
    QSplitter *splitter;
    QPushButton *suchen;
    QPushButton *laden;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *go;
    QPushButton *schritt;
    QPushButton *reset;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *Programmzaehler;
    QLabel *programmzaehler;
    QLabel *WRegister;
    QLabel *w_reg;
    QLabel *ZeroBit;
    QLabel *z;
    QLabel *CarryBit;
    QLabel *c;
    QLabel *DCBit;
    QLabel *dc;
    QLabel *FSR;
    QLabel *fsr;
    QLabel *PCLATH;
    QLabel *pclath;
    QLabel *STATUS;
    QLabel *status;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1166, 593);
        MainWindow->setMaximumSize(QSize(1166, 593));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dateiname = new QLineEdit(centralWidget);
        dateiname->setObjectName(QStringLiteral("dateiname"));
        dateiname->setGeometry(QRect(130, 10, 741, 20));
        befehlsliste = new QListWidget(centralWidget);
        befehlsliste->setObjectName(QStringLiteral("befehlsliste"));
        befehlsliste->setGeometry(QRect(130, 130, 741, 401));
        stack = new QListWidget(centralWidget);
        stack->setObjectName(QStringLiteral("stack"));
        stack->setGeometry(QRect(630, 60, 101, 51));
        speicherAnzeige = new QTableWidget(centralWidget);
        speicherAnzeige->setObjectName(QStringLiteral("speicherAnzeige"));
        speicherAnzeige->setGeometry(QRect(880, 40, 256, 491));
        hilfe = new QPushButton(centralWidget);
        hilfe->setObjectName(QStringLiteral("hilfe"));
        hilfe->setGeometry(QRect(930, 10, 75, 23));
        stack_2 = new QLabel(centralWidget);
        stack_2->setObjectName(QStringLiteral("stack_2"));
        stack_2->setGeometry(QRect(630, 40, 46, 13));
        registerA = new QTableWidget(centralWidget);
        if (registerA->columnCount() < 8)
            registerA->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        registerA->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (registerA->rowCount() < 2)
            registerA->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        registerA->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        registerA->setVerticalHeaderItem(1, __qtablewidgetitem9);
        registerA->setObjectName(QStringLiteral("registerA"));
        registerA->setGeometry(QRect(150, 40, 191, 81));
        registerA->horizontalHeader()->setDefaultSectionSize(20);
        registerA->horizontalHeader()->setMinimumSectionSize(20);
        registerA->verticalHeader()->setDefaultSectionSize(25);
        registerA->verticalHeader()->setMinimumSectionSize(20);
        registerB = new QTableWidget(centralWidget);
        if (registerB->columnCount() < 8)
            registerB->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        registerB->setHorizontalHeaderItem(7, __qtablewidgetitem17);
        if (registerB->rowCount() < 2)
            registerB->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        registerB->setVerticalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        registerB->setVerticalHeaderItem(1, __qtablewidgetitem19);
        registerB->setObjectName(QStringLiteral("registerB"));
        registerB->setEnabled(true);
        registerB->setGeometry(QRect(390, 40, 191, 81));
        registerB->setCornerButtonEnabled(false);
        registerB->horizontalHeader()->setDefaultSectionSize(20);
        registerB->horizontalHeader()->setMinimumSectionSize(20);
        registerB->verticalHeader()->setDefaultSectionSize(25);
        registerB->verticalHeader()->setMinimumSectionSize(20);
        ra = new QLabel(centralWidget);
        ra->setObjectName(QStringLiteral("ra"));
        ra->setGeometry(QRect(130, 40, 21, 16));
        rb = new QLabel(centralWidget);
        rb->setObjectName(QStringLiteral("rb"));
        rb->setGeometry(QRect(370, 40, 21, 16));
        spezialregister = new QLabel(centralWidget);
        spezialregister->setObjectName(QStringLiteral("spezialregister"));
        spezialregister->setGeometry(QRect(20, 120, 71, 25));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(10, 10, 75, 46));
        splitter->setOrientation(Qt::Vertical);
        suchen = new QPushButton(splitter);
        suchen->setObjectName(QStringLiteral("suchen"));
        splitter->addWidget(suchen);
        laden = new QPushButton(splitter);
        laden->setObjectName(QStringLiteral("laden"));
        splitter->addWidget(laden);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 330, 77, 83));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        go = new QPushButton(layoutWidget);
        go->setObjectName(QStringLiteral("go"));

        verticalLayout->addWidget(go);

        schritt = new QPushButton(layoutWidget);
        schritt->setObjectName(QStringLiteral("schritt"));

        verticalLayout->addWidget(schritt);

        reset = new QPushButton(layoutWidget);
        reset->setObjectName(QStringLiteral("reset"));

        verticalLayout->addWidget(reset);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 151, 101, 148));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Programmzaehler = new QLabel(layoutWidget1);
        Programmzaehler->setObjectName(QStringLiteral("Programmzaehler"));

        gridLayout->addWidget(Programmzaehler, 0, 0, 1, 1);

        programmzaehler = new QLabel(layoutWidget1);
        programmzaehler->setObjectName(QStringLiteral("programmzaehler"));

        gridLayout->addWidget(programmzaehler, 0, 1, 1, 1);

        WRegister = new QLabel(layoutWidget1);
        WRegister->setObjectName(QStringLiteral("WRegister"));

        gridLayout->addWidget(WRegister, 1, 0, 1, 1);

        w_reg = new QLabel(layoutWidget1);
        w_reg->setObjectName(QStringLiteral("w_reg"));

        gridLayout->addWidget(w_reg, 1, 1, 1, 1);

        ZeroBit = new QLabel(layoutWidget1);
        ZeroBit->setObjectName(QStringLiteral("ZeroBit"));

        gridLayout->addWidget(ZeroBit, 2, 0, 1, 1);

        z = new QLabel(layoutWidget1);
        z->setObjectName(QStringLiteral("z"));

        gridLayout->addWidget(z, 2, 1, 1, 1);

        CarryBit = new QLabel(layoutWidget1);
        CarryBit->setObjectName(QStringLiteral("CarryBit"));

        gridLayout->addWidget(CarryBit, 3, 0, 1, 1);

        c = new QLabel(layoutWidget1);
        c->setObjectName(QStringLiteral("c"));

        gridLayout->addWidget(c, 3, 1, 1, 1);

        DCBit = new QLabel(layoutWidget1);
        DCBit->setObjectName(QStringLiteral("DCBit"));

        gridLayout->addWidget(DCBit, 4, 0, 1, 1);

        dc = new QLabel(layoutWidget1);
        dc->setObjectName(QStringLiteral("dc"));

        gridLayout->addWidget(dc, 4, 1, 1, 1);

        FSR = new QLabel(layoutWidget1);
        FSR->setObjectName(QStringLiteral("FSR"));

        gridLayout->addWidget(FSR, 5, 0, 1, 1);

        fsr = new QLabel(layoutWidget1);
        fsr->setObjectName(QStringLiteral("fsr"));

        gridLayout->addWidget(fsr, 5, 1, 1, 1);

        PCLATH = new QLabel(layoutWidget1);
        PCLATH->setObjectName(QStringLiteral("PCLATH"));

        gridLayout->addWidget(PCLATH, 6, 0, 1, 1);

        pclath = new QLabel(layoutWidget1);
        pclath->setObjectName(QStringLiteral("pclath"));

        gridLayout->addWidget(pclath, 6, 1, 1, 1);

        STATUS = new QLabel(layoutWidget1);
        STATUS->setObjectName(QStringLiteral("STATUS"));

        gridLayout->addWidget(STATUS, 7, 0, 1, 1);

        status = new QLabel(layoutWidget1);
        status->setObjectName(QStringLiteral("status"));

        gridLayout->addWidget(status, 7, 1, 1, 1);

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
        hilfe->setText(QApplication::translate("MainWindow", "HILFE", 0));
        stack_2->setText(QApplication::translate("MainWindow", "Stack", 0));
        QTableWidgetItem *___qtablewidgetitem = registerA->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "7", 0));
        QTableWidgetItem *___qtablewidgetitem1 = registerA->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "6", 0));
        QTableWidgetItem *___qtablewidgetitem2 = registerA->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "5", 0));
        QTableWidgetItem *___qtablewidgetitem3 = registerA->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "4", 0));
        QTableWidgetItem *___qtablewidgetitem4 = registerA->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "3", 0));
        QTableWidgetItem *___qtablewidgetitem5 = registerA->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "2", 0));
        QTableWidgetItem *___qtablewidgetitem6 = registerA->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "1", 0));
        QTableWidgetItem *___qtablewidgetitem7 = registerA->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "0", 0));
        QTableWidgetItem *___qtablewidgetitem8 = registerA->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Tris", 0));
        QTableWidgetItem *___qtablewidgetitem9 = registerA->verticalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Pin", 0));
        QTableWidgetItem *___qtablewidgetitem10 = registerB->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "7", 0));
        QTableWidgetItem *___qtablewidgetitem11 = registerB->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "6", 0));
        QTableWidgetItem *___qtablewidgetitem12 = registerB->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "5", 0));
        QTableWidgetItem *___qtablewidgetitem13 = registerB->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "4", 0));
        QTableWidgetItem *___qtablewidgetitem14 = registerB->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "3", 0));
        QTableWidgetItem *___qtablewidgetitem15 = registerB->horizontalHeaderItem(5);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "2", 0));
        QTableWidgetItem *___qtablewidgetitem16 = registerB->horizontalHeaderItem(6);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "1", 0));
        QTableWidgetItem *___qtablewidgetitem17 = registerB->horizontalHeaderItem(7);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "0", 0));
        QTableWidgetItem *___qtablewidgetitem18 = registerB->verticalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "Tris", 0));
        QTableWidgetItem *___qtablewidgetitem19 = registerB->verticalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "Pin", 0));
        ra->setText(QApplication::translate("MainWindow", "RA", 0));
        rb->setText(QApplication::translate("MainWindow", "RB", 0));
        spezialregister->setText(QApplication::translate("MainWindow", "Spezialregister", 0));
        suchen->setText(QApplication::translate("MainWindow", "Suchen", 0));
        laden->setText(QApplication::translate("MainWindow", "Laden", 0));
        go->setText(QApplication::translate("MainWindow", "GO", 0));
        schritt->setText(QApplication::translate("MainWindow", "Schritt", 0));
        reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        Programmzaehler->setText(QApplication::translate("MainWindow", "PC", 0));
        programmzaehler->setText(QApplication::translate("MainWindow", "PC", 0));
        WRegister->setText(QApplication::translate("MainWindow", "W-Reg", 0));
        w_reg->setText(QApplication::translate("MainWindow", "w_reg", 0));
        ZeroBit->setText(QApplication::translate("MainWindow", "Zero-Bit", 0));
        z->setText(QApplication::translate("MainWindow", "Z", 0));
        CarryBit->setText(QApplication::translate("MainWindow", "Carry-Bit", 0));
        c->setText(QApplication::translate("MainWindow", "C", 0));
        DCBit->setText(QApplication::translate("MainWindow", "DC-Bit", 0));
        dc->setText(QApplication::translate("MainWindow", "DC", 0));
        FSR->setText(QApplication::translate("MainWindow", "FSR", 0));
        fsr->setText(QApplication::translate("MainWindow", "FSR", 0));
        PCLATH->setText(QApplication::translate("MainWindow", "PCLATH", 0));
        pclath->setText(QApplication::translate("MainWindow", "PCLATH", 0));
        STATUS->setText(QApplication::translate("MainWindow", "STATUS", 0));
        status->setText(QApplication::translate("MainWindow", "STATUS", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
