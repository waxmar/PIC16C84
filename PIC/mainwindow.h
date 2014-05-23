#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QList>

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
    QPushButton* startButton;
    QPushButton* schrittButton;
    QTableWidget* speicherAnsicht;

    void neuZeichnenProgrammzaehler();
    void neuZeichnenStack();
    void neuZeichnenSpeicherAnsicht();

    void speicherAnsichtInitialisieren();

private slots:
    void oeffneDateiBrowserDialog(void);
    void ladeLstDatei(void);
    void schrittAusfuehren(void);
};

#endif // MAINWINDOW_H
