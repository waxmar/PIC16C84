#include "runthread.h"

#include "steuerwerk.h"
#include "mainwindow.h"

RunThread::RunThread(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
}

void RunThread::run()
{
    while(steuerwerk->gui->threadIsAlive)
    {
        steuerwerk->schrittSteuern();

        QThread::msleep(500);
    }
}
