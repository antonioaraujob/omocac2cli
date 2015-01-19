#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simulation.h"
//#include "qcustomplot.h"


#include <QSettings>

class MainWindow
{


private:

    /**
     * @brief Tamano de la poblacion para el algoritmo cultural
     */
    int population;

    /**
     * @brief Numero maximo de generaciones
     */
    int generationsNumber;


    /**
     * @brief Desviacion estandar de la mutacion
     */
    int standarDeviation;

    /**
     * @brief Tamano maximo del archivo externo
     */
    int externalFileSize;

    /**
     * @brief Numero de subintervalos de la rejilla del espacio de creencias
     */
    int gridSubintervalnumber;

    /**
     * @brief Frecuencia de actualizacion de parte normativa
     */
    int updateFrequency;

    /**
     * @brief Numero de encuentros por individuos en torneos
     */
    int matchesPerIndividual;

    /**
     * @brief Probabilidad de mutacion dirigida
     */
    double mutationProbability;

    /**
     * @brief Verdadero si se debe ejecutar la mutacion dirigida
     */
    bool doDirectedMutation;

    /**
     * @brief Objeto Simulation que abstrae todo el algoritmo cultural
     */
    Simulation * simulation;

    /**
     * @brief Lista de soluciones no dominadas resultantes de la ejecucion del algoritmo cultural original
     */
    QList<Individual *> genericAlgorithmSolutions;

    /**
     * @brief Lista de soluciones no dominadas resultantes de la ejecucion del algoritmo cultural modificado
     *
     * En la modificacion se esta utilizando
     */
    QList<Individual *> modificatedAlgorithmSolutions;

    /**
     * @brief repeatedSolutionList
     */
    QList< QList<Individual *> > repeatedSolutionList;

    /**
     * @brief repeatedOriginalSolutionList
     */
    QList< QList<Individual *> > repeatedOriginalSolutionList;

    /**
     * @brief repeatedModificatedSolutionList
     */
    QList< QList<Individual *> > repeatedModificatedSolutionList;


public:

    /**
     * @brief Constructor de la clase
     */
    MainWindow();

    /**
     * @brief Destructor de la clase
     */
    ~MainWindow();


    /**
     * @brief Completa el widget ListView con los individuos no dominados del
     * archivo externo al final de la ejecución del algoritmo cultural
     */
    void populateListView();

    /**
     * @brief Configura el widget para generar el grafico de los individuos no dominados del
     * archivo externo.
     *  Se esta utilizando QCustomPlot
     *
     * @param customPlot
     */
    //void setupCustomPlot(QCustomPlot *customPlot);

    /**
     * @brief Valida los parametros antes de ejecutar el algoritmo
     *
     *  @return Verdadero si todos los campos son validos
     */
    bool validateFields();

    //void newSetupCustomPlot(QCustomPlot *customPlot);

    //void setupCustomPlot2(QCustomPlot *customPlot);

    void plotSolutions();


    void storeExecutionSolution();

    /**
     * @brief Retorna el numero de individuos no dominados de todas las repeticiones
     * del algoritmo
     * @return
     */
    int getCountOfNonDominatedInRepetitions();

    /**
     * @brief Retorna el numero de individuos no dominados de todas las repeticiones
     * del algoritmo original
     * @return
     */

    int getCountOfNonDominatedInOriginalRepetitions();

    /**
     * @brief Retorna el numero de individuos no dominados de todas las repeticiones
     * del algoritmo modificado
     * @return
     */
    int getCountOfNonDominatedInModificatedRepetitions();



    /**
     * @brief Retorna el promedio de la funcion objetivo de todos los individuos no dominados
     * luego de las repeticiones del algoritmo
     * @param fo identificador de la funcion objetivo: 1 para descubierta, 2 para latencia
     * @param list lista de individuos no dominados sobre la cual calcular el promedio
     *
     * @return promedio de la funcion objetivo
     */
    double getMeanOfObjectiveFunction(int fo, QList<QList<Individual *> > list , int type);

