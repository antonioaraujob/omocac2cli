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
# version: 6
# agrega una columna al final de la tabla que incluye el valor de nscan para el 
# individuo


# iniciar el archivo latex
echo "\documentclass{article}
\usepackage{fullpage}
\usepackage[a4paper,margin=10mm,landscape]{geometry}

\usepackage{tabularx}
\usepackage{tablefootnote}
\usepackage[table]{xcolor}

\title{Resultados de ejecucion}
%\author{PGCOMP}
\date{}

\begin{document}
\maketitle

\begin{table}[h]
\centering
\caption{Channel sequences}
\label{tab:sequences}

\definecolor{light-gray}{gray}{0.95}
\rowcolors{1}{white}{light-gray}

%\begin{tabularx}{\textwidth}{XXXXXXXXXXXrr}
\begin{tabularx}{\textwidth}{|XXXXXXXXX|m{0.5cm}|m{0.5cm}|m{0.3cm}|}



%\begin{tabular}{lrrrrrrrrrrrr}
\hline
%\multicolumn{11}{l}{Ch$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$ & \$FO_2\$ \\""\\
\multicolumn{9}{|l|}{Ch\newline\$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$\newline(\#AP) & \$FO_2\$\newline(ms) & nscan\\""\\

\hline
" > salida.tex


# procesar cada linea de secuencia de canales del archivo individuosFrenteParetoOriginal.txt
awk ' 

BEGIN { 
	FS=","; gen1="";gen2="";gen3="";gen4="";gen5="";gen6="";gen7="";gen8="";gen9="";
}

{ 
	if ($4=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen1="\\textit{"$1"}";
		gen1="\\textit{\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen1="\\textbf{"$1"}";
		gen1="\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4;
	}
	if ($8=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen2="\\textit{"$5"}";
		gen2="\\textit{\\textbf{"$5"}\\newline$<$"$6","$7"$>\\rightarrow$"$8"}";

	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen2="\\textbf{"$5"}";
		gen2="\\textbf{"$5"}\\newline$<$"$6","$7"$>\\rightarrow$"$8;

	}
	if ($12=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		gen3="\\textit{"$9"}";
		gen3="\\textit{\\textbf{"$9"}\\newline$<$"$10","$11"$>\\rightarrow$"$12"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen3="\\textbf{""$9}";
		gen3="\\textbf{"$9"}\\newline$<$"$10","$11"$>\\rightarrow$"$12;

	}
	if ($16=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen4="\\textit{"$13"}";
		gen4="\\textit{\\textbf{"$13"}\\newline$<$"$14","$15"$>\\rightarrow$"$16"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen4="\\textbf{"$13"}";
		gen4="\\textbf{"$13"}\\newline$<$"$14","$15"$>\\rightarrow$"$16;

	}
	if ($20=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen5="\\textit{"$17"}";
		gen5="\\textit{\\textbf{"$17"}\\newline$<$"$18","$19"$>\\rightarrow$"$20"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen5="\\textbf{"$17"}";
		gen5="\\textbf{"$17"}\\newline$<$"$18","$19"$>\\rightarrow$"$20;

	}
	if ($24=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen6="\\textit{"$21"}";
		gen6="\\textit{\\textbf{"$21"}\\newline$<$"$22","$23"$>\\rightarrow$"$24"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen6="\\textbf{"$21"}";
		gen6="\\textbf{"$21"}\\newline$<$"$22","$23"$>\\rightarrow$"$24;

	}
	if ($28=="0")
	{17.05.2015_18.48.56
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen7="\\textit{"$25"}";
		gen7="\\textit{\\textbf{"$25"}\\newline$<$"$26","$27"$>\\rightarrow$"$28"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen7="\\textbf{"$25"}";
		gen7="\\textbf{"$25"}\\newline$<$"$26","$27"$>\\rightarrow$"$28;

	}
	if ($32=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen8="\\textit{"$29"}";
		gen8="\\textit{\\textbf{"$29"}\\newline$<$"$30","$31"$>\\rightarrow$"$32"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen8="\\textbf{"$29"}";
		gen8="\\textbf{"$29"}\\newline$<$"$30","$31"$>\\rightarrow$"$32;
	
	}
	if ($36=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen9="\\textit{"$33"}";
		gen9="\\textit{\\textbf{"$33"}\\newline$<$"$34","$35"$>\\rightarrow$"$36"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen9="\\textbf{"$33"}";
		gen9="\\textbf{"$33"}\\newline$<$"$34","$35"$>\\rightarrow$"$36;

	}
	

	print gen1" & "gen2" & "gen3" & "gen4" & "gen5" & "gen6" & "gen7" & "gen8" & "gen9" & " $37" & "$38 "& " $39 "\134\134" ;

}' individuosFrenteParetoOriginal.txt >> salida.tex

# finalizar la tabla de latex
echo "\hline
%\end{tabular}

\end{tabularx}

\end{table}


" >> salida.tex

# ******************************************************************************
# agregar la tabla 2 correspondiente a los individuos con canales ordenados por mayor latencia

echo "
\begin{table}[h]
\centering
\caption{Channel sequences ordered by channels latency}
\label{tab:sequencesorderbylatency}

\definecolor{light-gray}{gray}{0.95}
\rowcolors{1}{white}{light-gray}

%\begin{tabularx}{\textwidth}{XXXXXXXXXXXrr}
\begin{tabularx}{\textwidth}{|XXXXXXXXX|m{0.5cm}|m{0.5cm}|m{0.3cm}|}

%\begin{tabular}{lrrrrrrrrrrrr}
\hline
%\multicolumn{11}{l}{Ch$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$ & \$FO_2\$ \\""\\
\multicolumn{9}{|l|}{Ch\newline\$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$\newline(\#AP) & \$FO_2\$\newline(ms) & nscan \\""\\
\hline
" >> salida.tex

# procesar cada linea de secuencia de canales del archivo individuosFrenteParetoOriginalPorLatencia.txt
awk ' 

BEGIN { 
	FS=","; gen1="";gen2="";gen3="";gen4="";gen5="";gen6="";gen7="";gen8="";gen9="";
}  

{ 

	if ($4=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen1="\\textit{"$1"}";
		#gen1="\\textit{\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
		gen1="\\textit{$\\textbf{"$1"}^{"$2+$3"}$\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen1="\\textbf{"$1"}";
		#gen1="\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4;
		gen1="$\\textbf{"$1"}^{"$2+$3"}$\\newline$<$"$2","$3"$>\\rightarrow$"$4;
	}
	if ($8=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen2="\\textit{"$5"}";
		gen2="\\textit{$\\textbf{"$5"}^{"$2+$3+$6+$7"}$\\newline$<$"$6","$7"$>\\rightarrow$"$8"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen2="\\textbf{"$5"}";
		gen2="$\\textbf{"$5"}^{"$2+$3+$6+$7"}$\\newline$<$"$6","$7"$>\\rightarrow$"$8;
	}

	if ($12=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen3="\\textit{"$9"}";
		#$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12" & " \
		gen3="\\textit{$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen3="\\textbf{""$9}";
		gen3="$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12;
	}
	if ($16=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen4="\\textit{"$13"}";
		gen4="\\textit{$\\textbf{"$13"}^{"$2+$3+$6+$7+$10+$11+$14+$15"}$\\newline$<$"$14","$15"$>\\rightarrow$"$16"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen4="\\textbf{"$13"}";
		gen4="$\\textbf{"$13"}^{"$2+$3+$6+$7+$10+$11+$14+$15"}$\\newline$<$"$14","$15"$>\\rightarrow$"$16;
	}
	if ($20=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen5="\\textit{"$17"}";
		gen5="\\textit{$\\textbf{"$17"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19"}$\\newline$<$"$18","$18"$>\\rightarrow$"$20"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen5="\\textbf{"$17"}";
		gen5="$\\textbf{"$17"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19"}$\\newline$<$"$18","$19"$>\\rightarrow$"$20;
	}
	if ($24=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen6="\\textit{"$21"}";
		gen6="\\textit{$\\textbf{"$21"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23"}$\\newline$<$"$22","$23"$>\\rightarrow$"$24"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen6="\\textbf{"21"}";
		gen6="$\\textbf{"$21"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23"}$\\newline$<$"$22","$23"$>\\rightarrow$"$24;
	}
	if ($28=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen7="\\textit{"$25"}";
		gen7="\\textit{$\\textbf{"$25"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27"}$\\newline$<$"$26","$27"$>\\rightarrow$"$28"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen7="\\textbf{"$25"}";
		gen7="$\\textbf{"$25"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27"}$\\newline$<$"$26","$27"$>\\rightarrow$"$28;
	}
	if ($32=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen8="\\textit{"$29"}";
		gen8="\\textit{$\\textbf{"$29"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31"}$\\newline$<$"$30","$31"$>\\rightarrow$"$32"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen8="\\textbf{"$29"}";
		gen8="$\\textbf{"$29"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31"}$\\newline$<$"$30","$31"$>\\rightarrow$"$32;
	}
	if ($36=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen9="\\textit{"$33"}";
		gen9="\\textit{$\\textbf{"$33"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31+$34+$35"}$\\newline$<$"$34","$35"$>\\rightarrow$"$36"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen9="\\textbf{"$33"}";
		gen9="$\\textbf{"$33"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31+$34+$35"}$\\newline$<$"$34","$35"$>\\rightarrow$"$36;
	}
	
		
	print gen1" & "gen2" & "gen3" & "gen4" & "gen5" & "gen6" & "gen7" & "gen8" & "gen9" & " $37" & "$38" &" $39 "\134\134" ;

}' individuosFrenteParetoOriginalPorLatencia.txt >> salida.tex

