#include <QCoreApplication>

#include <QSettings>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("hola mundo");


    MainWindow mw;

    //mw.executeAlgorithm();
    mw.compareAlgorithmRepeated();



    qDebug("return 0");
    return 0;

    //return a.exec();
}