    /**
     * @brief retorna la desviacion estandar de la funcion objetivo pasada como argumento
     * @param mean media de la funcion objetivo seleccionada
     * @param fo funcion objetivo seleccionada: 1 para descubierta, 2 para latencia
     * @param list lista de individuos no dominados sobre la cual calcular el promedio
     * @return desviacion estandar de la funcion objetivo pasada como argumento
     */
    double getStandardDeviation(double mean, int fo, QList<QList<Individual *> >list, int type);


    /**
     * @brief Retorna el tiempo promedio de ejecucion de 30 repeticiones
     * @param l lista de los tiempos de ejecucion de las 30 repeticiones
     * @return tiempo promedio de ejecucion de 30 repeticiones
     */
    double getMeanExecutionTime(QList<double> l);

    /**
     * @brief Retorna la desviacion estandar del tiempo de ejecucion
     * @param l lista de los tiempos de ejecucion de las 30 repeticiones
     * @param mean tiempo promedio
     * @return
     */
    double getStdDeviationExecutionTime(QList<double> l, double mean);


    /**
     * @brief Retorna la lista de individuos no dominados de la lista pasada como argumento
     * @param list lista de individuos de los cuales obtener los no dominados
     * @return lista de individuos no dominados
     */
    QList<Individual*> getNonDominatedIndividualsFromList(QList<QList<Individual*> >list);

    /**
     * @brief Retorna la lista de individuos no dominados de las 30 ejecuciones del algoritmo
     * @param original verdadero si se debe utilizar la lista del algoritmo original; falso en caso
     * de usar la lista del algoritmo modificado.
     * @return lista de individuos no dominados (aproximacion del frente de Pareto)
     */
    QList<Individual*> getNonDominatedIndivualsFromRepetitions(bool original);


    /**
     * @brief Funcion para generar un archivo con los individuos de la lista pasada como
     * argumento
     * @param list lista de individuos para escribir en el archivo
     * @param fileName nombre del archivo que almacenara los individuos. La ruta del archivo
     * sera: /tmp/fileName.txt
     */
    void reportIndividualAsFile(QList<Individual*> list, QString fileName);


    /**
     * @brief Funcion para colocar las cadenas de individuos en los listview de la
     * pestana de cadenas de la interfaz grafica
     * @param list lista de individuos a colocar en el listview
     * @param listView listview donde se colocan los individuos
     */
    //void populateAListView(QList<Individual*> list, QListView * listView);

//public slots:

    /**
     * @brief Slot para ejecutar el algoritmo cultural al presionar un boton en
     * la interfaz grafica
     */
    void executeAlgorithm();


    /**
     * @brief Slot para habilitar o deshabilitar el campo para introducir el valor de la
     *  probabilidad de mutacion dirigida
     * @param state Estado del check box
     */
    void activateDirectedMutation(int state);

    /**
     * @brief Slot para cambiar el valor del numero de encuentros por individuo en el torneo
     * @param str
     */
    void checkPopulationSize(const QString & str);

    /**
     * @brief Slot para habilitar el boton de comparacion de los algoritmos genericos y modificado
     * @param state
     */
    void activateComparationButton(int state);

    /**
     * @brief Slot para ejecutar el algoritmo PSO modificado al presionar un boton en la
     * interfaz grafica
     */
    void compareAlgorithms();



    void repeatAlgorithm();

    void view();

    void viewAll();

    /**
     * @brief slot para comparacion la ejecucion repetida 30 veces de cada uno de los algoritmos
     *
     * Se ejecuta primero el algorimo original y almacenan todos los individuos no dominados,
     * luego se ejecuta el algoritmo con la mutación dirigida y se
     *
     */
    void compareAlgorithmRepeated();





};

#endif // MAINWINDOW_H
