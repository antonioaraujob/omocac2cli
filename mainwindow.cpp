#include "mainwindow.h"

#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QSet>
#include <QDir>

#include "individual.h"
#include "simulation.h"


/**
 * @brief Funcion de comparacion de individuos con respecto al valor de desempeno de latencia
 * @param p1 Individuo 1 a comparar
 * @param p2 Individuo 2 a comparar
 * @return Verdadero si p1 es menor que p2 con respecto a la funcion objetivo de latencia
 */
inline static bool xLessThanLatency(Individual *p1, Individual *p2)
{
    return p1->getPerformanceLatency() < p2->getPerformanceLatency();
}

/**
 * @brief Define e inicializa el miembro estatico individualSize
 */
int MainWindow::individualSize = 0;


MainWindow::MainWindow()
{
    // lectura de los parametros del algoritmo cultural a partir del archivo ini
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("CONF");

    population = settings.value("poblacion").toInt();
    qDebug(qPrintable(QString::number(population)));

    generationsNumber = settings.value("numeroDeGeneraciones").toInt();
    qDebug(qPrintable(QString::number(generationsNumber)));

    standarDeviation = settings.value("desviacionEstandar").toInt();
    qDebug(qPrintable(QString::number(standarDeviation)));

    externalFileSize = settings.value("tamanoArchivoExterno").toInt();
    qDebug(qPrintable(QString::number(externalFileSize)));

    gridSubintervalnumber = settings.value("numeroDeSubintervalosDeRejilla").toInt();
    qDebug(qPrintable(QString::number(gridSubintervalnumber)));

    updateFrequency = settings.value("frecuenciaDeActualizacion").toInt();
    qDebug(qPrintable(QString::number(updateFrequency)));

    matchesPerIndividual = settings.value("numeroDeEncuentrosPorIndividuo").toInt();
    qDebug(qPrintable(QString::number(matchesPerIndividual)));

    mutationProbability = settings.value("probabilidadDeMutacionDirigida").toDouble();
    qDebug(qPrintable(QString::number(mutationProbability)));

    doDirectedMutation = settings.value("ejecutarMutacionDirigida").toBool();
    if (doDirectedMutation)
        qDebug("doDirectMutation");
    else
        qDebug("NO doDirectMutation");

    simulationRepetitions = settings.value("numeroDeRepeticionesDeSimulacion").toInt();

    doComparationOfAlgorithms = settings.value("ejecutarComparacionDeAlgoritmos").toBool();

    individualSize = settings.value("tamanoDeIndividuo").toInt();
    qDebug("individualSize %s", qPrintable(QString::number(individualSize)));

    qDebug("salida");


}


MainWindow::~MainWindow()
{

}



