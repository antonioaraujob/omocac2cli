#include "individual.h"

//#include "simulation.h"
#include "mainwindow.h"

#include <QTime>
#include <QStringList>
#include <QString>

#include "scan.h"


Individual::Individual(int numberOfApsDeployed)
{
    //qsrand((uint)QTime::currentTime().msec());

    // asignar el valor unico del identificador del individuo
    individualId = Simulation::getNewindividualId();

    // asignar el tamano del individuo
    individualSize = MainWindow::getIndividualSize();
    //qDebug("Individual.cpp: individualSize = %s", qPrintable(QString::number(individualSize)));

    emulateScanning = MainWindow::getEmulateScanning();

    // asignar un valor de nscan entre 1 y 8
    //nscansForMutation = qrand() % ((8 + 1) - 1) + 1;
    nscansForMutation = 1;

    // se deben crear los 33 parametros
    // C1,Min1,Max1,AP1,C2,Min2,Max2,AP2,...,C11,Min11,Max11,AP11


    // base de datos sqlite
    //QString database("/home/antonio/Copy/2014/pgcomp/ia/gridCells/gridCells/test_18.1.db");
    //QString database("/home/antonio/desarrollo/iaa/git/omocac/test_18.1.db");
    //QString database("test_18.1.db");
    QString database("database.db");

    // tipo de experimento para extraer las muestras: full -> full scanning
    QString experiment("full");

    //Scan scan(database.toStdString(),experiment.toStdString());
    ScanningCampaing scan(database.toStdString(),experiment.toStdString());

    scan.init();
    scan.prepareIRD();

    //Scan::ScanResults results = scan.execute(11, 10, 30);
    ScanningCampaing::ScanResults results;

    //std::cout << results.size() << " results: " << std::endl;

    int randomChannel = 0;
    double minChannelTime = 0;
    double maxChannelTime = 0;

    int apsFound = 0;


    // iterar de acuerdo al tamano del individuo
    //for (int i=0; i<11; i++)
    for (int i=0; i<individualSize; i++)
    {
        randomChannel = getRandomChannel();
        parametersList.append(randomChannel);

        minChannelTime = getRandomMinChannelTime();
        maxChannelTime = getRandomMaxChannelTime();
        parametersList.append(minChannelTime);
        parametersList.append(maxChannelTime);

        //parametersList.append(getAPNumberOnChannel(numberOfApsDeployed, randomChannel));

        //qDebug("**channel: %d, min: %f, max: %f",randomChannel, minChannelTime, maxChannelTime);
        //results = scan.execute(randomChannel, minChannelTime, maxChannelTime);

        // nueva funcion para obtener el numero de AP de acuerdo a la campana de medicion
        //results = scan.randomScan(randomChannel, minChannelTime, maxChannelTime);
        //results = MainWindow::getRandomScan(randomChannel, minChannelTime, maxChannelTime);

        //apsFound = MainWindow::getAPs(randomChannel, minChannelTime, maxChannelTime);
        apsFound = scan.getAPs(randomChannel, minChannelTime, maxChannelTime);

        //qDebug("**numero de APs encontrados en el canal %d: %d",randomChannel, results.size());
        //std::cout << " numero de APs encontrados en el canal: " << randomChannel << ": " << results.size() << std::endl;
        //qDebug("**scan.execute(%d, %f, %f)=%d",randomChannel, minChannelTime, maxChannelTime, results.size());

        //parametersList.append(results.size());

        parametersList.append(apsFound);

        wonMatchesCounter = 0;
    }

    // calcular el valor de desempeno para el individuo
    //calculatePerformanceValue();

    // calcular el valor de desempeno para la descubierta
    //setPerformanceDiscovery(getRandomMaxChannelTime());
    calculateDiscoveryValue();

    // calcular el valor de desempeno para la latencia
    //setPerformanceLatency(getRandomMaxChannelTime());
    calculateLatencyValue();
}


