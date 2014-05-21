#ifndef PARSER_H
#define PARSER_H

#include <string>
class Steuerwerk;
class QString;
class QListWidget;
using namespace std;

class Parser
{
public:
    Parser();

    static void parsen(QString speicherOrt, Steuerwerk* steuerwerk, QListWidget* befehlsliste);
};

#endif // PARSER_H
