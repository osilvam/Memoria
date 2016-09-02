EXECUTABLE1 = Train
EXECUTABLE2 = Champion
VPATH = ./src ./headers 
CC = g++ -O3 -std=c++11
CFLAGS = -g -Wall -I./src -I./headers -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255
LDFLAGS = -lpthread -L. -ltauhyperneat -lrobotlib -lneat
DATE = `date +'%F--%T'`
CURRENFOLDER = $(notdir $(shell pwd))
SPATH = ./saveTrains_$(CURRENFOLDER)/$(DATE)
CNAME = ../saveTrains.zip

all: CalcFunctions.o Fitness.o SimFiles.o SimFiles2.o
	@mkdir -p bin/NEAT_organisms
	@rm -f ./bin/NEAT_organisms/*
	@mkdir -p bin/TauHyperNeat_conf_files
	@rm -f ./bin/TauHyperNeat_conf_files/*
	@echo "Linking all objects to ./bin/$(EXECUTABLE1)"
	@$(CC) $(CFLAGS) ./src/Train.cpp ./objects/Fitness.o ./objects/SimFiles.o ./objects/SimFiles2.o ./objects/CalcFunctions.o -o ./bin/$(EXECUTABLE1) $(LDFLAGS)
	@echo "Linking all objects to ./bin/$(EXECUTABLE2)"
	@$(CC) $(CFLAGS) ./src/Champion.cpp -o ./bin/$(EXECUTABLE2) $(LDFLAGS)

CalcFunctions.o: CalcFunctions.cpp CalcFunctions.hpp
	@mkdir -p objects
	@echo "Compiling CalcFunctions.cpp to CalcFunctions.o"
	@$(CC) $(CFLAGS) -c ./src/CalcFunctions.cpp -o ./objects/CalcFunctions.o

Fitness.o: Fitness.cpp Fitness.hpp
	@mkdir -p objects
	@echo "Compiling Fitness.cpp to Fitness.o"
	@$(CC) $(CFLAGS) -c ./src/Fitness.cpp -o ./objects/Fitness.o

SimFiles.o: SimFiles.cpp SimFiles.hpp
	@mkdir -p objects
	@echo "Compiling SimFiles.cpp to SimFiles.o"
	@$(CC) $(CFLAGS) -c ./src/SimFiles.cpp -o ./objects/SimFiles.o

SimFiles2.o: SimFiles2.cpp SimFiles2.hpp
	@mkdir -p objects
	@echo "Compiling SimFiles2.cpp to SimFiles2.o"
	@$(CC) $(CFLAGS) -c ./src/SimFiles2.cpp -o ./objects/SimFiles2.o

clean:
	@echo "Cleaning"
	@rm -f -R ./objects
	@rm -f ./bin/$(EXECUTABLE1)	
	@rm -f ./bin/$(EXECUTABLE2)
	@rm -f -R ./bin/NEAT_organisms
	@rm -f -R ./bin/TauHyperNeat_conf_files
	@rm -f -R ./bin/simulation_files*
	@rm -f -R ./bin/videoRecorder*
	@rm -f ./bin/*.txt
	@if [ -d saveTrains* ] ; \
	then \
		zip -r $(CNAME) ./saveTrains*/* ; \
		rm -f -R ./saveTrains* ; \
	fi;

cleanTrain:
	@rm -f ./bin/NEAT_organisms/*

save:
	@mkdir -p $(SPATH); cp -R ./bin/* $(SPATH);

runTrain:
	make cleanTrain; 
	cd bin; ./$(EXECUTABLE1) tauhyperneat_config.json user_def genetic_encoding VrepsList

runChampion: 
	cd bin; ./$(EXECUTABLE2) tauhyperneat_config.json ./NEAT_organisms/Champion.txt