void MainWindow::executeAlgorithm()
{
    /*
    if (!validateFields())
    {
        return;
    }
    */


    // creacion del objeto simulacion
    simulation = new Simulation(population,
                                externalFileSize,
                                generationsNumber,
                                gridSubintervalnumber,
                                updateFrequency,
                                matchesPerIndividual,
                                standarDeviation,
                                25,
                                doDirectedMutation,
                                mutationProbability);
    /*
                ui->lineEditPopulationSize->text().toInt(),
                                ui->lineEditExternalFileSize->text().toInt(),
                                ui->lineEditGenerationNumber->text().toInt(),
                                ui->lineEditGridSubintervals->text().toInt(),
                                ui->lineEditGnormative->text().toInt(),
                                ui->lineEditPopulationSize->text().toInt()/2,
                                ui->lineEditMutationStd->text().toInt(),
                                25,
                                ui->checkBoxDirectedMutation->isChecked(),
                                ui->lineEditDirectedMutation->text().toDouble());
                                */

    qsrand((uint)QTime::currentTime().msec());


    /*
    QFile file("/tmp/algorithmResult.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        //QMessageBox msg;
        //msg.setText("No se pudo abrir el archivo /tmp/algorithmResult.txt para escribir \nresultados de la ejecucion del algoritmo.");
        qDebug("No se pudo abrir el archivo /tmp/algorithmResult.txt para escribir \nresultados de la ejecucion del algoritmo.");
        //msg.exec();
        return;
    }
    QTextStream out(&file);
    out << "Inicia ejecucion del algoritmo cultural." <<"\n";

    out << endl;
    out << "Parametros de la ejecucion" << endl;
    out << "Tamano de la poblacion: " << QString::number(population) << endl;
    out << "Tamano del archivo externo: " << QString::number(externalFileSize) << endl;
    out << "Maximo numero de generaciones: " << QString::number(generationsNumber) << endl;
    out << "Numero de subintervalos para la rejilla: " << QString::number(gridSubintervalnumber) << endl;
    out << "Numero de generaciones para actualizar parte normativa: " << QString::number(updateFrequency) << endl;
    out << "Numero de encuentros por individuo en un torneo: " << QString::number(population/2) << endl;
    out << "Desviacion estandar de la mutacion gausiana: " << QString::number(standarDeviation) << endl;
    out << "Numero de APs desplegados: " << 25 << endl;
    */

    // inicializar poblacion de tamano P
    simulation->initializePopulation();

    // evaluar poblacion inicial
    simulation->evaluateIndividuals();

    // inicializar parte fenotipica normativa del espacio de creencias
    simulation->initializeNormativePhenotypicPart();
    qDebug("...se acaba de inicializar la parte normativa fenotipica del espacio de creencias");

    // inicializar rejilla del espacio de creencias
    simulation->initializeGrid();
    qDebug("...se acaba de inicializar la grid");


    // lista de individuos no dominados
    QList<Individual *> nonDominatedList;

    // contador de generaciones para la actualizacion de la parte fenotipica normativa
    int countOfGenerations = 1;

    // repetir por el numero maximo de generaciones
    do{
        qDebug("...generacion: %d", simulation->getCurrentGenerationNumber());

        /*
        QFile file("/tmp/algorithmResult.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            //QMessageBox msg;
            //msg.setText("No se pudo abrir el archivo /tmp/algorithmResult.txt para escribir \nresultados de la ejecucion del algoritmo.");
            qDebug("No se pudo abrir el archivo /tmp/algorithmResult.txt para escribir \nresultados de la ejecucion del algoritmo.");
            //msg.exec();
            return;
        }
        QTextStream out(&file);
        out << endl<< "Generacion: "<< simulation->getCurrentGenerationNumber() <<"\n";
        */

        // mutacion de la poblacion
        simulation->mutatePopulation();
        qDebug("...despues de simulation->mutatePopulation()");


        // evaluar hijos
        simulation->evaluateIndividuals();

        // realizar torneos y seleccionar poblacion
        simulation->selectPopulation();
        qDebug("...despues de simulation->selectPopulation()");

        // imprimir poblacion para depuracion
        simulation->printPopulation();

        // obtener los individuos no dominados
        nonDominatedList = simulation->getNonDominatedPopulationApproach1();
        qDebug("...Numero de individuos en la poblacion no dominada: %d", nonDominatedList.count());


        qDebug("-------INDIVIDUOS no dominados antes de insertarlos en el archivo externo-------");
        simulation->printList(nonDominatedList);
        qDebug("--------------------------------------------------------------------------------");
        qDebug("...despues de obtener los individuos no dominados");

        // agregar los individuos no dominados al archivo externo
        simulation->addNonDominatedIndividualsToExternalFile(nonDominatedList);
        //simulation->addNonDominatedIndividualsToExternalFile(simulation->getPopulationList());

        qDebug("Cantidad de INDIVIDUOS no dominados despues de insertarlos en el archivo externo: %d",
               simulation->getExternalFile()->getExternalFileList().count());


        // actualizar el espacio de creencias con los individos aceptados
        if (countOfGenerations == simulation->getgNormative())
        {
            qDebug("MainWindow.cpp: numero de generaciones transcurridas: %d ahora actualizar parte normativa", countOfGenerations);
            simulation->updateNormativePhenotypicPart();
        }


        // actualizar la rejilla con todos los individuos no dominados recien agregados al archivo externo
        // durante la generación actual
        simulation->updateGrid(simulation->getExternalFile()->getCurrentGenerationIndividualList());
        simulation->getExternalFile()->resetCurrentGenerationIndividualList();
        qDebug("...despues de actualizar la rejilla");

        qDebug("generacion actual: %d", simulation->getCurrentGenerationNumber());

        qDebug("****************************************************************************");
        qDebug("Individuos del archivo externo");
        simulation->printList(simulation->getExternalFile()->getExternalFileList());
        qDebug("****************************************************************************");

        //QMessageBox msg;
        //QString string = "Ver el Archivo externo al final de la generacion ";
        //string.append(QString::number(simulation->getCurrentGenerationNumber()));
        //msg.setText(string);
        //msg.exec();


        simulation->incrementGeneration();

        // incrementar contador de generaciones para actualizar parte fenotipica normativa
        countOfGenerations++;

    }while(!simulation->stopEvolution()); // fin de la repeticion

    qDebug("*********");
    qDebug("TERMINO EL ALGORITMO CULTURAL!");


    // poblar la lista de individuos no dominados del archivo externo
    //populateListView();


    //if (ui->checkBoxDirectedMutation->isChecked())
    if (doDirectedMutation)
    {
        modificatedAlgorithmSolutions = simulation->getExternalFile()->getExternalFileList();
    }
    else
    {
        genericAlgorithmSolutions = simulation->getExternalFile()->getExternalFileList();
    }


    // generar el grafico
    //setupCustomPlot(ui->customPlot);

    // generar el grafico
    //plotSolutions();

    //storeExecutionSolution();

    // *****************************************************************************
    if (!doComparationOfAlgorithms)
    {
        // escribir los resultados de la simulacion
        QList<Individual *> finalResultsList;
        QString outputFileName = "";
        // cadena con el nombre del subdirectorio que almacenara los resultados
        QString resultsDirectory = createResultsDirectory();

        if (doDirectedMutation)
        {
            finalResultsList = modificatedAlgorithmSolutions;
            outputFileName = "individuosFrenteParetoModificado";
        }
        else
        {
            finalResultsList = genericAlgorithmSolutions;
            outputFileName = "individuosFrenteParetoOriginal";
        }

        // ordenar la lista en orden ascendente de acuerdo a la latencia (F2)
        qSort(finalResultsList.begin(), finalResultsList.end(), xLessThanLatency);

        // escribir en un archivo los individuos del frente de pareto encontrado en un archivo
        reportIndividualAsFile(finalResultsList, resultsDirectory, outputFileName);
    }
    // *****************************************************************************


    qDebug("antes de salir executeAlgorithm");
}


