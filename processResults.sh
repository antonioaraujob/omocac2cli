#!/bin/bash

# script para procesar los resultados del programa omocac2cli y generar una salida
# en formato de tabla de LaTeX
#
#
# El formato de la tabla es como sigue
#
#
# 	| ch1<min,max>->AP|...|ch11<min,max>->AP|totalAP|totalLatencia|
#
#
#

# iniciar el archivo latex
echo "\documentclass{article}
\usepackage{fullpage}
\usepackage[a4paper,margin=1in,landscape]{geometry}

\usepackage{tabularx}

\title{Resultados de ejecucion}
\author{PGCOMP}
\date{}

\begin{document}
\maketitle

\begin{table}[h]
\centering
\caption{Channel sequences}
\label{tab:summary}

\begin{tabularx}{\textwidth}{XXXXXXXXXXXrr}

%\begin{tabular}{lrrrrrrrrrrrr}
\hline
\multicolumn{11}{l}{Ch$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$ & \$FO_2\$ \\""\\
\hline
" > /tmp/salida.tex


# procesar cada linea de secuencia de canales
awk ' 

BEGIN { 
	FS=",";  
}  

{ 
	print $1"$<$"$2","$3"$>\\rightarrow$"$4" & " $5"$<$"$6","$7"$>\\rightarrow$"$8" & " $9"$<$"$10","$11"$>\\rightarrow$"$12" & " \
	$13"$<$"$14","$15"$>\\rightarrow$"$16" & " $17"$<$"$18","$19"$>\\rightarrow$"$20" & " $21"$<$"$22","$23"$>\\rightarrow$"$24" & " \
	$25"$<$"$26","$27"$>\\rightarrow$"$28" & " $29"$<$"$30","$31"$>\\rightarrow$"$32" & " $33"$<$"$34","$35"$>\\rightarrow$"$36" & " \
	$37"$<$"$38","$39"$>\\rightarrow$"$40" & " $41"$<$"$42","$43"$>\\rightarrow$"$44" & " $45" & "$46 "\134\134" ;
}' /tmp/individuosFrenteParetoOriginal.txt >> /tmp/salida.tex

# finalizar la tabla de latex
echo "\hline
%\end{tabular}

\end{tabularx}

\end{table}

\end{document}" >> /tmp/salida.tex

