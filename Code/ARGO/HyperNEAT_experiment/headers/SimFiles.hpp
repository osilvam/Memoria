#ifndef SIMFILES_HPP
#define SIMFILES_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <ROBOTLIB>
#include "Fitness.hpp"
#include "CalcFunctions.hpp"

class Fitness;

class SimFiles
{
	ofstream file_fitness;
	ofstream file_frecuency;
	ofstream file_distance;
	ofstream file_champions;

public:

	SimFiles();
	~SimFiles();

	void addFileFitness(vector < Fitness * > fitness, int generation);
	void addFileChampions(double fitness, int generation, int population);

};

#endif