Individual::Individual(bool smart)
{
    // asignar el valor unico del identificador del individuo
    individualId = Simulation::getNewindividualId();

    // asignar el tamano del individuo
    individualSize = MainWindow::getIndividualSize();
    //qDebug("Individual.cpp: individualSize = %s", qPrintable(QString::number(individualSize)));

    emulateScanning = MainWindow::getEmulateScanning();

    // asignar un valor de nscan entre 1 y 8
    nscansForMutation = qrand() % ((8 + 1) - 1) + 1;

    // se deben crear los 33 parametros
    // C1,Min1,Max1,AP1,C2,Min2,Max2,AP2,...,C11,Min11,Max11,AP11


    // base de datos sqlite
    QString database("database.db");

    // tipo de experimento para extraer las muestras: full -> full scanning
    QString experiment("full");

    //Scan scan(database.toStdString(),experiment.toStdString());
    ScanningCampaing scan(database.toStdString(),experiment.toStdString());

    scan.init();
    scan.prepareIRD();

    int randomChannel = 0;
    double minChannelTime = 0;
    double maxChannelTime = 0;

    int apsFound = 0;

    if (!smart)
    {
        // iterar de acuerdo al tamano del individuo
        for (int i=0; i<individualSize; i++)
        {
            randomChannel = getRandomChannel();
            parametersList.append(randomChannel);

            minChannelTime = getRandomMinChannelTime();
            maxChannelTime = getRandomMaxChannelTime();
            parametersList.append(minChannelTime);
            parametersList.append(maxChannelTime);

            apsFound = scan.getAPs(randomChannel, minChannelTime, maxChannelTime);
            parametersList.append(apsFound);

            wonMatchesCounter = 0;
        }
    }
    else
    {
        setSmartParameters();
    }


    // calcular el valor de desempeno para la descubierta
    calculateDiscoveryValue();

    // calcular el valor de desempeno para la latencia
    calculateLatencyValue();
}



