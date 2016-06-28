if ! [[ -d RobotLib ]]
	then
	echo "Downloading RobotLib library from git repository"
	git clone https://github.com/osilvam/RobotLib.git
	cd RobotLib; make; sudo make install; cd ..;
else
	cd RobotLib
	LOCAL=$(git rev-parse @)
	REMOTE=$(git rev-parse @{u})
	if [ $LOCAL = $REMOTE ]
		then
		echo "RobotLib is already downloaded and Up-to-date"
		cd ..
	else
		cd ..
		rm -f -R /RobotLib
		echo "Downloading RobotLib library from git repository"
		git clone https://github.com/osilvam/RobotLib.git
		cd RobotLib; make; sudo make install; cd ..;
	fi
fi

VREPF=$(ls -d */ | grep V-REP)
cd $VREPF
if ! [[ -f MultiVrep.sh ]]
	then
	cp ../MultiVrep.sh .
fi
cd ..

if ! [[ -d NEAT ]]
	then
	echo "Downloading NEAT library from git repository"
	git clone https://github.com/osilvam/NEAT.git
	cd NEAT; make; sudo make install; cd ..;
else
	cd NEAT
	LOCAL=$(git rev-parse @)
	REMOTE=$(git rev-parse @{u})
	if [ $LOCAL = $REMOTE ]
		then
		echo "NEAT is already downloaded and Up-to-date"		
		cd ..
	else
		cd ..
		rm -f -R /NEAT
		echo "Downloading NEAT library from git repository"
		git clone https://github.com/osilvam/NEAT.git
		cd NEAT; make; sudo make install; cd ..;
	fi
fi

if ! [[ -d HyperNeat ]]
	then
	echo "Downloading HyperNeat library from git repository"
	git clone https://github.com/osilvam/HyperNeat.git
	cd HyperNeat; make; sudo make install; cd ..;
else
	cd HyperNeat
	LOCAL=$(git rev-parse @)
	REMOTE=$(git rev-parse @{u})
	if [ $LOCAL = $REMOTE ]
		then
		echo "HyperNeat is already downloaded and Up-to-date"		
		cd ..
	else
		cd ..
		rm -f -R /HyperNeat
		echo "Downloading HyperNeat library from git repository"
		git clone https://github.com/osilvam/HyperNeat.git
		cd HyperNeat; make; sudo make install; cd ..;
	fi
fi

cd ARGO/HyperNEAT_experiment; make; cd ../..;
