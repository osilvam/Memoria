#ifndef SIMFILES_CPP
#define SIMFILES_CPP

#include "SimFiles.hpp"

using namespace std;

SimFiles::SimFiles()
{
	if(system("mkdir -p simulation_files") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to create folder 'simulation_files'" << endl;
		exit(0);
	}

	if(system("rm -f ./simulation_files/*.txt") == -1)
	{
		cerr << "SIMFILES ERROR:\tFailed to remove files inside of 'simulation_files' folder" << endl;
		exit(0);
	}	

	file_fitness.open("simulation_files/fitness.txt");
	file_frecuency.open("simulation_files/frecuency.txt");
	file_distance.open("simulation_files/distance.txt");
	file_champions.open("simulation_files/champions.txt");
}

SimFiles::~SimFiles()
{
	file_fitness.close();
	file_frecuency.close();
	file_distance.close();
	file_champions.close();
}
	
void SimFiles::addFileFitness(vector < Fitness * > fitness, int generation)
{
	vector < double > fit;

	for(int i = 0; i < (int)fitness.size(); i++)
	{
		vector < double > aux(fitness.at(i)->getGenerationFitness());
		fit.insert(fit.end(),aux.begin(),aux.end());
	}

	double average = mean(fit);
	double stddesv = stdDesviation(fit);

	file_fitness << generation << "\t" << average << "\t" << stddesv << endl;

	fit.clear();

	for(int i = 0; i < (int)fitness.size(); i++)
	{
		vector < double > aux(fitness.at(i)->getGenerationFrequency());
		fit.insert(fit.end(),aux.begin(),aux.end());
	}

	average = mean(fit);
	stddesv = stdDesviation(fit);

	file_frecuency << generation << "\t" << average << "\t" << stddesv << endl;

	fit.clear();

	for(int i = 0; i < (int)fitness.size(); i++)
	{
		vector < double > aux(fitness.at(i)->getGenerationDistance());
		fit.insert(fit.end(),aux.begin(),aux.end());
	}

	average = mean(fit);
	stddesv = stdDesviation(fit);

	file_distance << generation << "\t" << average << "\t" << stddesv << endl;
}

void SimFiles::addFileChampions(double fitness, int generation, int population)
{
	file_champions << generation << "\t" << population << "\t" << fitness << endl;
}

#endif