#include "salarios.h"
#include "obrero.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salarios w;
    w.show();

    Obrero *objObrero1 = new Obrero ("Juan",47,TipoJornada::Vespertina);





    return a.exec();
}
