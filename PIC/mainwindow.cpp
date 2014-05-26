#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steuerwerk.h"

#include "codezeile.h"
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
    startButton = ui->go;
    schrittButton = ui->schritt;
    speicherAnsicht = ui->speicherAnzeige;
    hilfeButton=ui->hilfe;

    speicherAnsichtInitialisieren();

    // Buttonfunktionen definieren
    connect(suchenButton, SIGNAL(clicked()), SLOT(oeffneDateiBrowserDialog()));
    connect(ladenButton, SIGNAL(clicked()), SLOT(ladeLstDatei()));
    connect(schrittButton, SIGNAL(clicked()), SLOT(schrittAusfuehren()));
    connect(hilfeButton, SIGNAL(clicked()), SLOT(hilfeOeffnen()));
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

    neuZeichnenProgrammzaehler();
    neuZeichnenW();
    neuZeichnenZ();
    neuZeichnenC();
    neuZeichnenDC();
    neuZeichnenStatus();
}

void MainWindow::schrittAusfuehren()
{
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
    z = ((z&4)>>2);
    QString zero = (HexConverter::intToHex(z));
    zLabel ->setText(zero);
}

//Aktualisierung des Carry-Bits
void MainWindow::neuZeichnenC()
{
    int c = steuerwerk->getRam()->lesen(Ram::STATUS);
    c = ((c&1)>>0);
    QString carry = (HexConverter::intToHex(c));
    cLabel ->setText(carry);
}

//Aktualisierung des Carry-Bits
void MainWindow::neuZeichnenDC()
{
    int dc = steuerwerk->getRam()->lesen(Ram::STATUS);
    dc = ((dc&2)>>1);
    QString digitcarry = (HexConverter::intToHex(dc));
    dcLabel ->setText(digitcarry);
}

//Aktualisierung des Status-Registers
void MainWindow::neuZeichnenStatus()
{
    statusLabel ->setText(HexConverter::intToHex(steuerwerk->getRam()->lesen(Ram::STATUS)));
}

//Aktualisierung der Ansicht für den Speicherinhalt
void MainWindow::neuZeichnenSpeicherAnsicht()
{
    for(int adresse = 0; adresse < 0x50; adresse++)
    {
        speicherAnsicht->item(adresse, 1)->setText(QString::number(steuerwerk->getRam()->lesen(adresse, 0)));
        speicherAnsicht->item(adresse, 2)->setText(QString::number(steuerwerk->getRam()->lesen(adresse, 1)));
    }
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
}

//Öffnen der Help-PDF
void MainWindow::hilfeOeffnen()
{
    QString path = QDir::currentPath();

    QDesktopServices::openUrl(QUrl(path + "/help.pdf"));

}

void MainWindow::fokusAufAktuelleProgrammzeile()
{
    for(int i = 0; i < befehlslisteWidget->count(); i++)
        befehlslisteWidget->item(i)->setBackground(Qt::white);

    int adresse = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS);
    int textzeile = steuerwerk->getProgrammspeicher()->getCodezeileAt(adresse)->getTextzeile();

    befehlslisteWidget->item(textzeile)->setBackground(Qt::green);
}