# finalizar la tabla de latex
echo "
\hline
%\end{tabular}

\end{tabularx}

\end{table}


" >> salida.tex






# ******************************************************************************
# agregar la tabla 3 correspondiente a los individuos con canales ordenados por AP ascendente

echo "
\begin{table}[h]
\centering
\caption{Channel sequences ordered by ascending APs discovered. If two channels have same APs discovered the latency in each channel is used to order the sequence. }
\label{tab:sequencesorderbyapsdiscoveredascending}

\definecolor{light-gray}{gray}{0.95}
\rowcolors{1}{white}{light-gray}

%\begin{tabularx}{\textwidth}{XXXXXXXXXXXrr}
\begin{tabularx}{\textwidth}{|XXXXXXXXX|m{0.5cm}|m{0.5cm}|m{0.3cm}|}

%\begin{tabular}{lrrrrrrrrrrrr}
\hline
%\multicolumn{11}{l}{Ch$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$ & \$FO_2\$ \\""\\
\multicolumn{9}{|l|}{Ch\newline\$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$\newline(\#AP) & \$FO_2\$\newline(ms) & nscan \\""\\
\hline
" >> salida.tex


# procesar cada linea de secuencia de canales del archivo individuosFrenteParetoOriginalPorAPsAscendente.txt
awk ' 

BEGIN { 
	FS=","; gen1="";gen2="";gen3="";gen4="";gen5="";gen6="";gen7="";gen8="";gen9="";
}  

{ 

	if ($4=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen1="\\textit{"$1"}";
		#gen1="\\textit{\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
		gen1="\\textit{$\\textbf{"$1"}^{"$2+$3"}$\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen1="\\textbf{"$1"}";
		#gen1="\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4;
		gen1="$\\textbf{"$1"}^{"$2+$3"}$\\newline$<$"$2","$3"$>\\rightarrow$"$4;
	}
	if ($8=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen2="\\textit{"$5"}";
		gen2="\\textit{$\\textbf{"$5"}^{"$2+$3+$6+$7"}$\\newline$<$"$6","$7"$>\\rightarrow$"$8"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen2="\\textbf{"$5"}";
		gen2="$\\textbf{"$5"}^{"$2+$3+$6+$7"}$\\newline$<$"$6","$7"$>\\rightarrow$"$8;
	}

	if ($12=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen3="\\textit{"$9"}";
		#$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12" & " \
		gen3="\\textit{$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen3="\\textbf{""$9}";
		gen3="$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12;
	}
	if ($16=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen4="\\textit{"$13"}";
		gen4="\\textit{$\\textbf{"$13"}^{"$2+$3+$6+$7+$10+$11+$14+$15"}$\\newline$<$"$14","$15"$>\\rightarrow$"$16"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen4="\\textbf{"$13"}";
		gen4="$\\textbf{"$13"}^{"$2+$3+$6+$7+$10+$11+$14+$15"}$\\newline$<$"$14","$15"$>\\rightarrow$"$16;
	}
	if ($20=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen5="\\textit{"$17"}";
		gen5="\\textit{$\\textbf{"$17"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19"}$\\newline$<$"$18","$18"$>\\rightarrow$"$20"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen5="\\textbf{"$17"}";
		gen5="$\\textbf{"$17"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19"}$\\newline$<$"$18","$19"$>\\rightarrow$"$20;
	}
	if ($24=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen6="\\textit{"$21"}";
		gen6="\\textit{$\\textbf{"$21"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23"}$\\newline$<$"$22","$23"$>\\rightarrow$"$24"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen6="\\textbf{"21"}";
		gen6="$\\textbf{"$21"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23"}$\\newline$<$"$22","$23"$>\\rightarrow$"$24;
	}
	if ($28=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen7="\\textit{"$25"}";
		gen7="\\textit{$\\textbf{"$25"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27"}$\\newline$<$"$26","$27"$>\\rightarrow$"$28"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen7="\\textbf{"$25"}";
		gen7="$\\textbf{"$25"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27"}$\\newline$<$"$26","$27"$>\\rightarrow$"$28;
	}
	if ($32=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen8="\\textit{"$29"}";
		gen8="\\textit{$\\textbf{"$29"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31"}$\\newline$<$"$30","$31"$>\\rightarrow$"$32"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen8="\\textbf{"$29"}";
		gen8="$\\textbf{"$29"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31"}$\\newline$<$"$30","$31"$>\\rightarrow$"$32;
	}
	if ($36=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen9="\\textit{"$33"}";
		gen9="\\textit{$\\textbf{"$33"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31+$34+$35"}$\\newline$<$"$34","$35"$>\\rightarrow$"$36"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen9="\\textbf{"$33"}";
		gen9="$\\textbf{"$33"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31+$34+$35"}$\\newline$<$"$34","$35"$>\\rightarrow$"$36;
	}
		
		
	print gen1" & "gen2" & "gen3" & "gen4" & "gen5" & "gen6" & "gen7" & "gen8" & "gen9" & " $37" & "$38 " & " $39 "\134\134" ;

}' individuosFrenteParetoOriginalPorAPsAscendente.txt >> salida.tex

