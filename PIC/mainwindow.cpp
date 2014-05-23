#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steuerwerk.h"

#include "qpushbutton.h"
#include "qlineedit.h"
#include "qfiledialog.h"
#include <qlistwidget.h>
#include "programmspeicher.h"
#include "programmzaehler.h"
#include "stack.h"
#include "ram.h"
#include <qlabel.h>

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
    startButton = ui->go;
    schrittButton = ui->schritt;
    speicherAnsicht = ui->speicherAnzeige;

    speicherAnsichtInitialisieren();

    // Buttonfunktionen definieren
    connect(suchenButton, SIGNAL(clicked()), SLOT(oeffneDateiBrowserDialog()));
    connect(ladenButton, SIGNAL(clicked()), SLOT(ladeLstDatei()));
    connect(schrittButton, SIGNAL(clicked()), SLOT(schrittAusfuehren()));
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
}

void MainWindow::schrittAusfuehren()
{
    steuerwerk->schrittSteuern();
}

void MainWindow::neuZeichnenStack()
{
    stackWidget->clear();

    QList<int>* stackInhalt = steuerwerk->getStack()->getInhalt();
    QList<int>::iterator stackElement;

    for(stackElement = stackInhalt->begin(); stackElement != stackInhalt->end(); stackElement++)
    {
        QListWidgetItem* stackWidgetItem = new QListWidgetItem(QString::number(*stackElement));
        stackWidget->addItem(stackWidgetItem);
    }
}

void MainWindow::neuZeichnenProgrammzaehler()
{
    programmzaehlerLabel->setText(QString::number(steuerwerk->getProgrammzaehler()->lesen(-1)));
}

void MainWindow::neuZeichnenSpeicherAnsicht()
{
    for(int adresse = 0; adresse < 0x50; adresse++)
    {
        speicherAnsicht->item(adresse, 1)->setText(QString::number(steuerwerk->getRam()->lesen(adresse, 0)));
        speicherAnsicht->item(adresse, 2)->setText(QString::number(steuerwerk->getRam()->lesen(adresse, 1)));
    }
}

void MainWindow::speicherAnsichtInitialisieren()
{
    speicherAnsicht->setRowCount(0x50);

    speicherAnsicht->setColumnCount(3);
    speicherAnsicht->setColumnWidth(0, 60);
    speicherAnsicht->setColumnWidth(1, 36);
    speicherAnsicht->setColumnWidth(2, 36);

    speicherAnsicht->setHorizontalHeaderItem(0,new QTableWidgetItem("Adresse"));
    speicherAnsicht->setHorizontalHeaderItem(1,new QTableWidgetItem("Bank0"));
    speicherAnsicht->setHorizontalHeaderItem(2, new QTableWidgetItem("Bank1"));

    for(int adresse = 0; adresse < 0x50; adresse++)
    {
        speicherAnsicht->setItem(adresse, 0, new QTableWidgetItem(QString::number(adresse)));
        speicherAnsicht->setItem(adresse, 1, new QTableWidgetItem(QString::number(steuerwerk->getRam()->lesen(adresse, 0))));
        speicherAnsicht->setItem(adresse, 2, new QTableWidgetItem(QString::number(steuerwerk->getRam()->lesen(adresse, 1))));
    }
}

void MainWindow::erneuernUI()
{
    neuZeichnenProgrammzaehler();
    neuZeichnenStack();
    neuZeichnenSpeicherAnsicht();
}
