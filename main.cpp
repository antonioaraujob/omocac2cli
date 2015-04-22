#include <QCoreApplication>

#include <QSettings>
#include <QTime>

#include "mainwindow.h"
#include "individual.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //qDebug("hola mundo");

    MainWindow mw;

    //qsrand((uint)QTime::currentTime().msec());
    //Individual * i = new Individual(1);
    //i->printIndividual();

    if (mw.getDoComparationOfAlgorithms())
    {
        // ejecucion de la comparacion de los algoritmo original y modificado
        // el numero de ejecuciones de cada algoritmo se toma del archivo de
        // configuracion
        mw.compareAlgorithmRepeated();
    }
    else if (mw.getDoOriginalAlgorithm())
    {
        // se ejecuta el algoritmo cultural una vez de acuerdo a los parametros
        // establecidos en el archivo de configuracion
        // mw.executeAlgorithm();
        mw.executeAlgorithmRepeated();
    }
    else // ejecutarMutacionDirigida
    {
        mw.executeModificatedAlgorithm();
    }

    qDebug("return 0");
    return 0;

    //return a.exec();
}
