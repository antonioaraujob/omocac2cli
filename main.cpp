#include <QCoreApplication>

#include <QSettings>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("hola mundo");


    MainWindow mw;

    if (mw.getDoComparationOfAlgorithms())
    {
        // ejecucion de la comparacion de los algoritmo original y modificado
        // el numero de ejecuciones de cada algoritmo se toma del archivo de
        // configuracion
        mw.compareAlgorithmRepeated();
    }
    else
    {
        // se ejecuta el algoritmo cultural una vez de acuerdo a los parametros
        // establecidos en el archivo de configuracion
        mw.executeAlgorithm();
    }

    qDebug("return 0");
    return 0;

    //return a.exec();
}
