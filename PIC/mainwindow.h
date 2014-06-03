#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QList>
#include <QModelIndex>

class Steuerwerk;
class QLineEdit;
class QPushButton;
class QListWidget;
class QLabel;
class QTableWidget;

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void erneuernUI();

private:
    Ui::MainWindow *ui;
    Steuerwerk* steuerwerk;

    QLineEdit* dateinameLineEdit;
    QPushButton* suchenButton;
    QPushButton* ladenButton;
    QListWidget* befehlslisteWidget;
    QListWidget* stackWidget;
    QLabel* programmzaehlerLabel;
    QLabel* wregisterLabel;
    QLabel* zLabel;
    QLabel* cLabel;
    QLabel* dcLabel;
    QLabel* statusLabel;
    QLabel* fsrLabel;
    QLabel* pclathLabel;
    QPushButton* startButton;
    QPushButton* schrittButton;
    QPushButton* resetButton;
    QTableWidget* speicherAnsicht;
    QTableWidget* registerA;
    QTableWidget* registerB;
    QPushButton* hilfeButton;

    void neuZeichnenProgrammzaehler();
    void neuZeichnenW();
    void neuZeichnenZ();
    void neuZeichnenC();
    void neuZeichnenDC();
    void neuZeichnenStatus();
    void neuZeichnenFSR();
    void neuZeichnenPCLATH();
    void neuZeichnenStack();
    void neuZeichnenSpeicherAnsicht();

    void fokusAlteProgrammzeileEntfernen();
    void fokusAufAktuelleProgrammzeile();

    void speicherAnsichtInitialisieren();
    void registerAnsichtInitialisieren();

private slots:
    void oeffneDateiBrowserDialog(void);
    void ladeLstDatei(void);
    void schrittAusfuehren(void);
    void hilfeOeffnen(void);
    void resetUI(void);
    void programmAusfuehren(void);
    void setzeBreakpoint(QModelIndex);
    void registerAaktualisieren(int reihe, int spalte);
    void registerBaktualisieren(int reihe, int spalte);
};

#endif // MAINWINDOW_H
