#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <QThread>
#include <QObject>

class Steuerwerk;

class RunThread : public QObject
{
    Q_OBJECT
public:
    RunThread(Steuerwerk* steuerwerk);
public slots:
    void run(void);
private:
    Steuerwerk* steuerwerk;
signals:


};

#endif // RUNTHREAD_H
