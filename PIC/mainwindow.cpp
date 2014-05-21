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

void MainWindow::erneuernUI()
{
    neuZeichnenProgrammzaehler();
    neuZeichnenStack();
}
