#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steuerwerk.h"

#include "codezeile.h"
#include "bitoperationen.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include "qfiledialog.h"
#include <qlistwidget.h>
#include "programmspeicher.h"
#include "programmzaehler.h"
#include "wregister.h"
#include "stack.h"
#include "ram.h"
#include "hexconverter.h"
#include <qlabel.h>
#include <QDesktopServices>
#include <QUrl>

#include "parser.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Übergabe des Objektes steuerwerk, Verbindung zwischen Steuerwerk und MainWindow
    steuerwerk = new Steuerwerk(this);

    // GUI Elemente
    dateinameLineEdit = ui->dateiname;
    suchenButton = ui->suchen;
    ladenButton = ui->laden;
    befehlslisteWidget = ui->befehlsliste;
    stackWidget = ui->stack;
    programmzaehlerLabel = ui->programmzaehler;
    wregisterLabel = ui->w_reg;
    zLabel = ui->z;
    cLabel = ui->c;
    dcLabel = ui->dc;
    statusLabel = ui->status;
    fsrLabel = ui->fsr;
    pclathLabel = ui->pclath;
    startButton = ui->go;
    schrittButton = ui->schritt;
    resetButton = ui->reset;
    speicherAnsicht = ui->speicherAnzeige;
    registerA = ui->registerA;
    registerB = ui->registerB;
    hilfeButton=ui->hilfe;

    speicherAnsichtInitialisieren();
    registerAnsichtInitialisieren();

    // Buttonfunktionen definieren
    connect(suchenButton, SIGNAL(clicked()), SLOT(oeffneDateiBrowserDialog()));
    connect(ladenButton, SIGNAL(clicked()), SLOT(ladeLstDatei()));
    connect(schrittButton, SIGNAL(clicked()), SLOT(schrittAusfuehren()));
    connect(hilfeButton, SIGNAL(clicked()), SLOT(hilfeOeffnen()));
    connect(resetButton, SIGNAL(clicked()), SLOT(resetUI()));
    connect(startButton, SIGNAL(clicked()), SLOT(programmAusfuehren()));
    connect(befehlslisteWidget, SIGNAL(doubleClicked(QModelIndex)), SLOT(setzeBreakpoint(QModelIndex)));
    connect(registerB, SIGNAL(cellClicked(int,int)), this, SLOT(registerAnsichtAendern(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Funktion zum Öffnen des Browsers und suchen der .lst Datei
void MainWindow::oeffneDateiBrowserDialog()
{
    QString dateiName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));
    dateinameLineEdit->clear();
    dateinameLineEdit->setText(dateiName);
}

// Funktion zum Laden der .lst Datei in den Parser
void MainWindow::ladeLstDatei()
{
    // Beginn Initialisierung
    // INIT programmspeicher
    QString speicherOrt = dateinameLineEdit->text();
    Parser::parsen(speicherOrt, steuerwerk, befehlslisteWidget);

    // INIT programmzaehler
    QList<Codezeile>::iterator startAdresse = steuerwerk->getProgrammspeicher()->getErsteAdresse();
    steuerwerk->getProgrammzaehler()->initialisieren(startAdresse);

    erneuernUI();
}

void MainWindow::programmAusfuehren()
{
    //alle Schritte nacheinander ausführen
}

void MainWindow::resetUI()
{
    //alle Werte zurücksetzen
}

void MainWindow::schrittAusfuehren()
{
    fokusAlteProgrammzeileEntfernen();

    steuerwerk->schrittSteuern();
}

//Aktualisierung des Stack-Widgets
void MainWindow::neuZeichnenStack()
{
    stackWidget->clear();

    QList<int>* stackInhalt = steuerwerk->getStack()->getInhalt();
    QList<int>::iterator stackElement;

    for(stackElement = stackInhalt->begin(); stackElement != stackInhalt->end(); stackElement++)
    {
        QListWidgetItem* stackWidgetItem = new QListWidgetItem(HexConverter::intToHex(*stackElement));
        stackWidget->addItem(stackWidgetItem);
    }
}

//Aktualisierung des Programmzählers
void MainWindow::neuZeichnenProgrammzaehler()
{
    programmzaehlerLabel->setText(HexConverter::intToHex(steuerwerk->getProgrammzaehler()->lesen(-1)));
}

//Aktualisierung des W-Registers
void MainWindow::neuZeichnenW()
{
    wregisterLabel ->setText(HexConverter::intToHex(steuerwerk->getW()->lesen(-1)));
}

//Aktualisierung des Zero-Bits
void MainWindow::neuZeichnenZ()
{
    int z = steuerwerk->getRam()->lesen(Ram::STATUS);
    zLabel ->setText(QString::number((z&4)>>2));
}

//Aktualisierung des Carry-Bits
void MainWindow::neuZeichnenC()
{
    int c = steuerwerk->getRam()->lesen(Ram::STATUS);
    cLabel ->setText(QString::number((c&1)>>0));
}

//Aktualisierung des Carry-Bits
void MainWindow::neuZeichnenDC()
{
    int dc = steuerwerk->getRam()->lesen(Ram::STATUS);
    dcLabel ->setText(QString::number((dc&2)>>1));
}

//Aktualisierung des Status-Registers
void MainWindow::neuZeichnenStatus()
{
    statusLabel ->setText(HexConverter::intToHex(steuerwerk->getRam()->lesen(Ram::STATUS)));
}

//Aktualisierung des FSR-Registers
void MainWindow::neuZeichnenFSR()
{
    fsrLabel ->setText(HexConverter::intToHex(steuerwerk->getRam()->lesen(Ram::FSR)));
}

//Aktualisierung des PCLATH-Registers
void MainWindow::neuZeichnenPCLATH()
{
    pclathLabel ->setText(HexConverter::intToHex(steuerwerk->getRam()->lesen(Ram::PCLATH)));
}

//Aktualisierung der Ansicht für den Speicherinhalt
void MainWindow::neuZeichnenSpeicherAnsicht()
{
    for(int adresse = 0; adresse < 0x50; adresse++)
    {
        speicherAnsicht->item(adresse, 1)->setText(HexConverter::intToHex(steuerwerk->getRam()->lesen(adresse, 0)));
        speicherAnsicht->item(adresse, 2)->setText(HexConverter::intToHex(steuerwerk->getRam()->lesen(adresse, 1)));
    }
}

//Aktualisierung der Ansicht für den Registerinhalt
void MainWindow::neuZeichnenRegisterAnsicht()
{
    for (int i = 0; i < 8; i++)
    {
    registerA->setItem(1,i,new QTableWidgetItem(QString::number(Bitoperationen::zeigeBit(0x05,7-i))));
    registerA->setItem(0,i,new QTableWidgetItem("i"));
    registerB->setItem(1,i,new QTableWidgetItem(QString::number(Bitoperationen::zeigeBit(0x06,7-i))));
    registerB->setItem(0,i,new QTableWidgetItem("i"));
    }
}

//Ansicht des Registers B �ndern
void MainWindow::registerAnsichtAendern(int reihe, int spalte)
{
    Bitoperationen::setzeBit(steuerwerk->getRam()->lesen(0x06,0),7-spalte);
    std::cout << "PortB = " << steuerwerk->getRam()->lesen(0x06) << std::endl;
    registerAnsichtInitialisieren();
    neuZeichnenRegisterAnsicht();
}

//Initialisierung der Ansicht für den Speicherinhalt
void MainWindow::speicherAnsichtInitialisieren()
{
    speicherAnsicht->setRowCount(0x50);

    speicherAnsicht->setColumnCount(3);
    speicherAnsicht->setColumnWidth(0, 60);
    speicherAnsicht->setColumnWidth(1, 60);
    speicherAnsicht->setColumnWidth(2, 60);

    speicherAnsicht->setHorizontalHeaderItem(0,new QTableWidgetItem("Adresse"));
    speicherAnsicht->setHorizontalHeaderItem(1,new QTableWidgetItem("Bank0"));
    speicherAnsicht->setHorizontalHeaderItem(2, new QTableWidgetItem("Bank1"));

    for(int adresse = 0; adresse < 0x50; adresse++)
    {
        speicherAnsicht->setItem(adresse, 0, new QTableWidgetItem(HexConverter::intToHex(adresse)));
        speicherAnsicht->setItem(adresse, 1, new QTableWidgetItem(HexConverter::intToHex(steuerwerk->getRam()->lesen(adresse, 0))));
        speicherAnsicht->setItem(adresse, 2, new QTableWidgetItem(HexConverter::intToHex(steuerwerk->getRam()->lesen(adresse, 1))));
    }
}

//Initialisierung der Ansicht für den Registerinhalt
void MainWindow::registerAnsichtInitialisieren()
{
    for (int i = 0; i < 8; i++)
    {
    registerA->setItem(1,i,new QTableWidgetItem(QString::number(Bitoperationen::zeigeBit(0x05,7-i))));
    if (Bitoperationen::zeigeBit( steuerwerk->getRam()->lesen(0x05,1),7-i) == 1)
                registerA->setItem(0,i,new QTableWidgetItem("i"));
    else
                registerA->setItem(0,i,new QTableWidgetItem("o"));

    registerB->setItem(1,i,new QTableWidgetItem(QString::number(Bitoperationen::zeigeBit(0x06,7-i))));
    if (Bitoperationen::zeigeBit( steuerwerk->getRam()->lesen(0x06,1),7-i) == 1)
                registerB->setItem(0,i,new QTableWidgetItem("i"));
    else
                registerB->setItem(0,i,new QTableWidgetItem("o"));
    }

}

//Aktualiserung der gesamten Benutzeroberfläche
void MainWindow::erneuernUI()
{
    neuZeichnenProgrammzaehler();
    neuZeichnenStack();
    neuZeichnenSpeicherAnsicht();
    fokusAufAktuelleProgrammzeile();
    neuZeichnenW();
    neuZeichnenZ();
    neuZeichnenC();
    neuZeichnenDC();
    neuZeichnenStatus();
    neuZeichnenFSR();
    neuZeichnenPCLATH();
    neuZeichnenRegisterAnsicht();
}

//Öffnen der Help-PDF
void MainWindow::hilfeOeffnen()
{
    QString path = QDir::currentPath();

    QDesktopServices::openUrl(QUrl(path + "/help.pdf"));

}

void MainWindow::fokusAlteProgrammzeileEntfernen()
{
    int adresse = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS);
    int textzeile = steuerwerk->getProgrammspeicher()->getCodezeileAt(adresse)->getTextzeile();

    befehlslisteWidget->item(textzeile)->setBackground(Qt::white);
}

void MainWindow::fokusAufAktuelleProgrammzeile()
{
    int adresse = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS);
    int textzeile = steuerwerk->getProgrammspeicher()->getCodezeileAt(adresse)->getTextzeile();

    befehlslisteWidget->item(textzeile)->setBackground(Qt::green);
    befehlslisteWidget->setCurrentRow(textzeile);
    befehlslisteWidget->clearSelection();
}

void MainWindow::setzeBreakpoint(QModelIndex index)
{
    int textzeile = index.row();

    cout << "Line clicked " << textzeile << endl;

    Codezeile* breakpointZeile = steuerwerk->getProgrammspeicher()->findCodezeileByLinenumber(textzeile);

    if(breakpointZeile == NULL)
        return;

    breakpointZeile->toggleBreakpoint();

    if(breakpointZeile->isBreakpoint())
        befehlslisteWidget->item(textzeile)->setBackground(Qt::yellow);
    else
        befehlslisteWidget->item(textzeile)->setBackground(Qt::white);

    befehlslisteWidget->clearSelection();
}
