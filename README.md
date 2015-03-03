# omocac2cli
omocac2cli

Dependencias Qt>=4.8, libsqlite3

Para compilar: 

$ qmake
$ make

Para ejecutar:

Ajustar parámetros en el archivo settings.ini:

[CONF]
tamanoDeIndividuo=11
poblacion=20
numeroDeGeneraciones=30
desviacionEstandar=2
tamanoArchivoExterno=100
numeroDeSubintervalosDeRejilla=10
frecuenciaDeActualizacion=2
numeroDeEncuentrosPorIndividuo=10
probabilidadDeMutacionDirigida=0.5
ejecutarMutacionDirigida=false
numeroDeRepeticionesDeSimulacion=30
ejecutarComparacionDeAlgoritmos=false
emularScanning=true


