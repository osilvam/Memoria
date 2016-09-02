ROBOTOPC=(ARGO ARGOV2 PB2 QUADRATOT)
ANNOPC=(run_HyperNEAT_experiment run_TauHyperNEAT_experiment)

echo Escriba el numero de la opcion de robot que desea utilizar
echo Opciones:
echo -e ' \t ' 1.- ARGO
echo -e ' \t ' 2.- ARGOV2
echo -e ' \t ' 3.- PB2
echo -e ' \t ' 4.- QUADRATOT
read robot
robot=${ROBOTOPC[$((robot - 1))]}

echo Escriba el numero de la opcion de ANN que desea utilizar
echo Opciones:
echo -e ' \t ' 1.- HYPERNEAT
echo -e ' \t ' 2.- TAUHYPERNEAT
read experiment
experiment=${ANNOPC[$((experiment - 1))]}

echo Teclee T para realizar un entrenamiento o S para mostrar resultados:
read tarea

puerto=19997
numero=1

if [ $tarea == T ]
	then
	echo Indique el puerto inicial y el numero de simuladores separados por espacios
	read puerto numero
fi

if [ -d V-REP* ]
	then
	cd V-REP*
	chmod 755 MultiVrep.sh; 
	PIDS=$(bash ./MultiVrep.sh $puerto $numero "../$robot.ttt" &)
	cd ..
else
	echo ERROR: No existe la carpeta que contiene al simulador V-REP
	echo V-REP puede ser descargado desde 'http://www.coppeliarobotics.com/downloads.html'
	exit
fi

sleep 5

ruta="./${robot}_recorder/${experiment#*_}"
cd $ruta

echo Presione la tecla Enter para comenzar el experimento
read ok

if [ $tarea == T ]
	then
	rm -f bin/VrepsList

	echo "$numero" >> bin/VrepsList
	for (( i = 0; i < $numero; i++ )); do
			echo "127.0.0.1 $puerto" >> bin/VrepsList
		((puerto = puerto + 1))
	done

	make runTrain
	make save
elif [ $tarea == S ]
	then
	if [ -f "./bin/NEAT_organisms/Champion.txt" ]
		then
		rm -f ./bin/VrepsList
		echo "1" >> ./bin/VrepsList
		echo "127.0.0.1 19997" >> ./bin/VrepsList

		make runChampion
	else
		echo ERROR: No existe el archivo Champion.txt
	fi	
else
	echo ERROR: La instrucción no es correcta.
fi

kill -9 $PIDS