void Individual::setSmartParameters()
{
    // base de datos sqlite
    QString database("database.db");
    // tipo de experimento para extraer las muestras: full -> full scanning
    QString experiment("full");
    //Scan scan(database.toStdString(),experiment.toStdString());
    ScanningCampaing scan(database.toStdString(),experiment.toStdString());
    scan.init();
    scan.prepareIRD();
    int apsFound = 0;

    // secuencia de ios
    // 1,39.02,0,2,39.02,0,3,39.02,0,4,39.02,0,5,39.02,0,6,39.02,0,7,39.02,0,8,39.02,0,9,39.02,0,10,39.02,0,11,39.02,0

    // secuencia de ios considerando la distribucion de proporcion de AP
    // 1,9,0,2,0,0,3,0,0,4,0,0,5,0,0,6,12,0,7,1,0,8,0,0,9,0,0,10,0,0,11,12,0

    parametersList.append(1);
    parametersList.append(9);
    parametersList.append(0);
    apsFound = scan.getAPs(1, 9, 0);
    parametersList.append(apsFound);
    parametersList.append(2);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(2, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(3);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(3, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(4);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(4, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(5);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(5, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(6);
    parametersList.append(12);
    parametersList.append(0);
    apsFound = scan.getAPs(6, 12, 0);
    parametersList.append(apsFound);
    parametersList.append(7);
    parametersList.append(1);
    parametersList.append(0);
    apsFound = scan.getAPs(7, 1, 0);
    parametersList.append(apsFound);
    parametersList.append(8);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(8, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(9);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(9, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(10);
    parametersList.append(0);
    parametersList.append(0);
    apsFound = scan.getAPs(10, 0, 0);
    parametersList.append(apsFound);
    parametersList.append(11);
    parametersList.append(12);
    parametersList.append(0);
    apsFound = scan.getAPs(11, 12, 0);
    parametersList.append(apsFound);
}

Individual::Individual(bool smart, QString sequence)
{
    // asignar el valor unico del identificador del individuo
    individualId = Simulation::getNewindividualId();

    // asignar el tamano del individuo
    individualSize = MainWindow::getIndividualSize();
    //qDebug("Individual.cpp: individualSize = %s", qPrintable(QString::number(individualSize)));

    emulateScanning = MainWindow::getEmulateScanning();

    // asignar un valor de nscan entre 1 y 8
    nscansForMutation = qrand() % ((8 + 1) - 1) + 1;

    // inicializar el contador de torneos ganados en 0
    wonMatchesCounter = 0;

    // se deben crear los 33 parametros
    // C1,Min1,Max1,AP1,C2,Min2,Max2,AP2,...,C11,Min11,Max11,AP11


    // base de datos sqlite
    QString database("database.db");

    // tipo de experimento para extraer las muestras: full -> full scanning
    QString experiment("full");

    //Scan scan(database.toStdString(),experiment.toStdString());
    ScanningCampaing scan(database.toStdString(),experiment.toStdString());

    scan.init();
    scan.prepareIRD();

    QStringList tmpList;
    tmpList = sequence.split(",");

    int ch = 0;
    int min = 0;
    int max = 0;
    int apsFound = 0;

    for (int i=0; i<individualSize; i++)
    {
        ch = tmpList.at(i*3).toDouble();
        min = tmpList.at(i*3+1).toDouble();
        max = tmpList.at(i*3+2).toDouble();

        parametersList.append(ch);
        parametersList.append(min);
        parametersList.append(max);

        apsFound = scan.getAPs(ch, min, max);

        parametersList.append(apsFound);
    }


    // calcular el valor de desempeno para la descubierta
    calculateDiscoveryValue();

    // calcular el valor de desempeno para la latencia
    calculateLatencyValue();
}

Individual::Individual(Individual &p)
{
    // iterar de acuerdo al tamano del individuo
    //for (int i=0; i<44; i++)
    int numParameters = getNumberOfParameters();
    for (int i=0; i<numParameters; i++)
    {
        parametersList.append(p.getParameter(i));
    }

    individualId = p.getIndividualId();

    individualSize = p.getIndividualSize();

    emulateScanning = p.getEmulateScanning();

    nscansForMutation = p.getNscanForMutation();

    wonMatchesCounter = p.getWonMatchesCounter();

    // calcular el valor de desempeno para el individuo
    //calculatePerformanceValue();

    // calcular el valor de desempeno para la descubierta
    //setPerformanceDiscovery(getRandomMaxChannelTime());
    calculateDiscoveryValue();

    // calcular el valor de desempeno para la latencia
    //setPerformanceLatency(getRandomMaxChannelTime());
    calculateLatencyValue();
}

int Individual::getIndividualId()
{
    return individualId;
}

int Individual::getIndividualSize()
{
    return individualSize;
}


int Individual::getRandomChannel()
{
/*
    // el rango es 1 <= channel <= 11
    int low = 1;
    int high = 11;
    return qrand() % ((high + 1) - low) + low;
*/

    int low = 1;
    int high = 11;
    int value = 0;

    while(true)
    {
        value = qrand() % ((high + 1) - low) + low;
        if (!channelSequenceSet.contains(value))
        {
            channelSequenceSet.insert(value);
            //qDebug("canal seleccionado: %d", value);
            return value;
        }
    }
}


double Individual::getRandomMinChannelTime()
{
    // el rango es 3 <= MinChannelTime <= 12 en ms

    // se esta restringiendo el hecho de que el MinChannelTime sea 3
    int low = 5;
    int high = 15;
    return qrand() % ((high + 1) - low) + low;
}

double Individual::getRandomMaxChannelTime()
{

    // el rango es 10 <= MaxChannelTime <= 150
    int low = 10;
    int high = 90;
    return qrand() % ((high + 1) - low) + low;
}

double Individual::getAPNumberOnChannel(int numberOfApsDeployed, int channel)
{
/*
    // la proporcion de APs que operan en cada canal es tomada del articulo
    //
    if (channel == 1)
    {
        return (numberOfApsDeployed * 18)/100;
    }
    if (channel == 2)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 3)
    {
        return (numberOfApsDeployed * 3)/100;
    }
    if (channel == 4)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 5)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 6)
    {
        return (numberOfApsDeployed * 36)/100;
    }
    if (channel == 7)
    {
        return (numberOfApsDeployed * 2)/100;
    }
    if (channel == 8)
    {
        return (numberOfApsDeployed * 1)/100;
    }
    if (channel == 9)
    {
        return (numberOfApsDeployed * 6)/100;
    }
    if (channel == 10)
    {
        return (numberOfApsDeployed * 6)/100;
    }
    if (channel == 11)
    {
        return (numberOfApsDeployed * 25)/100;
    }
*/
    return 0;
}

void Individual::printIndividual()
{
    //qDebug("El Individual creado es el siguiente:");
    QString individualString("   ");
    /*
    for (int j=0;j<44;j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=43)
            individualString.append("-");
    }
    */

    /*
    for (int j=0;j<getNumberOfParameters();j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=getNumberOfParameters()-1)
            individualString.append("-");
    }


    individualString.append("-");
    individualString.append(QString::number(getPerformanceDiscovery()));
    individualString.append("-");
    individualString.append(QString::number(getPerformanceLatency()));
    qDebug(qPrintable(individualString));
    //qDebug("Fo:%f",getPerformanceValue());
    */

    // *********************************************************************************
    // nuevo formato para imprimir la cadena correspondiente al individuo <c,m,M,A>
    int aux = 1;

    for (int i=0; i<individualSize; i++)
    {
        //qDebug("i: %s", qPrintable(QString::number(i)));
        for (int j=0; j<4; j++)
        {
            //qDebug("j: %s", qPrintable(QString::number(j)));
            if (aux == 1)
            {
                individualString.append("<");
                individualString.append(QString::number(getParameter(i*4)));
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux++;
            }
            else if (aux == 2)
            {
                individualString.append(QString::number(getParameter(i*4+1)));
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux++;
            }
            else if (aux == 3)
            {
                individualString.append(QString::number(getParameter(i*4+2)));
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux++;
            }
            else if (aux == 4)
            {
                individualString.append(QString::number(getParameter(i*4+3)));
                individualString.append(">");
                //individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux = 1;
            }

        }
    }
    //individualString.append("-");
    individualString.append(QString::number(getPerformanceDiscovery()));
    individualString.append("-");
    individualString.append(QString::number(getPerformanceLatency()));

    qDebug(qPrintable(individualString));
    // *********************************************************************************



}

QString Individual::getIndividualAsQString()
{
    //qDebug("El Individual creado es el siguiente:");
    QString individualString("");

    /*
    for (int j=0;j<44;j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=43)
            individualString.append("-");
    }
    */

    /*
    for (int j=0;j<getNumberOfParameters();j++)
    {
        individualString.append(QString::number(parametersList.at(j)));
        if (j!=getNumberOfParameters()-1)
            individualString.append("-");
    }

    individualString.append("-");
    individualString.append(QString::number(getPerformanceDiscovery()));
    individualString.append("-");
    individualString.append(QString::number(getPerformanceLatency()));
    return individualString;
    */


    // *********************************************************************************
    // nuevo formato para imprimir la cadena correspondiente al individuo <c,m,M,A>
    int aux = 1;

    for (int i=0; i<individualSize; i++)
    {
        //qDebug("i: %s", qPrintable(QString::number(i)));
        for (int j=0; j<4; j++)
        {
            //qDebug("j: %s", qPrintable(QString::number(j)));
            if (aux == 1)
            {
                //individualString.append("<");
                individualString.append(QString::number(getParameter(i*4)));
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux++;
            }
            else if (aux == 2)
            {
                individualString.append(QString::number(getParameter(i*4+1)));
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux++;
            }
            else if (aux == 3)
            {
                individualString.append(QString::number(getParameter(i*4+2)));
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux++;
            }
            else if (aux == 4)
            {
                individualString.append(QString::number(getParameter(i*4+3)));
                //individualString.append(">");
                individualString.append(",");
                //qDebug("aux %s: %s", qPrintable(QString::number(aux)), qPrintable(individualString));
                aux = 1;
            }

        }
    }
    //individualString.append("-");
    //individualString.append("<");
    individualString.append(QString::number(getPerformanceDiscovery()));
    individualString.append(",");
    individualString.append(QString::number(getPerformanceLatency()));

    individualString.append(",");
    individualString.append(QString::number(getNscanForMutation()));

    return individualString;
    // *********************************************************************************


}

void Individual::setPerformanceValue(double performance)
{
    performanceValue = performance;
}


void Individual::calculatePerformanceValue()
{
    performanceValue = parametersList.at(2)+parametersList.at(5)+parametersList.at(8)+parametersList.at(11)+parametersList.at(14)+
            parametersList.at(17)+parametersList.at(20)+parametersList.at(23)+parametersList.at(26)+parametersList.at(29)+parametersList.at(32);

    // se deben calcular los valores de las funciones objetivo para el individuo


    // D = Sumatoria i=1,11 Pi*di
    performanceDiscovery = 0;


    performanceLatency = 0;


}

void Individual::calculateDiscoveryValue()
{

    double api = 0;
    double discovery = 0;
    double probOfAtLeastOneAP = 0;
    double factor = 0;
    double maxChannelTime = 0;

    if (getEmulateScanning())
    {
        /*
        // suma de los valores de AP por canal
        for (int i=0; i<individualSize; i++)
        {
            discovery = discovery + parametersList.at((i*4)+3);
        }
        */

        // ********************************************************************************************************
        // codigo para probar funcion objetivo = ((Suma AP_i)/minchannel_i)*0.20 + ((Suma AP_i)/maxchannel_i)*0.80

        for (int i=0; i<individualSize; i++)
        {
            discovery = ( (parametersList.at((i*4)+3))/(parametersList.at((i*4)+1)) )*0.20 + ( (parametersList.at((i*4)+3))/(parametersList.at((i*4)+2)) )*0.80;
        }
        qDebug("discovery");

        // ********************************************************************************************************

    }
    else
    {
        // iterar de acuerdo al tamano del individuo
        //for (int i=0; i<11; i++)
        for (int i=0; i<individualSize; i++)
        {
            api = parametersList.at((i*4)+3);
            maxChannelTime = parametersList.at((i*4)+2);

            probOfAtLeastOneAP = probabilityExistAtLeastOneAp(i+1);

            factor = probOfAtLeastOneAP / (i+1);

            //discovery = discovery + api + probOfAtLeastOneAP;

            // prueba de la funcion objetivo D tal cual como aparece en el articulo
            discovery = discovery + (probabilityOfFindingAllAps(maxChannelTime) * percentageOfAps(i+1));
        }
    }

    performanceDiscovery = discovery;
    qDebug("performanceDiscovery: ");

}

void Individual::calculateLatencyValue()
{
    int channel = 0;
    double minChannelTime = 0;
    double maxChannelTime = 0;
    double latency = 0;


    if (getEmulateScanning())
    {

        for (int i=0; i<individualSize; i++)
        {
            minChannelTime = parametersList.at((i*4)+1);
            if (minChannelTime != 0)
            {
                maxChannelTime = parametersList.at((i*4)+2);
            }
            else
            {
                maxChannelTime = 0;
            }
            latency = latency + minChannelTime + maxChannelTime;
        }

    }
    else
    {
        // iterar de acuerdo al tamano del individuo
        //for (int i=0; i<11; i++)
        for (int i=0; i<individualSize; i++)
        {
            channel = parametersList.at((i*4));
            minChannelTime = parametersList.at((i*4)+1);
            maxChannelTime = parametersList.at((i*4)+2);
            latency = latency + minChannelTime + (probabilityDelayLessThanMinCT(minChannelTime)*probabilityExistAtLeastOneAp(channel)*maxChannelTime);
        }
    }

    performanceLatency = latency;
}


double Individual::getPerformanceValue()
{
    return performanceValue;
}


void Individual::setPerformanceDiscovery(double performance)
{
    performanceDiscovery = performance;
}


double Individual::getPerformanceDiscovery() const
{
    return performanceDiscovery;
}

void Individual::setPerformanceLatency(double performance)
{
    performanceLatency = performance;
}


double Individual::getPerformanceLatency() const
{
    return performanceLatency;
}




void Individual::setParameter(int i, double value)
{
    parametersList.replace(i,value);
}

double Individual::getParameter(int i) const
{
    return parametersList.at(i);
}

int Individual::getNumberOfParameters() const
{
    return parametersList.count();
}

void Individual::setWonMatchesCounter(int value)
{
    wonMatchesCounter = value;
}

int Individual::getWonMatchesCounter()
{
    return wonMatchesCounter;
}

void Individual::incrementWonMatchesCounter()
{
    wonMatchesCounter++;
}

/*
Individual& Individual::operator = (const Individual &ind)
{
    for (int i=0;i<ind.getNumberOfParameters();i++)
    {
        this->setParameter(i,ind.getParameter(i));
    }
    this->setPerformanceDiscovery(ind.getPerformanceDiscovery());
    this->setPerformanceLatency(ind.getPerformanceLatency());

    return *this;
}
*/

double Individual::probabilityExistAtLeastOneAp(int channel)
{
    //qDebug("Individual::probabilityExistAtLeastOneAp");
    double probability = 0;

    if (channel == 1)
        probability = 0.82;
    else if (channel == 2)
        probability = 0.09;
    else if (channel == 3)
        probability = 0.35;
    else if (channel == 4)
        probability = 0.1;
    else if (channel == 5)
        probability = 0.11;
    else if (channel == 6)
        probability = 0.92;
    else if (channel == 7)
        probability = 0.12;
    else if (channel == 8)
        probability = 0.13;
    else if (channel == 9)
        probability = 0.45;
    else if (channel == 10)
        probability = 0.4;
    else if (channel == 11)
        probability = 0.83;
    else
        probability = 0;

    return probability;
}

double Individual::percentageOfAps(int channel)
{
    double percentage = 0;

    if (channel == 1)
        percentage = 18;
    else if (channel == 2)
        percentage = 1;
    else if (channel == 3)
        percentage = 3;
    else if (channel == 4)
        percentage = 1;
    else if (channel == 5)
        percentage = 1;
    else if (channel == 6)
        percentage = 37;
    else if (channel == 7)
        percentage = 2;
    else if (channel == 8)
        percentage = 1;
    else if (channel == 9)
        percentage = 7;
    else if (channel == 10)
        percentage = 6;
    else if (channel == 11)
        percentage = 23;
    else
        percentage = 0;

    return percentage;
}

double Individual::probabilityDelayLessThanMinCT(double delay)
{
    //qDebug("Individual::probabilityDelayLessThanMinCT");

    double probability = 0;

    if (delay == 0)
        probability = 0;
    else if (delay == 1)
        probability = 0.01;
    else if (delay == 2)
        probability = 0.03;
    else if (delay == 3)
        probability = 0.5;
    else if (delay == 4)
        probability = 0.68;
    else if (delay == 5)
        probability = 0.72;
    else if (delay == 6)
        probability = 0.79;
    else if (delay == 7)
        probability = 0.82;
    else if (delay == 8)
        probability = 0.84;
    else if (delay == 9)
        probability = 0.88;
    else if (delay == 10)
        probability = 0.89;
    else if (delay == 11)
        probability = 0.9;
    else if (delay == 12)
        probability = 0.91;
    else if (delay == 13)
        probability = 0.92;
    else if (delay == 14)
        probability = 0.93;
    else if (delay == 15)
        probability = 0.94;
    else if (delay == 16)
        probability = 0.95;
    else if (delay == 17)
        probability = 0.96;
    else if (delay == 18)
        probability = 0.97;
    else if (delay == 19)
        probability = 0.98;
    else if (delay == 20)
        probability = 0.99;
    else if (delay == 21)
        probability = 0.99;
    else if (delay == 22)
        probability = 0.99;
    else if (delay == 23)
        probability = 0.99;
    else if (delay == 24)
        probability = 0.99;
    else if (delay == 25)
        probability = 1;
    else if (delay > 25)
        probability =  1;
    else
        probability = 0;

    return probability;
}


double Individual::probabilityOfFindingAllAps(double delay)
{
    //qDebug("Individual::probabilityOfFindingAllAps");

    double probability = 0;

    if (delay == 0)
        probability = 0;
    else if (delay == 1)
        probability = 0.01;
    else if (delay == 2)
        probability = 0.02;
    else if (delay == 3)
        probability = 0.19;
    else if (delay == 4)
        probability = 0.28;
    else if (delay == 5)
        probability = 0.34;
    else if (delay == 6)
        probability = 0.42;
    else if (delay == 7)
        probability = 0.49;
    else if (delay == 8)
        probability = 0.53;
    else if (delay == 9)
        probability = 0.59;
    else if (delay == 10)
        probability = 0.61;
    else if (delay == 11)
        probability = 0.65;
    else if (delay == 12)
        probability = 0.7;
    else if (delay == 13)
        probability = 0.73;
    else if (delay == 14)
        probability = 0.78;
    else if (delay == 15)
        probability = 0.8;
    else if (delay == 16)
        probability = 0.82;
    else if (delay == 17)
        probability = 0.86;
    else if (delay == 18)
        probability = 0.88;
    else if (delay == 19)
        probability = 0.91;
    else if (delay == 20)
        probability = 0.94;
    else if (delay == 21)
        probability = 0.96;
    else if (delay == 22)
        probability = 0.97;
    else if (delay == 23)
        probability = 0.98;
    else if (delay == 24)
        probability = 0.99;
    else if (delay == 25)
        probability = 1;
    else if (delay > 25)
        probability =  1;
    else
        probability = 0;

    return probability;
}


bool Individual::getEmulateScanning()
{
    return emulateScanning;
}

int Individual::getNscanForMutation()
{
    return nscansForMutation;
}


void Individual::setNewNscansForMutation()
{
    //nscansForMutation = qrand() % ((8 + 1) - 1) + 1;
    nscansForMutation = 1;
}