void MainWindow::compareAlgorithmRepeated()
{

    qDebug("MainWindow::compareAlgorithmRepeated()");

    QTime timer;
    QList<double> executionTimeList;



    // ejecuciones del algoritmo original
    for (int i=0; i<simulationRepetitions; i++)
    {
        timer.start();
        executeAlgorithm();
        executionTimeList.append(timer.elapsed());
        QList<Individual*> list(genericAlgorithmSolutions);
        repeatedOriginalSolutionList.append(list);
    }
    // calcular el tiempo promedio de ejecucion del algoritmo original
    double meanExecutionTimeOriginal = getMeanExecutionTime(executionTimeList);
    double stdExecutionTimeOriginal = getStdDeviationExecutionTime(executionTimeList, meanExecutionTimeOriginal);
    executionTimeList.clear();

    // ejecuciones del algoritmo modificado
    //ui->checkBoxDirectedMutation->setChecked(true);
    doDirectedMutation = true;

    for (int i=0; i<simulationRepetitions; i++)
    {
        timer.start();
        executeAlgorithm();
        executionTimeList.append(timer.elapsed());
        QList<Individual*> list(modificatedAlgorithmSolutions);
        repeatedModificatedSolutionList.append(list);
    }

    // calcular el tiempo promedio de ejecucion del algoritmo modificado
    double meanExecutionTimeModificated = getMeanExecutionTime(executionTimeList);
    double stdExecutionTimeModificated = getStdDeviationExecutionTime(executionTimeList, meanExecutionTimeModificated);

    qDebug("------");
    qDebug("Promedio de tiempo de ejecución original:");
    qDebug(qPrintable(QString::number(meanExecutionTimeOriginal)+" ms, "+QString::number(stdExecutionTimeOriginal)));

    qDebug("Promedio de tiempo de ejecución modificado:");
    qDebug(qPrintable(QString::number(meanExecutionTimeModificated)+" ms, "+QString::number(stdExecutionTimeModificated)));
    qDebug("------");

    qDebug("Promedio de numero de individuos no dominados algoritmo original:");
    int totalIndividuals = 0;
    for (int j=0; j<repeatedOriginalSolutionList.count(); j++)
    {
        totalIndividuals = totalIndividuals + repeatedOriginalSolutionList.at(j).count();
    }
    double meanNonDominatedIndividuals1 = totalIndividuals/repeatedOriginalSolutionList.count();
    qDebug(qPrintable(QString::number(meanNonDominatedIndividuals1)+" individuos"));

    qDebug("Promedio de numero de individuos no dominados algoritmo modificado:");
    int totalIndividuals2 = 0;
    for (int j=0; j<repeatedModificatedSolutionList.count(); j++)
    {
        totalIndividuals2 = totalIndividuals2 + repeatedModificatedSolutionList.at(j).count();
    }
    double meanNonDominatedIndividuals2 = totalIndividuals2/repeatedModificatedSolutionList.count();
    qDebug(qPrintable(QString::number(meanNonDominatedIndividuals2)+" individuos"));
    qDebug("------");



    double meanF1Original = getMeanOfObjectiveFunction(1, repeatedOriginalSolutionList, 1);
    qDebug("Promedio de Fo1 original: %s", qPrintable(QString::number(meanF1Original)));
    qDebug("STD de Fo1 original: %s", qPrintable(QString::number(getStandardDeviation(meanF1Original, 1, repeatedOriginalSolutionList, 1))));
    double meanF2Original = getMeanOfObjectiveFunction(2, repeatedOriginalSolutionList, 1);
    qDebug("Promedio de Fo2 original: %s", qPrintable(QString::number(meanF2Original)));
    qDebug("STD de Fo2 original: %s", qPrintable(QString::number(getStandardDeviation(meanF2Original, 2, repeatedOriginalSolutionList, 1))));


    double meanF1Modificated = getMeanOfObjectiveFunction(1, repeatedModificatedSolutionList, 2);
    qDebug("Promedio de Fo1 modificada: %s", qPrintable(QString::number(meanF1Modificated)));
    qDebug("STD de Fo1 modificada: %s", qPrintable(QString::number(getStandardDeviation(meanF1Modificated, 1, repeatedModificatedSolutionList, 2))));
    double meanF2Modificated = getMeanOfObjectiveFunction(2, repeatedModificatedSolutionList, 2);
    qDebug("Promedio de Fo2 modificada: %s", qPrintable(QString::number(meanF2Modificated)));
    qDebug("STD de Fo2 modificada: %s", qPrintable(QString::number(getStandardDeviation(meanF2Modificated, 2, repeatedModificatedSolutionList, 2))));

    // cadena con el nombre del subdirectorio que almacenara los resultados
    QString resultsDirectory = createResultsDirectory();

    QFile file(resultsDirectory+"/resultadosFinalesComparacion.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text /*| QIODevice::Append*/))
    {
        //QMessageBox msg;
        //msg.setText("No se pudo abrir el archivo /tmp/resultadosFinalesComparacion.txt para escribir \nresultados de la comparacion de algoritmos.");
        //msg.exec();
        qDebug("No se pudo abrir el archivo /tmp/resultadosFinalesComparacion.txt para escribir \nresultados de la comparacion de algoritmos");
        return;
    }
    QTextStream out(&file);

    out << "Resultados de comparacion de algoritmos" << endl;
    out << "Promedio de tiempo de ejecución original: " << QString::number(meanExecutionTimeOriginal) << " ms, std: " <<
           QString::number(stdExecutionTimeOriginal) << endl;
    out << "Promedio de tiempo de ejecución modificado: " << QString::number(meanExecutionTimeModificated) << " ms, std: " <<
           QString::number(stdExecutionTimeModificated) << endl;
    out << endl;
    out << "Promedio de numero de individuos no dominados algoritmo original: " << QString::number(meanNonDominatedIndividuals1) << " individuos" << endl;
    out << "Promedio de numero de individuos no dominados algoritmo modificado: " << QString::number(meanNonDominatedIndividuals2) << " individuos" << endl;
    out << endl;
    out << "Promedio de Fo1 original: " << QString::number(meanF1Original) << endl;
    out << "STD de Fo1 original: " << QString::number(getStandardDeviation(meanF1Original, 1, repeatedOriginalSolutionList, 1)) << endl;
    out << "Promedio de Fo2 original: " << QString::number(meanF2Original) << endl;
    out << "STD de Fo2 original: " << QString::number(getStandardDeviation(meanF2Original, 2, repeatedOriginalSolutionList, 1)) << endl;
    out << endl;
    out << "Promedio de Fo1 modificada: " << QString::number(meanF1Modificated) << endl;
    out << "STD de Fo1 modificada: " << QString::number(getStandardDeviation(meanF2Original, 2, repeatedOriginalSolutionList, 1)) << endl;
    out << "Promedio de Fo2 modificada: " << QString::number(meanF2Modificated) << endl;
    out << "STD de Fo2 modificada: " << QString::number(getStandardDeviation(meanF2Modificated, 2, repeatedModificatedSolutionList, 2)) << endl;



    //---------------------------------------------------------------------------
    // prueba de obtener los no dominados de todas las ejecuciones del algoritmo
    QList<Individual*> myList = getNonDominatedIndivualsFromRepetitions(true);
    qDebug("--------");
    qDebug("individuos no dominados del algoritmo original: %s", qPrintable(QString::number(myList.count())));
/*
    QVector<double> discoveryParetoOriginal(myList.count()), latencyParetoOriginal(myList.count());
    Individual * paretoIndividual;
    int vectorPosition = 0;

    for (int i=0; i<myList.count();i++)
    {
        paretoIndividual = myList.at(i);
        discoveryParetoOriginal[vectorPosition] = paretoIndividual->getPerformanceDiscovery();
        latencyParetoOriginal[vectorPosition] = paretoIndividual->getPerformanceLatency();
        vectorPosition++;
    }
*/

    // ordenar la lista en orden ascendente de acuerdo a la latencia (F2)
    qSort(myList.begin(), myList.end(), xLessThanLatency);


    // escribir en un archivo los individuos del frente de pareto encontrado en un archivo
    reportIndividualAsFile(myList, resultsDirectory, "individuosFrenteParetoOriginal");


    // colocar las cadenas en la pestana de cadenas de la interfaz grafica
    //populateAListView(myList, ui->listViewPFOriginal);



    myList.clear();

    myList = getNonDominatedIndivualsFromRepetitions(false);
    qDebug("--------");
    qDebug("individuos no dominados del algoritmo modificado: %s", qPrintable(QString::number(myList.count())));

    /*
    QVector<double> discoveryParetoModificated(myList.count()), latencyParetoModificated(myList.count());
    vectorPosition = 0;

    for (int i=0; i<myList.count();i++)
    {
        paretoIndividual = myList.at(i);
        discoveryParetoModificated[vectorPosition] = paretoIndividual->getPerformanceDiscovery();
        latencyParetoModificated[vectorPosition] = paretoIndividual->getPerformanceLatency();
        vectorPosition++;
    }
*/

    // ordenar la lista en orden ascendente de acuerdo a la latencia (F2)
    qSort(myList.begin(), myList.end(), xLessThanLatency);

    // escribir en un archivo los individuos del frente de pareto encontrado en un archivo
    reportIndividualAsFile(myList, resultsDirectory, "individuosFrenteParetoModificado");

    // colocar las cadenas en la pestana de cadenas de la interfaz grafica
    //populateAListView(myList, ui->listViewPFModificated);

    qDebug("--------");
    //---------------------------------------------------------------------------
}


void MainWindow::reportIndividualAsFile(QList<Individual*> list, QString fileName)
{
    QFile file("/tmp/"+fileName+".txt");
    if (file.exists())
    {
        file.remove();
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QString msg = "No se pudo crear el archivo /tmp/"+fileName+".txt";
        qDebug(qPrintable(msg));
        return;
    }
    QTextStream out(&file);
    out << "/tmp/"+fileName+".txt - Individuos encontrados luego de ejecutar el algoritmo cultural: " << "\n";

    for(int i=0; i<list.count(); i++)
    {
        out << list.at(i)->getIndividualAsQString() << "\n";
    }
}

void MainWindow::reportIndividualAsFile(QList<Individual*> list, QString resultsSubdirectory, QString fileName)
{
    QFile file(resultsSubdirectory+"/"+fileName+".txt");
    if (file.exists())
    {
        file.remove();
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QString msg = "No se pudo crear el archivo /tmp/"+fileName+".txt";
        qDebug(qPrintable(msg));
        return;
    }
    QTextStream out(&file);
    //out << resultsSubdirectory +"/"+fileName+".txt - Individuos encontrados luego de ejecutar el algoritmo cultural: " << "\n";

    for(int i=0; i<list.count(); i++)
    {
        out << list.at(i)->getIndividualAsQString() << "\n";
    }
}


double MainWindow::getMeanExecutionTime(QList<double> l)
{

    double sumOfExecutionTime= 0;

    for (int j=0; j<l.count(); j++)
    {
        sumOfExecutionTime = sumOfExecutionTime + l.at(j);

    }
    return sumOfExecutionTime/l.count();

}


double MainWindow::getStdDeviationExecutionTime(QList<double> l, double mean)
{
    double numerator = 0;
    double denominator = l.count();

    for (int j=0; j<l.count(); j++)
    {
        numerator = numerator + pow((l.at(j)-mean),2);

    }
    return sqrt(numerator/denominator);
}


int MainWindow::getCountOfNonDominatedInRepetitions()
{
    // identificar el número total de individuos de todas las ejecuciones
    int counter = 0;
    for (int x=0; x<repeatedSolutionList.count(); x++)
    {
        counter = counter + repeatedSolutionList.at(x).count();
    }
    return counter;
}

double MainWindow::getMeanOfObjectiveFunction(int fo, QList<QList<Individual *> >list, int type)
{
    int counter = 0; //getCountOfNonDominatedInRepetitions();

    if (type==0)
    {
        counter = getCountOfNonDominatedInRepetitions();
    }
    else if (type==1)
    {
        counter = getCountOfNonDominatedInOriginalRepetitions();
    }else if (type==2)
    {
        counter = getCountOfNonDominatedInModificatedRepetitions();
    }

    double sumOfDiscovery = 0;
    double sumOfLatency = 0;

    QList<Individual *> listOfNonDominated;
    Individual * individual;

    //for (int j=0; j<repeatedSolutionList.count(); j++)
    for (int j=0; j<list.count(); j++)
    {
        //listOfNonDominated = repeatedSolutionList.at(j);
        listOfNonDominated = list.at(j);
        for (int k=0; k<listOfNonDominated.count(); k++)
        {
            individual = listOfNonDominated.at(k);
            sumOfDiscovery = sumOfDiscovery + individual->getPerformanceDiscovery();
            sumOfLatency = sumOfLatency + individual->getPerformanceLatency();

        }
    }

    if (fo==1)
    {
        return sumOfDiscovery/counter;
    }
    else if (fo==2)
    {
        return sumOfLatency/counter;
    }
    else
    {
        return 0;
    }

    //qDebug("Promedio de Fo1: %s", qPrintable(QString::number(sumOfDiscovery/counter)));
    //qDebug("Promedio de Fo2: %s", qPrintable(QString::number(sumOfLatency/counter)));
}


double MainWindow::getStandardDeviation(double mean, int fo, QList<QList<Individual *> >list, int type)
{
    double numerator = 0;
    double denominator = 0; // getCountOfNonDominatedInRepetitions();

    if (type==0)
    {
        denominator = getCountOfNonDominatedInRepetitions();
    }
    else if (type==1)
    {
        denominator = getCountOfNonDominatedInOriginalRepetitions();
    }else if (type==2)
    {
        denominator = getCountOfNonDominatedInModificatedRepetitions();
    }


    QList<Individual *> listOfNonDominated;
    Individual * individual;

    //for (int j=0; j<repeatedSolutionList.count(); j++)
    for (int j=0; j<list.count(); j++)
    {
        //listOfNonDominated = repeatedSolutionList.at(j);
        listOfNonDominated = list.at(j);
        for (int k=0; k<listOfNonDominated.count(); k++)
        {
            individual = listOfNonDominated.at(k);

            if (fo == 1)
            {
                numerator = numerator + pow((individual->getPerformanceDiscovery()-mean),2);

            }
            else if (fo == 2)
            {
                numerator = numerator + pow((individual->getPerformanceLatency()-mean),2);

            }
            else
            {
                return 0;
            }
        }
    }
    return sqrt(numerator/denominator);

}


QList<Individual*> MainWindow::getNonDominatedIndivualsFromRepetitions(bool original)
{
    QList<Individual*> auxiliaryList;
    if (original)
    {
        auxiliaryList = getNonDominatedIndividualsFromList(repeatedOriginalSolutionList);
    }
    else
    {
        auxiliaryList = getNonDominatedIndividualsFromList(repeatedModificatedSolutionList);
    }

    QList<Individual*> nonDominatedListToReturn;

    ExternalFile auxiliaryExternalFile;
    int p = auxiliaryList.count();

    Individual * individualI;
    Individual * individualJ;

    for (int i=0; i<p; i++)
    {
        bool dominated = false;
        individualI = auxiliaryList.at(i);

        for (int j=0; ((j<p) && (!dominated)); j++)
        {

            if (i==j)
            {
                continue;
            }
            individualJ = auxiliaryList.at(j);
            if (auxiliaryExternalFile.individualDominate(individualJ, individualI))
            {
                dominated = true;
            }
        }
        if (!dominated)
        {
            nonDominatedListToReturn.append(individualI);
        }
    }
    return nonDominatedListToReturn;


}


int MainWindow::getCountOfNonDominatedInOriginalRepetitions()
{
    // identificar el número total de individuos de todas las ejecuciones
    int counter = 0;
    for (int x=0; x<repeatedOriginalSolutionList.count(); x++)
    {
        counter = counter + repeatedOriginalSolutionList.at(x).count();
    }
    return counter;
}

int MainWindow::getCountOfNonDominatedInModificatedRepetitions()
{
    // identificar el número total de individuos de todas las ejecuciones
    int counter = 0;
    for (int x=0; x<repeatedModificatedSolutionList.count(); x++)
    {
        counter = counter + repeatedModificatedSolutionList.at(x).count();
    }
    return counter;
}

QList<Individual*> MainWindow::getNonDominatedIndividualsFromList(QList<QList<Individual *> > list)
{
    QList<Individual *> individualList;

    QList<Individual*> auxiliaryList;
    Individual * individual;
    for (int j=0; j<list.count(); j++)
    {
        auxiliaryList = list.at(j);
        for (int k=0; k<auxiliaryList.count(); k++)
        {
            individual = auxiliaryList.at(k);
            individualList.append(individual);
        }
    }
    return individualList;
}



QString MainWindow::createResultsDirectory()
{

    QString resultsDir = QDir::currentPath() + "/resultados";
    qDebug(qPrintable(resultsDir));

    QString outputDir = resultsDir + "/" + QDateTime::currentDateTime().toString("dd.MM.yyyy_hh.mm.ss");
    qDebug(qPrintable(outputDir));


    QDir dir(resultsDir);
    if (!dir.exists())
    {
        qDebug("no existe");
        if (dir.mkdir(resultsDir))
            qDebug("se acaba de crear");
        else
            qDebug("no se pudo crear");
    }
    else
    {
        qDebug("existe");
    }

    // crear el directorio con la fecha
    QDir tmpDir(outputDir);
    if (!tmpDir.exists())
    {
        qDebug("no existe el directorio de ejecucion");
        if (tmpDir.mkdir(outputDir))
            qDebug("creado el directorio de la ejecucion");
        else
            qDebug("fallo la creacion del directorio de ejecucion");

    }
    return outputDir;

}


bool MainWindow::getDoComparationOfAlgorithms()
{
    return doComparationOfAlgorithms;
}


int MainWindow::getIndividualSize()
{
    return individualSize;
}
