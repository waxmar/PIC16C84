#include "parser.h"
#include <iostream>
#include <QString>
#include <fstream>
#include <qlistwidget.h>
#include <QListWidgetItem>

#include "steuerwerk.h"
#include "programmspeicher.h"

Parser::Parser()
{
}

//Auslesen des Befehlscodes (Zeichen 5-8) sowie der Textzeile (Zeichen 21-24)
void Parser::parsen(QString dateipfad, Steuerwerk* steuerwerk, QListWidget* befehlsliste)
{
    if(steuerwerk == NULL)
        return;

    string zeile;
    ifstream lesestream(dateipfad.toStdString().c_str());

    if(!lesestream)
        return;

    Programmspeicher* programmspeicher = steuerwerk->getProgrammspeicher();

    while(!lesestream.eof())
    {
        getline(lesestream, zeile, '\n');

        QListWidgetItem* widgetitem  = new QListWidgetItem(QString::fromStdString(zeile));


        befehlsliste->addItem(widgetitem);


        if(zeile[0] != ' ' && zeile[0] != 0)	// Codezeile erkennen!
        {
            int textZeile = 0;
            int befehl = 0;

            bool ok;

            befehl = QString::fromStdString(zeile.substr(5,4)).toInt(&ok,16); // 16 gibt die Basis der gelesenen Dateien an, der String wird in Dezimal zur weiteren verarbeitung gespeichert
            textZeile = QString::fromStdString(zeile.substr(21, 4)).toInt(&ok,10);

            programmspeicher->schreiben(befehl, textZeile-1);
        }

    }

}
