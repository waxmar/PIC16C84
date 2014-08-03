#include "runthread.h"

#include "steuerwerk.h"
#include "mainwindow.h"

RunThread::RunThread(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
}

//Durchlauf eines Programmes
void RunThread::run()
{
    while(steuerwerk->gui->threadIsAlive)
    {
        steuerwerk->schrittSteuern();

        QThread::msleep(200); //Pause von 0,2 Sekunden zwecks Sichtbarkeit
    }
}