# finalizar la tabla de latex
echo "
\hline
%\end{tabular}

\end{tabularx}

\end{table}


" >> salida.tex








# ******************************************************************************
# agregar la tabla 4 correspondiente a los individuos con canales ordenados por AP descendente

echo "
\begin{table}[h]
\centering
\caption{Channel sequences ordered by descending APs discovered. If two channels have same APs discovered the lower latency in channels is used to order the sequence. }
\label{tab:sequencesorderbyapsdiscovereddescending}

\definecolor{light-gray}{gray}{0.95}
\rowcolors{1}{white}{light-gray}

%\begin{tabularx}{\textwidth}{XXXXXXXXXXXrr}
\begin{tabularx}{\textwidth}{|XXXXXXXXX|m{0.5cm}|m{0.5cm}|m{0.3cm}|}

%\begin{tabular}{lrrrrrrrrrrrr}
\hline
%\multicolumn{11}{l}{Ch$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$ & \$FO_2\$ \\""\\
\multicolumn{9}{|l|}{Ch\newline\$<\$min,max\$>\rightarrow\$AP} & \$FO_1\$\newline(\#AP) & \$FO_2\$\newline(ms) & nscan \\""\\
\hline
" >> salida.tex


# procesar cada linea de secuencia de canales del archivo individuosFrenteParetoOriginalPorAPsDescendente.txt
awk ' 

BEGIN { 
	FS=","; gen1="";gen2="";gen3="";gen4="";gen5="";gen6="";gen7="";gen8="";gen9="";
}  

{ 

	if ($4=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen1="\\textit{"$1"}";
		#gen1="\\textit{\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
		gen1="\\textit{$\\textbf{"$1"}^{"$2+$3"}$\\newline$<$"$2","$3"$>\\rightarrow$"$4"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen1="\\textbf{"$1"}";
		#gen1="\\textbf{"$1"}\\newline$<$"$2","$3"$>\\rightarrow$"$4;
		gen1="$\\textbf{"$1"}^{"$2+$3"}$\\newline$<$"$2","$3"$>\\rightarrow$"$4;
	}
	if ($8=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen2="\\textit{"$5"}";
		gen2="\\textit{$\\textbf{"$5"}^{"$2+$3+$6+$7"}$\\newline$<$"$6","$7"$>\\rightarrow$"$8"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen2="\\textbf{"$5"}";
		gen2="$\\textbf{"$5"}^{"$2+$3+$6+$7"}$\\newline$<$"$6","$7"$>\\rightarrow$"$8;
	}

	if ($12=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen3="\\textit{"$9"}";
		#$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12" & " \
		gen3="\\textit{$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen3="\\textbf{""$9}";
		gen3="$\\textbf{"$9"}^{"$2+$3+$6+$7+$10+$11"}$\\newline$<$"$10","$11"$>\\rightarrow$"$12;
	}
	if ($16=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen4="\\textit{"$13"}";
		gen4="\\textit{$\\textbf{"$13"}^{"$2+$3+$6+$7+$10+$11+$14+$15"}$\\newline$<$"$14","$15"$>\\rightarrow$"$16"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen4="\\textbf{"$13"}";
		gen4="$\\textbf{"$13"}^{"$2+$3+$6+$7+$10+$11+$14+$15"}$\\newline$<$"$14","$15"$>\\rightarrow$"$16;
	}
	if ($20=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen5="\\textit{"$17"}";
		gen5="\\textit{$\\textbf{"$17"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19"}$\\newline$<$"$18","$18"$>\\rightarrow$"$20"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen5="\\textbf{"$17"}";
		gen5="$\\textbf{"$17"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19"}$\\newline$<$"$18","$19"$>\\rightarrow$"$20;
	}
	if ($24=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen6="\\textit{"$21"}";
		gen6="\\textit{$\\textbf{"$21"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23"}$\\newline$<$"$22","$23"$>\\rightarrow$"$24"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen6="\\textbf{"21"}";
		gen6="$\\textbf{"$21"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23"}$\\newline$<$"$22","$23"$>\\rightarrow$"$24;
	}
	if ($28=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen7="\\textit{"$25"}";
		gen7="\\textit{$\\textbf{"$25"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27"}$\\newline$<$"$26","$27"$>\\rightarrow$"$28"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen7="\\textbf{"$25"}";
		gen7="$\\textbf{"$25"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27"}$\\newline$<$"$26","$27"$>\\rightarrow$"$28;
	}
	if ($32=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen8="\\textit{"$29"}";
		gen8="\\textit{$\\textbf{"$29"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31"}$\\newline$<$"$30","$31"$>\\rightarrow$"$32"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen8="\\textbf{"$29"}";
		gen8="$\\textbf{"$29"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31"}$\\newline$<$"$30","$31"$>\\rightarrow$"$32;
	}
	if ($36=="0")
	{
		#gen1="$\textit{$\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5}";
		#gen9="\\textit{"$33"}";
		gen9="\\textit{$\\textbf{"$33"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31+$34+$35"}$\\newline$<$"$34","$35"$>\\rightarrow$"$36"}";
	}
	else
	{
		#gen1="$\\textbf{10}^{70}$\newline$<$7,63$>\rightarrow$5";
		#gen9="\\textbf{"$33"}";
		gen9="$\\textbf{"$33"}^{"$2+$3+$6+$7+$10+$11+$14+$15+$18+$19+$22+$23+$26+$27+$30+$31+$34+$35"}$\\newline$<$"$34","$35"$>\\rightarrow$"$36;
	}
	
	
		
	print gen1" & "gen2" & "gen3" & "gen4" & "gen5" & "gen6" & "gen7" & "gen8" & "gen9" & " $37" & "$38" & " $39 "\134\134" ;

}' individuosFrenteParetoOriginalPorAPsDescendente.txt >> salida.tex

# finalizar la tabla de latex
echo "
\hline
%\end{tabular}

\end{tabularx}

\end{table}


" >> salida.tex








# ******************************************************************************
# escribir la configuracion utilizada para la ejecucion
awk ' 

BEGIN {}  

{ 
	print $0 "\n";
}' settings.ini >> salida.tex


echo "

\end{document}" >> salida.tex


# *****************************************************************************
# compilar el archivo /salida.tex y generar el pdf

pdflatex salida.tex
